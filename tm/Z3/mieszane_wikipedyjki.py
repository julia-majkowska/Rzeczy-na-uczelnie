
import fileinput
from collections import defaultdict as dd 
from highlight import highlight2, green, yellow_line
from nltk.tokenize import word_tokenize
import json
import jsonpickle
import psycopg2
from colorama import Fore, Style#, init
from copy import deepcopy
import bisect

def read_lemats() : 
    res = dd(lambda:set())
    with open('polimorfologik-2.1.txt') as f:
        l = f.readline()
        while l: 
            words = l.split(';')[:2]
            res[words[1]].add(words[0])
            l= f.readline()
    return res

lemats = read_lemats()
conn = psycopg2.connect("dbname=indeks user=julia")

def get_doc_starts() : 
    cur = conn.cursor()
    cur.execute('''SELECT id, starindex  FROM docstarts''')
    lista = cur.fetchall()
    #print(lista)
    return lista

doc_starts = get_doc_starts()
doc_indices = [int(x[1]) for x in doc_starts]

def get_indeks(slowo): 
    cur = conn.cursor()
    cur.execute('''SELECT indeks FROM posindex where lemat = \'%s\''''%slowo)
    lista = cur.fetchall()
    #print(lista)
    cur.close()
    conn.commit()
    return jsonpickle.decode(lista[0][0])

def get_dokument(indeks): 
    cur = conn.cursor()
    cur.execute('''SELECT content FROM articles where id = \'%s\''''%str(indeks))
    dokument = cur.fetchall()
    cur.close()
    conn.commit()
    return dokument[0][0]

def find_doc_number(indeks): 
    i = bisect.bisect_left(doc_indices, indeks)
    return i
    
def find_quotes(query_tokens) : #query tokens jest zadnieżdżoną listą gdzie fraza w cudzysłowie jest traktowana jak pojedynczy token
    i = 0
    documents = set()
    for token_list in query_tokens: 
        quote_indices= None
        for ti in range(len(token_list)): 
            token = token_list[ti]
            lems = lemats[token]
            token_indices = set()
            for lem in lems: 
                token_indices = token_indices | get_indeks(lem)
            if quote_indices == None : 
                quote_indices = token_indices
            else : 
                quote_indices = quote_indices & set([x - ti for x in token_indices])
        if i == 0 : 
            documents = set([find_doc_number(x) for x in quote_indices])
            #print(documents)
        else :
            my_docs = set([find_doc_number(x) for x in quote_indices]) 
            #print(my_docs)
            documents &= set([find_doc_number(x) for x in quote_indices]) 
        i+=1
    
    #print(documents)
    return documents

def merge_lists(l1, l2): 
    if len(l1) > len(l2): 
        l1, l2 = l2, l1
    
    i2 = 0
    merged = []
    for i1 in range(len(l1)): 
        while i2 < len(l2) and l2[i2][0]-1 < l1[i1][0]: 
            i2+=1
        if i2 >= len(l2): 
            break; 
        if l2[i2][0]-1 == l1[i1][0] : 
            merged.append((l2[i2][0], l2[i2][1] + l1[i1][1]))
    return merged; 
            


def rank_document(query_tok, tekst): 
    goodness = 0 # *5 match w tytule razy 2 match dokładn
    lines = tekst.split("\n")
    title_tok = word_tokenize(lines[0])[2:]
    hits = [[] for i in range(len(query_tok))] #wrzucam pary indeks w dokumencie, mnożnik
    #body_hits = [[] for i in range(len(query_tok))]
    indeks_in_docu = 0
    for qti in range(len(query_tok)): 
        qt_list = query_tok[qti]
        for it in range(len(title_tok)): 
            tok_goodness = 0
            found =1
            for qt in qt_list: 
                tt = title_tok[it]
                if qt == tt : 
                    tok_goodness+=10
                elif match_tokens(tt, qt): 
                    tok_goodness+=5
                else: 
                    found = 0
                    break
            if found == 1: 
                hits[qti].append((it, tok_goodness))
                goodness+= tok_goodness
                it+= len(qt_list)
            indeks_in_docu +=1
            
            
    for i in range(1, len(lines), 1) : 
        line_tok = word_tokenize(lines[i])
        for qti in range(len(query_tok)): 
            qt_list = query_tok[qti]
            for it in range(len(line_tok)): 
                tok_goodness = 0
                found =1
                for qt in qt_list: 
                    tt = line_tok[it]
                    if qt == tt : 
                        tok_goodness+=2
                    elif match_tokens(tt, qt): 
                        tok_goodness+=1
                    else: 
                        found = 0
                        break;
                if found == 1: 
                    hits[qti].append((it, tok_goodness))
                    goodness+= tok_goodness
                    it+= len(qt_list)
                indeks_in_docu +=1
    
    #znajdz najdłuższy ciag zaczynający się od danego tokenu
    for start in range(len(query_tokens)):
        indexes = hits[start] 
        ii = 0
        for i in range(1, len(query_tokens) - start, 1): 
            new_indexes = merge_lists(indexes, hits[start + i])
            if len(new_indexes) == 0:
                break; 
            ii+=1
            indexes = new_indexes
            #goodness+= sum([indx[1] for i in indexes])
        goodness*=4**ii
            
                
    return goodness

def match_tokens(query_tok, text_tok): 
    a = lemats[query_tok.lower()]
    b = lemats[text_tok.lower()]
    intersec = a.intersection(b)
    return len(intersec) != 0

def my_highlight(qL, L): 
    
    r = []
    for i in range(len( L )):
        w = L[i]
        good = False
        for q in qL : 
            good_token = True
            if i + len(q) < len(L) : 
                for j in range(len(q)): 
                    if not match_tokens(q[j], L[i+j]) : 
                        good_token = False
            else:
                good_token = False
            if good_token :
                good = True
                break
        if good: 
            for j in range(len(q)): 
                r.append(Fore.RED + Style.BRIGHT + L[i+j]+ Fore.BLACK + Style.RESET_ALL)
            i+=len(q)
        else:
            r.append(w) 
    return ' '.join(r)


print("Ready for input\n")
for query in fileinput.input():
    query_tokens = []
    split_res = query[:-1].split('\"')
    for i in range(len(split_res)): 
        if i%2 == 0:
            query_tokens+= [[w] for w in split_res[i].split(' ') if w != '']
        else:
            query_tokens+= [[w for w in split_res[i].split(' ') if w != '']]
    
    print(query_tokens)
    print (green('QUERY: ') + query)
    good_documents = sorted([get_dokument(f) for f in find_quotes( query_tokens )], key = lambda x : rank_document(query_tokens, x), reverse = True)
    good_documents = [word_tokenize(x)for x in good_documents]
    for quote in good_documents: 
        print ('   ', my_highlight(query_tokens, quote))