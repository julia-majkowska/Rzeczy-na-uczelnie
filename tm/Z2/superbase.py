import fileinput
from collections import defaultdict as dd 
from highlight import highlight2, green, yellow_line
from wyszukiwarka_indeks import lemats
from nltk.tokenize import word_tokenize

superbase = {s:(s,1) for s in lemats.keys()}
def find(s1):
    if s1 not in superbase.keys(): 
        superbase[s1] = (s1, 1)
    if superbase[s1][0] == s1:
        return s1
    base = find(superbase[s1][0])
    base, size = superbase[base]
    superbase[s1] = (base, size)
    return base
        
def Union(s1, s2): 
    base1, size1 = superbase[find(s1)]
    base2, size2 = superbase[find(s2)]
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

make_superbase()

base_mapping = dd(lambda:[])

def match_tokens(query_tok, text_tok): 
    a = lemats[query_tok]
    b = lemats[text_tok]
    intersec = a.intersection(b)
    return len(intersec) != 0

def bad_match(t1, t2): 
    if len(t1) != len(t2): 
        return True
    
    for i in range(len(t1)): 
        if t1[i]!= t2[i] and not match_tokens(t1[i], t2[i]): 
            #print("Zły match na " + str(t1[i]) + ", " + str(t2[i]))
            return True
    return False


def read_trigramy():
    k = 5000
    with open('2grams') as f:
        with open('bad2grams.txt', 'a') as out: 
            l = f.readline()
            i = 0
            while l: 
                #print(l)
                #
                slowa =  word_tokenize(l)
                #print(int(slowa[0]))
                if(int(slowa[0]) < k) : 
                    break
                tokeny = slowa[1:]
                supertokeny = tuple([find(t) for t in tokeny])
                for inne_tokeny in base_mapping[supertokeny] : 
                    if bad_match (tokeny, inne_tokeny) : 
                        out.write(str(supertokeny) + ": " + str(tokeny) + ' ' + str(inne_tokeny) + '\n')
                base_mapping[supertokeny].append(tokeny)
                l= f.readline()
                i+=1
    print(i)
read_trigramy()