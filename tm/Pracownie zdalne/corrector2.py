import fileinput
from collections import defaultdict as dd
from nltk.tokenize import word_tokenize
import editdistance
import heapq
keyboard = ['qwertyuiop[]', 'asdfghjkl;\'', '<zxcvbnm,./']
coords  = { keyboard[a][b] : (a, b) for a in range(len(keyboard)) for b in range(len(keyboard[a]))}
mistakes = [('ę', 'e'), ('u', 'ó'), ('ó', 'o'),('ą', 'a'), ('ś', 's'),('ł', 'l'), ('ł', 'u'), ('ż', 'z'), ('ź', 'z'), ('ch', 'h'), ('rz', 'ż'), ('ć', 'c'), ('ń', 'n')]
#mistakes = [('ę', 'e'), ('w', 'f'), ('t', 'd'), ('u', 'ó'), ('ó', 'o'), ('p', 'b'), ('ą', 'a'), ('ś', 's'), ('g', 'k'), ('j', 'i'), ('ł', 'l'), ('ł', 'u'), ('ż', 'z'), ('ź', 'x'), ('ch', 'h'), ('rz', 'ż'), ('ć', 'c'), ('ń', 'n')]
subst = dd(lambda: set())
for (a, b) in mistakes : 
    subst[a].add(b)
    subst[b].add(a)

def polskawa(w):
    zmiany = {'e' : 'ę', 'o' : 'ó', 'u':'ó',  'a': 'ą', 's': 'ś','l': 'ł', 'z': 'ż', 'ź': 'ż', 'x': 'ż', 'c':'ć', 'n': 'ń'}
    slowo = ''
    for l in w: 
        lit = l
        if lit in zmiany:
            lit = zmiany[lit]
        slowo = slowo + lit
    return slowo
    
def read_dictionary() :
    onegrams = dd(lambda: set())
    size_of_window = 4
    with open('polimorfologik-2.1.txt') as f : 
        l = f.readline()
        while l: 
            #slowa =  word_tokenize(l)
            slowa = l.split(';')[:2]
            slowa = [s.lower() for s in slowa]
            for i in range(len(slowa[1]) - size_of_window+1): 
                onegrams[polskawa(slowa[1][i:i+size_of_window])].add(slowa[1])
            for i in range(len(slowa[0]) - size_of_window+1): 
                onegrams[polskawa(slowa[0][i:i+size_of_window])].add(slowa[0])
                
            if  len(slowa[1])>=2 : 
                onegrams[slowa[1][0:2]].add(slowa[1])
            else: 
                onegrams[slowa[1][0]].add(slowa[1])
            if len(slowa[0]) >=2 :
                onegrams[slowa[0][0:2]].add(slowa[0])
            else:
                onegrams[slowa[0][0]].add(slowa[0])
            l= f.readline()
    return onegrams

onegrams = read_dictionary()
'''for l in onegrams.keys() : 
    onegrams[l] = sorted(onegrams[l], key = lambda x : len(x))
def read_dictionary() :
    onegrams = dd(lambda: set())#set()
    with open('1grams') as f : 
        l = f.readline()
        while l: 
            slowa =  word_tokenize(l)
            if int(slowa[0]) < 10: 
                break; 
            onegrams[slowa[1][0]] .add(slowa[1])
           # onegrams.add(slowa[1])
            l= f.readline()
    return onegrams

onegrams = read_dictionary()
for l in onegrams.keys() : 
    onegrams[l] = sorted(onegrams[l], key = lambda x : len(x))'''
keyboard = ['qwertyuiop[]', 'asdfghjkl;\'', 'zxcvbnm,./']
def letters_close(l1, l2) : 
    l1 = l1.lower()
    l2 = l2.lower()
    if l1 == l2 : 
        return 0
    if l2 in subst[l1] : 
        return 0.25
    surround = [(-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1) , (1, 0)]
    if not l1 in coords : 
        return 4
    i, j = coords[l1]
    for (i1, j1) in surround : 
        i2 = i1+i
        if i2 < 0 or i2 >= len(keyboard):
            continue
        j2 = j1+j 
        if j2 < 0 or j2 >= len(keyboard[i2]) :
            continue
        if keyboard[i2][j2] == l2: 
            return 2
    return 4

def addition_cost(l1, l2): 
    l1 = l1.lower()
    l2 = l2.lower()
    if l1 == l2 : 
        return 1
    if l2 in subst[l1] : 
        return 2
    surround = [(-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1) , (1, 0)]
    if not l1 in coords : 
        return 3
    i, j = coords[l1]
    for (i1, j1) in surround : 
        i2 = i1+i
        if i2 < 0 or i2 >= len(keyboard):
            continue
        j2 = j1+j 
        if j2 < 0 or j2 >= len(keyboard[i2]) :
            continue
        if keyboard[i2][j2] == l2: 
            return 2
    return 3
                    
