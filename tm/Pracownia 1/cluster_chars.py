import unicodedata
from collections import defaultdict as dd 
import copy

cat = dd(lambda:[])
with open('znaki_wikipedii.txt') as f:
    for line in f.readlines():
        for r in line : 
            if r!= ' ' and r!= '\n':
                c = unicodedata.category(r)
                if c[0] == 'L':
                    c = c[0]
                cat[c].append(r)

        
standard_sep = 1
         
cluster_names = { "Mc" : "spacing combining", "Me": "enclosing" , "Mn" : "non-spacing", "Nd" : "decimal digit", "Nl" : "math letter", "No" : "number other", "Pc" : "punctuation conntector", "Pd" : "dash", "Pi" : "initial quote", "Pf" : "final_quote", "Ps" : "open bracket", "Pe" : "close bracket", "Po" : "punctuation other", "Sc" : "currency symbol", "Sk" : "symbol modifier", "Sm" : "math and relation symbol", "So" : "other_symbols", "Zl": "line separator", "Zp" : "paragraph separator", "Zs" : "space", "Cc" : "control", "Cf" : " format", "Cn" : "not assigned", "Co" : "private use", "Cs" : "surrogate"}
""" not assigned (Cn), private use (Co), surrogate (Cs)"""
for c in cat:
    if c[0] != 'L' :
        print (cluster_names[c].upper()+':', ' '.join(cat[c]))
        continue
    cat[c] = sorted(cat[c], key = ord)
    new_clusters = []
    last = ord(cat[c][0])
    cur_cluster = [] # rozmiary 50, 74, 76, 80
    langs = dd(lambda:[])
    for znak in cat[c] : 
        lang_type = unicodedata.name(znak).split(' ')[0]
        langs[lang_type].append(znak)
    '''
    for i in range(len(cat[c])): 
        car
        if ord(cat[c][i]) - last <= standard_sep : 
            cur_cluster.append((cat[c][i], hex(ord(cat[c][i])), unicodedata.name(cat[c][i])))
        else :
            new_clusters.append(copy.deepcopy(cur_cluster))
            cur_cluster = [(cat[c][i], hex(ord(cat[c][i])), unicodedata.name(cat[c][i]))]
        
        last = ord(cat[c][i])
        
    print (c+':')
    for clust in new_clusters: 
        print(clust)
    print(new_clusters)'''
    for lang in langs : 
        print (lang+':', ' '.join(langs[lang]))