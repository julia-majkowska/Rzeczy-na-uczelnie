
import fileinput
from collections import defaultdict as dd 
from highlight import highlight2, green, yellow_line
from nltk.tokenize import word_tokenize
import json
import jsonpickle
import psycopg2

def read_dictionary() :
    titles = dd(lambda: set())
    artykuly = {}
    title_cont = {}
    size_of_window = 5
    with open('fp_wiki.txt', 'r') as f:
        first_line = ""
        i = 0
        line = f.readline()
        current_article=line
        while line :
            if line.startswith("TITLE:"): 
                #artykuly[i] = current_article
                current_article = ""
                i+=1
                title_cont[i] = line
                '''
                for ii in range(len(line) - size_of_window+1): 
                    titles[polskawa(line)[ii:ii+size_of_window]].add(i)
                if  len(line)>=2 : 
                    titles[line[0:2]].add(i)
                else: 
                    titles[line[0]].add(i)
        
            current_article+=line'''
            line = f.readline()
            
    #return titles, artykuly, title_cont
    return title_cont

#onegrams, articles, title_content = read_dictionary()
title_content = read_dictionary()

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

def get_indeks(slowo): 
    cur = conn.cursor()
    cur.execute('''SELECT indeks FROM postlist where lemat = \'%s\''''%slowo)
    lista = cur.fetchall()
    #print(lista)
    cur.close()
    conn.commit()
    return jsonpickle.decode(lista[0][0])

def get_dokument(indeks): 
    cur = conn.cursor()
    cur.execute('''SELECT content FROM articles where id = \'%s\''''%indeks)
    dokument = cur.fetchall()
    cur.close()
    conn.commit()
    return dokument[0][0]

def get_idf(lemat): 
    cur = conn.cursor()
    if lemat[-1] == '\'': 
        return 1
    cur.execute('''SELECT idf FROM lemat_idf where lemat = \'%s\''''%lemat)
    dokument = cur.fetchall()
    cur.close()
    conn.commit()
    return float(dokument[0][0])

def get_vector(doc_id): 
    cur = conn.cursor()
    cur.execute('''SELECT lemat_vect FROM rare_lemat_vect where id = \'%s\''''%doc_id)
    lista = cur.fetchall()
    #print(lista)
    cur.close()
    conn.commit()
    return jsonpickle.decode(lista[0][0])
    
def find_cands(query_tokens, K = 10) : 
    quote_indices= None
    lemats_count = set()
    for token in query_tokens: 
        lems = lemats[token]
        if len(lems) == 0: 
            lemd = [token]
        token_indices = set()
        for lem in lems: 
            lemats_count.add(lem)
            
    lemats_count = sorted([(lem, get_indeks(lem)) for lem in lemats_count], key = lambda x : len(x[1]))
    cand_docs = set()
    for lem, docs in lemats_count: 
        cand_docs|= set(docs)
        if len(cand_docs) >= K : 
            break
    return cand_docs

def len_vector(x) : 
    lenv = 0
    for key in x.keys():
        lenv+= (x[key]*get_idf(key))**2
    return lenv

def rare_cosine(v_query, v2): 
    len2 = len_vector(v2)
    common_lemats = set(v_query.keys())&set(v2.keys())
    res = 0
    for l in common_lemats: 
        res+=v_query[l]*v2[l]
    return res/len2

def closest_K_document(query_doc_id):
    v_query = get_vector(query_doc_id)
    query_toks = word_tokenize(get_dokument(query_doc_id))
    K = 10
    candidates = find_cands(query_toks, K)
    print(candidates)
    if len(candidates) <= K : 
        return candidates
    
    my_vects = sorted([(i, rare_cosine(v_query, get_vector(i))) for i in candidates], key = lambda x: x[1], reverse = True)
    return [i[0] for i in my_vects[:10]]

def match_tokens(query_tok, text_tok): 
    a = lemats[query_tok.lower()]
    b = lemats[text_tok.lower()]
    intersec = a.intersection(b)
    return len(intersec) != 0

def my_highlight(q, L): 
    
    last_dot = 0
    first_dot = 0
    found = False
    found2 = False
    for i in range(len(L)): 
        if '.' in L[i] : 
            if not found : 
                first_dot = i
            elif found2 : 
                last_dot = i
            found2 = False
            continue
        for qt in q : 
            if match_tokens(L[i], qt) : 
                found = True
                found2 = True
    print(first_dot, last_dot)
    return highlight2(q, L[first_dot+1:last_dot+1], lambda x, y :match_tokens(x, y))


print("Ready for input\n")
for query in fileinput.input():
    matched = False
    for i in title_content.keys(): 
        if query.lower() in title_content[i].lower(): 
            matched = True
            print("Found a matched title")
            print(get_dokument(i))
            close_docs = closest_K_document(i)
            for doc_id in close_docs : 
                print(get_dokument(doc_id))
            print(close_docs)
            break
    
    if matched == False : 
        print(":(")
    '''query_tokens = query[:-1].split(' ')
    print (green('QUERY: ') + query)
    good_quotes = [get_dokument(i) for i in find_quotes( query_tokens )]
    good_quotes = [word_tokenize(x) for x in sorted(good_quotes, key = lambda x : rank_document(query_tokens, x), reverse = True)]
    for quote in good_quotes: 
        print ('   ', my_highlight(query_tokens, quote))'''