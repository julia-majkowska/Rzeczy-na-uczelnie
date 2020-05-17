import psycopg2
from collections import defaultdict as dd 
from nltk.tokenize import word_tokenize
import json
import jsonpickle
import math

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
#Split po TITLE:

lemats_counter =  dd(lambda:0)
	
conn = psycopg2.connect("dbname=indeks user=julia")
cur = conn.cursor()
"print(connected);"
cur.execute(open("startup2.sql", "r").read())
    
def make_vect(query): 
    query_tokens = query[:-1].split(' ')
    vect = dd(lambda:0)
    for q in query_tokens:
        l = lemats[q]
        if len(l) == 0: 
            l = set[(q)]
        for ll in l : 
            vect[ll]+=1
    return vect 


with open('fp_wiki.txt', 'r') as f:
        i = 0
        line = f.readline()
        current_article=line
        lemats_doc_counter = dd(lambda:0)
        while line :
            
            if line.startswith("TITLE:"): 
                #print(i)
                for l in lemats_doc_counter.keys(): 
                    lemats_counter[l]+=1
                cur.execute('''INSERT INTO rare_lemat_vect(id, lemat_vect) VALUES(%s, %s)''', (i, jsonpickle.encode(lemats_doc_counter)))
                current_article = ""
                i+=1
                lemats_doc_counter = dd(lambda:0)
            current_article+=line
            words = word_tokenize(line)
            
            for w in words: 
                w= w.lower()
                lem = lemats[w]
                if len(lem) == 0:
                    lem = set(w)
                for l in lem:
                    lemats_doc_counter[l]+=1
            line = f.readline()
            
        log_total = math.log(i)
        for lem in lemats_counter.keys(): 
            cur.execute('''INSERT INTO lemat_idf(lemat, idf) VALUES(%s, %s)''', (lem, log_total - math.log(lemats_counter[lem])))
cur.close()
conn.commit()
        