def ed_dist(w1, w2) : #w1 słowo, w2 wzór
    w1 = '#' + w1
    w2 = '#' + w2
    dist = [[0]*len(w2) for i in w1]
    solution = [[[]]*len(w2) for i in w1]
    for i in range(len(w1)):
        for j in range(len(w2)): 
            
            #operacje wagi 1 - usuniecie, zmiana bliska
            dist[i][j] = 100000000000
            if i == 0 and j == 0 : 
                dist[i][j] = 0 
                continue
            if i > 0 and j > 0 and w1[i] == w2[j]: #litery sie zgadzają
                dist[i][j] = dist[i-1][j-1]
                solution[i][j] = solution[i-1][j-1]
                
            # usuniecie litery w w2 -( od tego bledu powstaje w1)
            if j > 0 : 
                operation_cost = 3
                if i == 1 : 
                    if dist[i][j] > dist[i][j-1] + operation_cost*2: 
                        dist[i][j] = min(dist[i][j], dist[i][j-1] + operation_cost*2)
                        solution[i][j] = solution[i][j-1] + ['delete ' + w2[j]] 
                    
                else : 
                    if dist[i][j] > dist[i][j-1] + operation_cost: 
                        dist[i][j] = min(dist[i][j], dist[i][j-1] + operation_cost)
                        solution[i][j] = solution[i][j-1] + ['delete ' + w2[j]] 
                    #dist[i][j] = min(dist[i][j], dist[i][j-1] + 1)
            
            # usunięce litery w w1
            if i > 0: 
                operation_cost = addition_cost(w1[i], w1[i-1])
                if i + 1 < len(w1): 
                    operation_cost = min(operation_cost, addition_cost(w1[i], w1[i+1]))
                if i == 1 : 
                    #dist[i][j] = min(dist[i][j], dist[i-1][j] + 2)
                    if dist[i][j] > dist[i-1][j] + operation_cost*2: 
                        dist[i][j] = min(dist[i][j], dist[i-1][j] + operation_cost*2)
                        solution[i][j] = solution[i-1][j] + ['add ' + w1[i]] 
                else : 
                    #dist[i][j] = min(dist[i][j], dist[i-1][j] + 1)
                    if dist[i][j] > dist[i-1][j] + operation_cost: 
                        dist[i][j] = min(dist[i][j], dist[i-1][j] + operation_cost)
                        solution[i][j] = solution[i-1][j] + ['add ' + w1[i]] 
                
            # zamiana litery
            if i > 0 and j > 0 : 
                operation_cost = letters_close(w1[i], w2[j]) 
                if operation_cost > 0 : 
                    if i == 1 or j == 1 : 
                        if dist[i][j] > dist[i-1][j-1] + operation_cost*2: 
                            dist[i][j] = min(dist[i][j], dist[i-1][j-1] + operation_cost*2)
                            solution[i][j] = solution[i-1][j-1] + ['swap ' + w1[i] + " na " + w2[j]] 
                        #dist[i][j] = min(dist[i][j], dist[i-1][j-1] + 2) #zamiana bliska na początku
                    else: 
                        if dist[i][j] > dist[i-1][j-1] + operation_cost: 
                            dist[i][j] = min(dist[i][j], dist[i-1][j-1] + operation_cost)
                            solution[i][j] = solution[i-1][j-1] + ['swap ' + w1[i] + " na " + w2[j]] 
                        #dist[i][j] = min(dist[i][j], dist[i-1][j-1] + 1) #zamiana bliska w srodku
                '''else : 
                    if i == 1 or j == 1 : 
                        #dist[i][j] = min(dist[i][j], dist[i-1][j-1] + 4) #zamiana daleka na początku
                        if dist[i][j] > dist[i-1][j-1] + 4: 
                            dist[i][j] = min(dist[i][j], dist[i-1][j-1] + 4)
                            solution[i][j] = solution[i-1][j-1] + ['swap ' + w1[i] + " na " + w2[j]] 
                    else: 
                       # dist[i][j] = min(dist[i][j], dist[i-1][j-1] + 2) #zamiana daleka w srodku
                       if dist[i][j] > dist[i-1][j-1] + 2: 
                            dist[i][j] = min(dist[i][j], dist[i-1][j-1] + 2)
                            solution[i][j] = solution[i-1][j-1] + ['swap ' + w1[i] + " na " + w2[j]] '''
                    
            #swap
            if i < 2 or j < 2 : 
                continue
            
            if w1[i] == w2[j-1] and w1[i-1] == w2[j] : 
                operation_cost = 2.25
                if i == 2 or j == 2 : 
                    #dist[i][j] = min(dist[i][j], dist[i-2][j-2] + 2) #swap na początku
                    if dist[i][j] > dist[i-2][j-2] + operation_cost*2: 
                            dist[i][j] = min(dist[i][j], dist[i-2][j-2] + operation_cost*2)
                            solution[i][j] = solution[i-2][j-2] + ['neighbour swap ' + w1[i] + " na " + w2[j]] 
                else: 
                    #dist[i][j] = min(dist[i][j], dist[i-2][j-2] + 1) #swap w srodku
                    if dist[i][j] > dist[i-2][j-2] + operation_cost: 
                            dist[i][j] = min(dist[i][j], dist[i-2][j-2] + operation_cost)
                            solution[i][j] = solution[i-2][j-2] + ['neighbour swap ' + w1[i] + " na " + w2[j]] 
            
            #swap z literką w środku
            if i < 3 or j < 3 : 
                continue
            if w1[i] == w2[j-2] and w1[i-2] == w2[j] and w1[i-1] == w2[j-1]: 
                operation_cost = 2.75
                if i == 3 or j == 3 : 
                    #dist[i][j] = min(dist[i][j], dist[i-3][j-3] + 2) #swap na początku
                    if dist[i][j] > dist[i-3][j-3] + operation_cost*2: 
                            dist[i][j] = min(dist[i][j], dist[i-3][j-3] + operation_cost*2)
                            solution[i][j] = solution[i-3][j-3] + ['next neighbour swap ' + w1[i] + " na " + w2[j]] 
                else: 
                    #dist[i][j] = min(dist[i][j], dist[i-3][j-3] + 1) #swap w srodku
                    if dist[i][j] > dist[i-3][j-3] + operation_cost: 
                            dist[i][j] = min(dist[i][j], dist[i-3][j-3] + operation_cost)
                            solution[i][j] = solution[i-3][j-3] + ['next neighbour swap ' + w1[i] + " na " + w2[j]] 
            
    #for i in range(len(dist)): 
    #    print(dist[i])
        #print(solution[i])
    #print(dist)
    #print(solution[len(w1)-1][len(w2)-1])
    return dist[len(w1)-1][len(w2)-1], solution[len(w1)-1][len(w2)-1]

