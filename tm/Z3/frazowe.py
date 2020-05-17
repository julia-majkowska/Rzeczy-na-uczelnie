
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
    return i, doc_indices[i-1]
    
def find_quotes(query_tokens) : 
    quote_indices= None
    i = 0
    for token in query_tokens: 
        lems = lemats[token]
        token_indices = set()
        for lem in lems: 
            token_indices = token_indices | get_indeks(lem)
        if quote_indices == None : 
            quote_indices = token_indices
        else : 
            quote_indices = quote_indices & set([x - i for x in token_indices])
        i+=1
    
    print(quote_indices)
    return set([find_doc_number(x) for x in quote_indices])

def match_tokens(query_tok, text_tok): 
    a = lemats[query_tok.lower()]
    b = lemats[text_tok.lower()]
    intersec = a.intersection(b)
    return len(intersec) != 0

def my_highlight(q, L): 
    
    r = []
    for i in range(len( L )):
        w = L[i]
        good = True
        if i + len(q) < len(L) : 
            for j in range(len(q)): 
                if not match_tokens(q[j], L[i+j]) : 
                    good = False
        else:
            good = False
        if good: 
            for j in range(len(q)): 
                r.append(Fore.RED + Style.BRIGHT + L[i+j]+ Fore.BLACK + Style.RESET_ALL)
            i+=len(q)
        else:
            r.append(w) 
    return ' '.join(r)


print("Ready for input\n")
for query in fileinput.input():
    query_tokens = query[:-1].split(' ')
    print (green('QUERY: ') + query)
    f = find_quotes( query_tokens )
    #print(f)
    good_quotes = [get_dokument(i[0]) for i in f]
    good_quotes = [word_tokenize(x)for x in good_quotes]
    for quote in good_quotes: 
        print ('   ', my_highlight(query_tokens, quote))