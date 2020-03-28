import fileinput
from collections import defaultdict as dd 
from highlight import highlight2, green, yellow_line
from wyszukiwarka_indeks import lemats
supersuperbase = {s:(s,1) for s in lemats.keys()}
def find(s1):
    if superbase[s1][0] == s1
        return s1
    base = find(superbase[s1][0])
    base, size = superbase[base]
    superbase[s1] = (base, size)
    return base
        
def Union(s1, s2): 
    base1, size1 = supersuperbase[find(s1)]
    base2, size2 = supersuperbase[find(s2)]
    if(size1 > size2) : 
        superbase[base2] = (base1, size2)
        superbase[base1] = (base1, size2+size1)
    else :
        superbase[base1] = (base2, size1)
        superbase[base2] = (base2, size1+size2)
    
    
def make_superbase():
    for slowo in lemats.keys(): 
        for l in lemats[slowo]: 
            Union(slowo, l)
    
def read_tri