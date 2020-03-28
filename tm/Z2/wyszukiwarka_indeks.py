import fileinput
from collections import defaultdict as dd 
from highlight import highlight2, green, yellow_line

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
def read_quotes_build_indeks():
    res = []
    indeks = dd(lambda:set())
    with open('tokenized_quotes.txt') as f:
        l = f.readline()
        i = 0
        while l:
            tokens = l.split(' ')
            res.append(tokens)
            for t in tokens : 
                lems = lemats[t]
                for lem in lems : 
                    indeks[lem].add(i)
            l= f.readline()
            i+=1
    return res, indeks

quotes, indeks = read_quotes_build_indeks()

def find_quotes(query_tokens) : 
    quote_indices= None
    for token in query_tokens: 
        lems = lemats[token]
        token_indices = set()
        for lem in lems: 
            token_indices = token_indices | indeks[lem]
        if quote_indices == None : 
            quote_indices = token_indices
        else : 
            quote_indices = quote_indices & token_indices
    return quote_indices