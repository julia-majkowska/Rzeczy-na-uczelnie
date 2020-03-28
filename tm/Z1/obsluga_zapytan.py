import fileinput
from collections import defaultdict as dd 
from highlight import highlight2, green, yellow_line

from wyszukiwarka_indeks import lemats, quotes, indeks, find_quotes

def match_tokens(query_tok, text_tok): 
    a = lemats[query_tok]
    b = lemats[text_tok]
    intersec = a.intersection(b)
    return len(intersec) != 0
    

def my_highlight(q, L): 
    return highlight2(q, L, lambda x, y :match_tokens(x, y))


print("Ready for input\n")
for query in fileinput.input():
    query_tokens = query[:-1].split(' ')
    print (green('QUERY: ') + query)
    good_quotes = [quotes[i] for i in find_quotes( query_tokens )]
    for quote in good_quotes: 
        print ('   ', my_highlight(query_tokens, quote))