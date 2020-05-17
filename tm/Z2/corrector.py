import fileinput
from collections import defaultdict as dd
from nltk.tokenize import word_tokenize
import editdistance
keyboard = ['qwertyuiop[]', 'asdfghjkl;\'', '<zxcvbnm,./']
coords  = { keyboard[a][b] : (a, b) for a in range(len(keyboard)) for b in range(len(keyboard[a]))}

def read_dictionary() :
    onegrams = {}
    with open('1grams') as f : 
        l = f.readline()
        while l: 
            slowa =  word_tokenize(l)
            if int(slowa[0]) < 50: 
                break; 
            onegrams[slowa[1]] = int(slowa[0])
            l= f.readline()
    return onegrams

onegrams = read_dictionary()
            
def generate_mists(word, cur_cost = 0 , top_cost = 5) : 
    #generuje iteracyjnie słowa z najpopularniejszymi błędami, jak znajdzie w słowniku to zwraca tylko pierwszy hit a jak nie to zwraca całą listę
    hits = []
    misses = []
    #swap na obok na klawiaturze
    surround = [(1, 0), (0, 1), (-1, 1), (-1, 0), (0, -1) , (1, -1)]

    for i in range(0, len(word), 1): 
        if word[i] in coords : 
            (a1, b1) = coords[word[i]]
            for (b, a) in surround : 
                if a+a1 < 0 or a+a1 >= len(keyboard) :
                    continue
                if b+b1 < 0 or b+b1 >= len(keyboard[a]) : 
                    continue
                lit = keyboard[a+a1][b+b1]
                slowo = word[:i] + lit + word[i+1:]
                if slowo in onegrams : 
                    hits.append((slowo, onegrams[slowo]))
                else : 
                    misses.append(slowo)
    
    #zjedzona literka
    for i in range(0, len(word), 1): 
        slowo = word[:i] + word[i+1:]
        if slowo in onegrams : 
            hits.append((slowo, onegrams[slowo]))
        else : 
            misses.append(slowo)
            
            
    #nie wcisniety ctrl i orty
    mistakes = [('ę', 'e'), ('w', 'f'), ('t', 'd'), ('u', 'ó'), ('ó', 'o'), ('p', 'b'), ('ą', 'a'), ('ś', 's'), ('g', 'k'), ('j', 'i'), ('ł', 'l'), ('ł', 'u'), ('ż', 'z'), ('ź', 'x'), ('ch', 'h'), ('rz', 'ż')]
    subst = dd(lambda: set())
    for (a, b) in mistakes : 
        subst[a].add(b)
        subst[b].add(a)
    
    for i in range(len(word)): 
        for chars in subst[word[i]] : 
            slowo = word[:i] + chars + word[i+1:]
            if slowo in onegrams : 
                hits.append((slowo, onegrams[slowo]))
            else : 
                misses.append(slowo)
                
    for i in range(len(word)-1): 
        for chars in subst[word[i]+word[i+1]] : 
            slowo = word[:i] + chars + word[i+2:]
            if slowo in onegrams : 
                hits.append((slowo, onegrams[slowo]))
            else : 
                misses.append(slowo)
    
    #swap sąsiedni
    for i in range(len(word) -1) : 
        slowo = word[:i] + word[i+1] + word[i] + word[i+2:]
        if slowo in onegrams : 
            hits.append((slowo, onegrams[slowo]))
        else : 
            misses.append(slowo)
        
    # podwójna literka
    for i in range(len(word)) : 
        slowo = word[:i] + word[i] + word[i] + word[i+1:]
        if slowo in onegrams : 
            hits.append((slowo, onegrams[slowo]))
        else : 
            misses.append(slowo)
            
    # swap z literką w środku
    for i in range(len(word)-2) : 
        slowo = word[:i] + word[i+2] + word[i+1] + word[i] + word[i+3:]
        if slowo in onegrams : 
            hits.append((slowo, onegrams[slowo]))
        else : 
            misses.append(slowo)
        
    if len(hits) > 0 : 
        hits = sorted(hits, key = lambda x: x[1], reverse = True)
        return [hits[0][0]]
    else :
        return misses

def correct_word(w1) : 
    ans = generate_mists(w1) 
    if len(ans) == 1: 
        return ans
    else :
        return w1
    
def validate_on_set() : 
    good = 0
    total = 0
    with open('literowki1.txt') as f: 
        l = f.readline()
        while l : 
            data = l.split()
            query = data[1].lower()
            ans = correct_word(query)
            print(data, ans) 
            if ans == data[0].lower() : 
                good += 1
            total +=1
            l = f.readline()
        
        print((good/total)*100)
            
validate_on_set()