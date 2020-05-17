
import fileinput
from collections import defaultdict as dd 
from highlight import highlight2, green, yellow_line
from nltk.tokenize import word_tokenize
import json
import jsonpickle
import psycopg2

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
    
def find_quotes(query_tokens) : 
    quote_indices= None
    for token in query_tokens: 
        lems = lemats[token]
        token_indices = set()
        for lem in lems: 
            token_indices = token_indices | get_indeks(lem)
        if quote_indices == None : 
            quote_indices = token_indices
        else : 
            quote_indices = quote_indices & token_indices
    return quote_indices

def match_tokens(query_tok, text_tok): 
    a = lemats[query_tok.lower()]
    b = lemats[text_tok.lower()]
    intersec = a.intersection(b)
    return len(intersec) != 0
    
def rank_document(query_tok, tekst): 
    goodness = 0 # *5 match w tytule razy 2 match dokładn
    lines = tekst.split("\n")
    title_tok = word_tokenize(lines[0])[2:]
    for tt in title_tok: 
        for qt in query_tok: 
            if qt == tt : 
                goodness+=10
            elif match_tokens(tt, qt): 
                goodness+=5
    
    for i in range(1, len(lines), 1) : 
        line_tok = word_tokenize(lines[i])
        for lt in line_tok: 
            for qt in query_tok: 
                if qt == lt : 
                    goodness+=2
                elif match_tokens(qt, lt): 
                    goodness+=1
                
    return goodness

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
    query_tokens = query[:-1].split(' ')
    print (green('QUERY: ') + query)
    good_quotes = [get_dokument(i) for i in find_quotes( query_tokens )]
    good_quotes = [word_tokenize(x) for x in sorted(good_quotes, key = lambda x : rank_document(query_tokens, x), reverse = True)]
    for quote in good_quotes: 
        print ('   ', my_highlight(query_tokens, quote))