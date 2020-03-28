import re
import unicodedata

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
    
with open('poczatki_wikipediowe.txt') as f:
    linie = f.readlines()
    for lines1, lines2, lines3 in zip(linie[::3], linie[1::3], linie[2::3]): 
        haslo = (lines1[4:].split('('))[0][:-1].lower()
        
        res = find_after_tell_tell(haslo, lines2)
        res += immediate_syn_in_parenth(haslo, lines2)
        res = list(set(res))
        if res != [] : 
            print(haslo +" # "+' # '.join(res) + "\n")