def correct_word(word1, ans = '') :
    cands = []
    min_dist = 10000000000000000
    solution = ''
    size_of_window=4
    ans_in_search = False
    #for first_letter in onegrams.keys(): 
         #if first_letter.lower() == word1[0].lower() :  
         #if letters_close(first_letter.lower(), word1[0].lower())< 4: 
         #   for w in onegrams[first_letter] : 
    for i in range(len(word1) - size_of_window+1): 
        window = polskawa(word1[i:i+size_of_window])
        #print(window)
        for w in onegrams[window]: 
            if len(w) - len(word1) > 4: 
                continue
            if len(word1) - len(w) > 4:
                continue
            if w == ans: 
                ans_in_search = True
            dist = editdistance.eval(word1, w)
            heapq.heappush(cands, (-1*dist, w))
            if len(cands)>100 : 
                heapq.heappop(cands)
    for w in onegrams[word1[0:2]]: 
        if len(w) - len(word1) > 4: 
            continue
        if len(word1) - len(w) > 4:
            continue
        if w == ans: 
            ans_in_search = True
        dist = editdistance.eval(word1, w)
        heapq.heappush(cands, (-1*dist, w))
        if len(cands)>100 : 
            heapq.heappop(cands)
    cand = ''
    for dist, w in cands: 
        dist, sol = ed_dist(w, word1)
        #print(word1, w, dist)
        if dist < min_dist :
                    cand = w
                    #
                    min_dist = dist
                    solution = sol
    if not ans_in_search : 
        print("Nie mam w przesrzeni odpowiedzi " + word1 + " " + ans)
    return cand, solution
    
def validate_on_set() :
    print("Staring processing")
    good = 0
    total = 0
    all_errs = dd(lambda: 0)
    with open('literowki1.txt') as f: 
        l = f.readline()
        inum = 0
        while l : 
            data = l.split()
            query = data[1].lower()
            ans, sol = correct_word(query, data[0].lower())
            for s in sol : 
                all_errs[s] += 1
            print(data, ans) 
            if ans.lower() == data[0].lower() : 
                good += 1
            '''else: 
                print()
                print(ans.lower(),  data[0].lower())
                print()'''
            total +=1
            #break; 
            inum+=1
            #if inum > 20: 
            #    break; 
            l = f.readline()
        
        print((good/total)*100)
        for err in all_errs.keys():
            print(err + ": " + str(all_errs[err]))
    
validate_on_set()
#print(correct_word('prawomocnosć', 'prawomocność'))
'''wwwww = 'mezczysnz'
for i in range(len(wwwww) - 3): 
    okno = polskawa(wwwww[i:i+4])
    print(okno)
    
wwwww = 'mężczyzna'
for i in range(len(wwwww) - 3): 
    okno = polskawa(wwwww[i:i+4])
    print(okno)'''
#print(ed_dist('kalapea', 'kalarepa'))
#print(ed_dist('kalapea', 'kalaba'))
