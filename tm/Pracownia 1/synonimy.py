from nltk.tokenize import word_tokenize
import unicodedata
import re

def remove_extra_punct(w) :
    start = 0
    end = len(w)
    for i in range(len(w)):
            #print(i)
            c = w[i]
            cat = unicodedata.category(c)[0]
            if cat != 'P' :
                start  = i 
                break
            
    for i in range(len(w)-1, 0, -1):
        #print(i)
        c = w[i]
        cat = unicodedata.category(c)[0]
        if cat != 'P' :
            end  = i 
            break
    if start < end :
        return w[start:end+1]
    return w
    
def tokenize(text):
    words = text.split(' ')
    #print (words[:3])
    fixed_words = []
    for w in words:
        start = 0
        end = len(w)
        #print(w, len(w))
        for i in range(len(w)):
            #print(i)
            c = w[i]
            cat = unicodedata.category(c)[0]
            if cat != 'P' :
                start  = i 
                break
            
        for i in range(len(w)-1, 0, -1):
            #print(i)
            c = w[i]
            cat = unicodedata.category(c)[0]
            if cat != 'P' :
                end  = i 
                break
        if start < end :
            #print ( w, start, end )
            fixed_words.append(w[start:end+1])
    return fixed_words

def find_words_in_par(text): 
    words = text.split('\'\'')
    return [remove_extra_punct(words[i]) for i in range(1, len(words), 2)]
        
    
with open('poczatki_wikipediowe.txt') as f:
    lines = [ x for x in f.readlines() if x != "\n" ]
    
    for i in range(0, len(lines)-1, 2): 
        #print(lines[i])
        haslo = (lines[i][4:].split('('))[0][:-1].lower()
        new_text = lines[i+1].lower()
        i = new_text.find("inne nazwy")
        if i == -1:
            continue
        res = find_words_in_par(new_text[i:].split('.')[0])
        if res!= [] : 
            print(haslo +" # "+' # '.join(res) + "\n")
            continue
        
        other_part = re.split(':|\=', new_text[i:].split('.')[0])
        if len( other_part) == 1 : 
            other_part = new_text[i:].split('.')[0].split('to')
            
        if len( other_part) == 1:
            continue
        part= re.split('\.|\;|\:|[|]\- |\(|\)|\/|\n', other_part[1])
        res = re.split(', | lub | i | oraz ', part[0])
        
        #print(part)
        #if part[0] != "":
        #    print(haslo + ": "+ new_text[i:]+ "\n"+part[0])
        #print(haslo)
        #d = lines[i+1].split('. | \|')
        #print(lines[i+1])
        
        '''res = [w for w in find_words_in_par(d[0]) if w.lower() != haslo]'''
        if res!= [] : 
            
            print(haslo +" # "+' # '.join(res) + "\n")
        
    '''for line in f.readlines():
        r1 = tokenize(line[:-1])
        r2 = word_tokenize(line)
        print(r1)
        print(r2)'''