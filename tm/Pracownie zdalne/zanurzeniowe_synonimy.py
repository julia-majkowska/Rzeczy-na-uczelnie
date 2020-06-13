import re
import unicodedata
from nltk.tokenize import word_tokenize
from nltk.tokenize import RegexpTokenizer
import numpy as np
import itertools
from gensim.models import KeyedVectors

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
    tokenizer = RegexpTokenizer(r'\w+')
    all_syn = []
    for i in indices: 
        slowo = text[i:].split(".")[0]
        if len(re.split(":", slowo)) > 1 : 
            slowo = re.split(":", slowo)[1]
        blok_syn= re.split('\.|\;|\:|[|]|\-|–|\)|\/|\n|=| ref ', slowo)[0]
        my_syn = re.split(', | lub | i | oraz | albo | tudzież', blok_syn)
        good_syn = [tokenizer.tokenize(s) for s in my_syn if not tokenize_word(s).startswith(haslo)]
        all_syn += list(itertools.chain.from_iterable(good_syn))
    return all_syn

def in_bracket(text): 
    znawiasowane= re.split('\)|\( ', text)[1::2]
    tokenizer = RegexpTokenizer(r'\w+')
    a = [tokenizer.tokenize(x) for x in znawiasowane]
    return list(itertools.chain.from_iterable(a))

def in_parenth(text): 
    znawiasowane= re.split('\"', text)[1::2]
    tokenizer = RegexpTokenizer(r'\w+')
    a = [tokenizer.tokenize(x) for x in znawiasowane]
    return list(itertools.chain.from_iterable(a))
    
def after_hyphen(text): 
    znawiasowane= re.split('\"', text)[1::2]
    tokenizer = RegexpTokenizer(r'\w+')
    return [tokenizer.tokenize(x)[0] for x in znawiasowane]

def get_title_vector(title): 
    tokenizer = RegexpTokenizer(r'\w+')
    tokens= tokenizer.tokenize(title)
    title_vect = np.array([0.]*100)
    for t in tokens : 
        title_vect+= model.wv[t]
    return title_vect

print("Podobieństwa")
#print(np.linalg.norm(model.wv['postulat']-model.wv['aksjomat']))
#print(np.linalg.norm(model.wv['księgowanie']-model.wv['kronikowanie']))
with open('poczatki_wikipediowe.txt') as f:
    epsilon = 5.
    with open('vectorowe_synonimy.txt', 'a') as out : 
        linie = f.readlines()
        i  = 0
        for lines1, lines2, lines3 in zip(linie[::3], linie[1::3], linie[2::3]): 
            i+=1
            #if (i > 10) : break
            haslo = (lines1[4:].split('(')[0])[:-1].lower()
            #if len(haslo.split(' ')) > 1 : 
            #    continue
            lines2 = lines2.lower()
            res = [] 
            try : 
                haslo_vect = get_title_vector(haslo)
                cands = find_after_tell_tell(haslo, lines2)
                cands += in_parenth(lines2)
                cands += in_bracket(lines2)
                cands += after_hyphen(lines2)
                cands = list(set(cands))
                #print(haslo, cands)
                
                for cand in cands: 
                    try : 
                        dist = np.linalg.norm(model.wv[cand]-haslo_vect)
                        if not (cand in haslo) and dist< epsilon : 
                            res.append(cand)
                        #print(haslo, cand, dist )
                    except: 
                        pass
                if len(res) > 0 : 
                    out.write(haslo + ": " + ", ".join(res)+ "\n")
                    print(haslo + ": " + ", ".join(res))
            except: 
                pass
            