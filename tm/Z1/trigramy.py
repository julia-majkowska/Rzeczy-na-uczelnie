import fileinput
from collections import defaultdict as dd 
from highlight import highlight2, green, yellow_line
from wyszukiwarka_indeks import lemats, quotes, indeks, find_quotes
    
def make_trigram(): 
    trigrams = dd(lambda:[])
    with open('przypadkowe_trigramy.txt') as f:
        l = f.readline()
        while l: 
            words = l[:-1].split(' ')
            good_quotes = find_quotes(words)
            trigrams[tuple(sorted(good_quotes))].append(l)
            l= f.readline() 
    return trigrams

tr = make_trigram()
with open('charakterystyki_trigramow.txt', 'a') as f:

    for value in tr.values():
        for v in value: 
            f.write(v)
        f.write('\n')