import unicodedata
from nltk.tokenize import word_tokenize
from keras.preprocessing.text import text_to_word_sequence

def tokenize(text):
    words = text.split(' ')
    #print (words[:3])
    fixed_words = []
    for w in words:
        start = 0
        end = len(w)
        if [x for x in w if unicodedata.category(x)[0] != 'P'] == [] : 
            fixed_words.append(w)
            continue
        for i in range(len(w)):
            c = w[i]
            cat = unicodedata.category(c)[0]
            if cat != 'P' :
                start  = i 
                break
            fixed_words.append(w[i])
        
        after_int = []
        for i in range(len(w)-1, start+1, -1):
            #print(i)
            c = w[i]
            cat = unicodedata.category(c)[0]
            if cat != 'P' :
                end  = i 
                break
            after_int.append(w[i])
        if start < end :
            fixed_words.append(w[start:end+1])
        fixed_words+= after_int
    return fixed_words

def print_diff(tok1, tok2): 
    size1 = 0
    size2 = 0
    curdif1 = []
    curdif2 = []
    i = 0
    j = 0
    while i < len(tok1) and j < len(tok2) : 
        if size1 > size2 : 
            curdif2.append(tok2[j])
            size2 += len(tok2[j])
            j+=1
        elif size1 < size2: 
            curdif1.append(tok1[i])
            size1 += len(tok1[i])
            i+=1
        else:
            if curdif1 != curdif2 :
                print("\n")
                print(curdif1)
                print(curdif2)
            curdif1 = []
            curdif2 = []
            size1+= len(tok1[i])
            size2+= len(tok2[j])
            curdif1.append(tok1[i])
            curdif2.append(tok2[j])
            j+=1
            i+=1
            
            

with open('cytaty.txt') as f:
    for line in f.readlines()[:5]:
        r1 = tokenize(line[:-1])
        r2 = word_tokenize(line)
        r3 = text_to_word_sequence(line, filters='!"#$%&()*+,-./:;<=>?@[\\]^_`{|}~\t\n', lower=True, split=' ')
        #print_diff(r1, r2)
        print(r1)
        print("#####")
        print(r2)
        print("#####")
        print(r3)
        