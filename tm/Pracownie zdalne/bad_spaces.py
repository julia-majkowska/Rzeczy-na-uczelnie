import fileinput
from collections import defaultdict as dd 
from nltk.tokenize import word_tokenize
def read_prefixes():
    with open('prefixes.txt') as f:
        l = f.readlines()
        l = [x.split('	')[0][:-1] for x in l]
        return l
    return []
        
prefixes = read_prefixes()
print(prefixes)

def read_sufixes():
    with open('suffixes.txt') as f:
        l = f.readlines()
        l = [x[1:-1] for x in l]
        return l
    return []
        
sufixes = read_sufixes()
print(sufixes)
onegrams = {}
def read_trigramy():
    print("Reading_onegrams")
    x = 20
    y = 100
    with open('1grams') as f:
        l = f.readline()
        
        while l: 
            slowa =  word_tokenize(l)
            #print(slowa)
            if int(slowa[0])  < x or int(slowa[0]) >= y  : 
                onegrams[slowa[1]] = int(slowa[0])
            l= f.readline()
    print("Indexed 1 grams")
    with open('2grams') as f:
        with open('space_typos.txt', 'a') as out : 
            found = 0
            l = f.readline()
            while l: 
                slowa =  word_tokenize(l)
                twogram = slowa[1:]
                '''if int(slowa[0]) >= y :
                    #print(slowa[1])
                    #dwugram częsty może występuje rzadki jednogram dla niego który będzie błędem
                    if(not twogram[0] in prefixes) and (not twogram[1] in sufixes) and (twogram[0] + twogram[1]) in onegrams and onegrams[twogram[0] + twogram[1]] < x : 
                        out.write( twogram[0]+twogram[1] + " -> " + twogram[0] + " + " + twogram[1]+'\n')
                        print(twogram[0]+twogram[1] + " -> " + twogram[0] + " + " + twogram[1]+'\n')
                        found +=1'''
                if  int(slowa[0]) < x: 
                    #print(slowa[1])
                    # dwugram jest rzadki więc jednogram miałbybyć poprawny
                    if(twogram[0] + twogram[1]) in onegrams and twogram[1]!= '.' and onegrams[twogram[0] + twogram[1]] >= y: 
                        out.write(twogram[0] + " + " + twogram[1] + " -> " + twogram[0]+twogram[1]+'\n')
                        print(twogram[0]+' + ' + twogram[1] + " -> " + twogram[0] + twogram[1]+'\n')
                        found +=1
                if found >= 1e4:
                    break
                
                l= f.readline()
read_trigramy()