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
            #if len(res[words[1]]) > 1:
            #    print( words[1]+ ": " + str(res[words[1]]))
            l= f.readline()
    return res

def read_and_tokenize_quotes():
    res = []
    with open('tokenized_quotes.txt') as f:
        l = f.readline()
        while l:
            res.append(l.split(' '))
            l= f.readline()
    return res

lemats = read_lemats()
#print(lemats)
quotes = read_and_tokenize_quotes()

def match_tokens(query_tok, text_tok): 
    a = lemats[query_tok]
    b = lemats[text_tok]
    intersec = a.intersection(b)
    return len(intersec) != 0
    

def my_highlight(q, L): 
    return highlight2(q, L, lambda x, y :match_tokens(x, y))

def search

for query in fileinput.input():
    query_tokens = query[:-1].split(' ')
    print (green('QUERY: ') + query)
    for quote in quotes: 
        good = True
        for tok in query_tokens : 
            good_tok = False
            for quot_tok in quote : 
                if match_tokens(tok, quot_tok) : 
                    good_tok = True
            if good_tok == False:
                good = False
                break
        if good : 
            #print (quote)
            print ('   ', my_highlight(query_tokens, quote))
            
#print(lemtas)