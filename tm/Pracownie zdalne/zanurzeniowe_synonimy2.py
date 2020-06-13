import re
import unicodedata
from gensim.models import KeyedVectors
from nltk.tokenize import word_tokenize
from nltk.tokenize import RegexpTokenizer
import numpy as np
model = KeyedVectors.load_word2vec_format("indeksy/wiki-forms-all-100-cbow-hs.txt", binary = False)
print("Model read")

def tokenize_word(word):
    w = re.split("\(| to | jest ", word)[0]
    start = 0
    end = len(w)
    #if [x for x in w if unicodedata.category(x)[0] == 'L'] == [] : 
    #    return w
    for i in range(len(w)):
        c = w[i]
        cat = unicodedata.category(c)[0]
        if cat == 'L' :
            start  = i 
            break
    
    after_int = []
    for i in range(len(w)-1, start+1, -1):
        #print(i)
        c = w[i]
        cat = unicodedata.category(c)[0]
        if cat == 'L' :
            end  = i 
            break
        after_int.append(w[i])
    if start < end :
        return w[start:end+1]
    return ""

def find_after_tell_tell(haslo, text) : 

    tell_tell = ["inna nazwa to", "inaczej zwane", "inne nazwy", "inne nazwy to", "zwany też", "zwane też"]
    
    indices= [i+len(tell) for i in range(len(text)) for tell in tell_tell  if text[i:].startswith(tell)]
    #print(haslo,  indices)
    all_syn = []
    for i in indices: 
        slowo = text[i:].split(".")[0]
        if len(re.split(":", slowo)) > 1 : 
            slowo = re.split(":", slowo)[1]
        blok_syn= re.split('\.|\;|\:|[|]|\-|–|\)|\/|\n|=| ref ', slowo)[0]
        my_syn = re.split(', | lub | i | oraz | albo | tudzież', blok_syn)
        good_syn = [tokenize_word(s).lower() for s in my_syn if not tokenize_word(s).lower().startswith(haslo)]
        all_syn += good_syn
    return all_syn

def immediate_syn_in_parenth(haslo, text) :
    slowo = re.split('\.|\:|\;|\-|–|[|]|\(\)|\/|\n|=| ref ', text)[0]
    cands = slowo.split('\'\'')
    if len(cands)<= 2 : 
        return []
    res = [tokenize_word(c).lower() for c in cands[1::2] if not tokenize_word(c).lower().startswith(haslo)]
    return res

def get_title_vector(title): 
    tokenizer = RegexpTokenizer(r'\w+')
    tokens= tokenizer.tokenize(title)
    title_vect = np.array([0.]*100)
    for t in tokens : 
        title_vect+= model.wv[t]
    return title_vect

def count_dist(va, vb): 
    if(vb in va) : 
        return 1e6
    try: 
        return np.linalg.norm(get_title_vector(va)-get_title_vector(vb))  <= epsilon
    except : 
        return 1e6
    
with open('poczatki_wikipediowe.txt') as f:
    with open ('zanurzeniowe_synonimy2.txt', 'a') as out : 
        linie = f.readlines()
        epsilon  = 15.
        tokenizer = RegexpTokenizer(r'\w+')
        for lines1, lines2, lines3 in zip(linie[::3], linie[1::3], linie[2::3]): 
            haslo = (lines1[4:].split('('))[0][:-1].lower()
            if(':' in haslo) : 
                continue
            res = find_after_tell_tell(haslo, lines2)
            res += immediate_syn_in_parenth(haslo, lines2)
            res = [tokenizer.tokenize(r)[0] for r in res if len(tokenizer.tokenize(r)) <=1 and len(tokenizer.tokenize(r)) > 0]
            res = list(set(res))
            try : 
                get_title_vector(haslo)
                res = [synonim for synonim in res if count_dist(haslo, synonim) <= epsilon and synonim != '']
                if res != [] : 
                    #print("%^###" + haslo)
                    #for sl in res : 
                    #    try: 
                    #        dist = np.linalg.norm(get_title_vector(haslo)-get_title_vector(sl))
                    #        print(sl, dist)
                    #    except: 
                    #        pass
                    print(haslo +" # "+' # '.join(res))
                    out.write(haslo +" # "+' # '.join(res) + '\n')
            except: 
                pass