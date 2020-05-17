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

#lemats = read_lemats()
#Split po TITLE:

s_indeks_norm = 0
s_indeks_vb8 = 0
s_indeks_vb4 = 0
last_gamma = dd(lambda:0)
s_gamma = dd(lambda:0)

last_indeks =  dd(lambda:0)

with open('fp_wiki.txt', 'r') as f:
        i = 0
        line = f.readline()
        current_article=line
        while line :
            #print(line)
            if line.startswith("TITLE:"): 
                current_article = ""
                i+=1
            current_article+=line
            words = line.split()
            for w in words: 
                w= w.lower()
                difference = i - last_indeks[w]
                s_indeks_norm+= 32
                binary = bin(difference)[2:] 
                num_bits = len(binary)
                s_gamma[w] +=num_bits*2+1
                s_indeks_vb4 += math.ceil(num_bits/3) *4
                s_indeks_vb8 += math.ceil(num_bits/7) *8
                last_indeks[w] = i
            line = f.readline()
        ss_gamma = 0
        for i in s_gamma.keys() : 
            s = s_gamma[i]
            if s % 8 ==0 : 
                ss_gamma+= s
            else : 
                ss_gamma+= s+ 8 - s%8
        print(s_indeks_norm, s_indeks_vb8, s_indeks_vb4, ss_gamma)

        