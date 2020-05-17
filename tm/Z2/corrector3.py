import fileinput
from collections import defaultdict as dd
from nltk.tokenize import word_tokenize
import sys 
  
# the setrecursionlimit function is 
# used to modify the default recursion 
# limit set by python. Using this,  
# we can increase the recursion limit 
# to satisfy our needs 
  
sys.setrecursionlimit(10**6) 

keyboard = ['qwertyuiop[]', 'asdfghjkl;\'', '<zxcvbnm,./']
coords  = { keyboard[a][b] : (a, b) for a in range(len(keyboard)) for b in range(len(keyboard[a]))}
letters = set()
def read_dictionary() :
    onegrams = set()
    with open('polimorfologik-2.1.txt') as f : 
        l = f.readline()
        while l: 
            #slowa =  word_tokenize(l)
            slowa = l.split(';')[:2]
            onegrams.add(slowa[1])
            onegrams.add(slowa[0])
            for l in slowa[1]: 
                letters.add(l)
            for l in slowa[0]: 
                letters.add(l)
            l= f.readline()
    return onegrams

onegrams = read_dictionary()

keyboard = ['qwertyuiop[]', 'asdfghjkl;\'', '<zxcvbnm,./']
coords  = { keyboard[a][b] : (a, b) for a in range(len(keyboard)) for b in range(len(keyboard[a]))}
mistakes = [('ę', 'e'), ('w', 'f'), ('t', 'd'), ('u', 'ó'), ('ó', 'o'), ('p', 'b'), ('ą', 'a'), ('ś', 's'), ('g', 'k'), ('j', 'i'), ('ł', 'l'), ('ł', 'u'), ('ż', 'z'), ('ź', 'x'), ('ch', 'h'), ('rz', 'ż')]
subst = dd(lambda: set())
for (a, b) in mistakes : 
    subst[a].add(b)
    subst[b].add(a)
def letters_close(l1, l2) : 
    l1 = l1.lower()
    l2 = l2.lower()
    if l1 == l2 : 
        return True
    if l2 in subst[l1] : 
        return True
    surround = [(-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1) , (1, 0)]
    if not l1 in coords : 
        return False
    i, j = coords[l1]
    for (i1, j1) in surround : 
        i2 = i1+i
        if i2 < 0 or i2 >= len(keyboard):
            continue
        j2 = j1+j 
        if j2 < 0 or j2 >= len(keyboard[i2]) :
            continue
        if keyboard[i2][j2] == l2: 
            return True
    return False
            
def generate_mists(word, cur_ops = [],  cur_cost = 0 , top_cost = 5) : 
    #generuje iteracyjnie słowa z najpopularniejszymi błędami, jak znajdzie w słowniku to zwraca tylko pierwszy hit a jak nie to zwraca całą listę
    results = []
    if word in onegrams : 
        results = [(word, cur_cost, cur_ops)]
    if cur_cost == top_cost : 
        return []
    #swap na inną literkę
    for i in range(len(word)): 
        for lit in letters: 
            slowo = word[:i] + lit + word[i+1:]
            if letters_close(word[i], lit) : 
                results+= generate_mists(slowo, cur_ops + ['zamiana ' + lit + ' na ' +  word[i]], cur_cost+1, top_cost)
            else: 
                results+= generate_mists(slowo, cur_ops + ['zamiana ' + lit + ' na ' +  word[i]], cur_cost+2, top_cost)
                
    
    #zjedzona literka
    for i in range(0, len(word), 1): 
        slowo = word[:i] + word[i+1:]
        results+=generate_mists(slowo, cur_ops + ['usuniecie ' + word[i]], cur_cost+1, top_cost)
            
            
    '''#orty ze zmianą liczby znaków
    mistakes = [('ę', 'e'), ('w', 'f'), ('t', 'd'), ('u', 'ó'), ('ó', 'o'), ('p', 'b'), ('ą', 'a'), ('ś', 's'), ('g', 'k'), ('j', 'i'), ('ł', 'l'), ('ł', 'u'), ('ż', 'z'), ('ź', 'x'), ('ch', 'h'), ('rz', 'ż')]
    subst = dd(lambda: set())
    for (a, b) in mistakes : 
        subst[a].add(b)
        subst[b].add(a)
    
    for i in range(len(word)): 
        for chars in subst[word[i]] : 
            slowo = word[:i] + chars + word[i+1:]
            results +=generate_mists(slowo, cur_ops + ['zamiana ' + chars + 'na' +  word[i]], cur_cost+1, top_cost)
                
    for i in range(len(word)-1): 
        for chars in subst[word[i]+word[i+1]] : 
            slowo = word[:i] + chars + word[i+2:]
            results +=generate_mists(slowo, cur_ops + ['zamiana ' + chars + 'na' +  word[i]], cur_cost+1, top_cost)'''
    
    #swap sąsiedni
    for i in range(len(word) -1) : 
        slowo = word[:i] + word[i+1] + word[i] + word[i+2:]
        results+=generate_mists(slowo, cur_ops + ['zamiana miejsc sasiednia'], cur_cost+1, top_cost)
        
    # podwójna literka
    for i in range(len(word)) : 
        slowo = word[:i] + word[i] + word[i] + word[i+1:]
        results+=generate_mists(slowo, cur_ops + ['podwojona litera'], cur_cost+1, top_cost)
            
    if top_cost - cur_cost >=1:  
        # swap z literką w środku
        for i in range(len(word)-2) : 
            slowo = word[:i] + word[i+2] + word[i+1] + word[i] + word[i+3:]
            results+=generate_mists(slowo, cur_ops + ['zamiana miejsc z litera w srodku'], cur_cost+2, top_cost)
            
        # dodanie dowolnej litery
        for i in range(len(word)) :
            for lit in letters: 
                slowo = word[:i+1] + lit + word[i+1:]
                results+=generate_mists(slowo, cur_ops + ['dodana litera ' + lit], cur_cost+2, top_cost)

    return results

def correct_word(w1) : 
    ans = generate_mists(w1) 
    if len(ans) == 1: 
        return ans
    else :
        return w1
    
def validate_on_set() : 
    print("Begin validating")
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