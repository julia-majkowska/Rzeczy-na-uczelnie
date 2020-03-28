import psycopg2
from collections import defaultdict as dd 
from nltk.tokenize import word_tokenize
import json
import jsonpickle

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

indeks =  dd(lambda:set())
	
conn = psycopg2.connect("dbname=indeks user=julia")
cur = conn.cursor()
"print(connected);"
cur.execute(open("startup.sql", "r").read())

with open('fp_wiki.txt', 'r') as f:
        i = 0
        line = f.readline()
        current_article=line
        while line :
            #print(line)
            if line.startswith("TITLE:"): 
                #print(i)
                cur.execute('''INSERT INTO articles(id, content) VALUES(%s, %s)''', (i, current_article))
                current_article = ""
                i+=1
            current_article+=line
            words = word_tokenize(line)
            for w in words: 
                w= w.lower()
                lem = lemats[w]
                for l in lem: 
                    indeks[l].add(i)
            line = f.readline()
            
        for lem in indeks.keys(): 
            cur.execute('''INSERT INTO postlist(lemat, indeks) VALUES(%s, %s)''', (lem, jsonpickle.encode(indeks[lem])))
cur.close()
conn.commit()
        