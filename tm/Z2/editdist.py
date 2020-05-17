import fileinput
from collections import defaultdict as dd
from nltk.tokenize import word_tokenize
import editdistance
import heapq
keyboard = ['qwertyuiop[]', 'asdfghjkl;\'', '<zxcvbnm,./']
coords  = { keyboard[a][b] : (a, b) for a in range(len(keyboard)) for b in range(len(keyboard[a]))}
mistakes = [('ę', 'e'), ('w', 'f'), ('t', 'd'), ('u', 'ó'), ('ó', 'o'), ('p', 'b'), ('ą', 'a'), ('ś', 's'), ('g', 'k'), ('j', 'i'), ('ł', 'l'), ('ł', 'u'), ('ż', 'z'), ('ź', 'x'), ('ch', 'h'), ('rz', 'ż'), ('ć', 'c'), ('ń', 'n')]
subst = dd(lambda: set())
for (a, b) in mistakes : 
    subst[a].add(b)
    subst[b].add(a)

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
                operation_cost = 2
                if i == 1 : 
                    if dist[i][j] > dist[i][j-1] + operation_cost*2: 
                        dist[i][j] = min(dist[i][j], dist[i][j-1] + operation_cost*2)
                        solution[i][j] = solution[i][j-1] + ['delete ' + w2[j] + ' ' + str(i)+str(j)] 
                    
                else : 
                    if dist[i][j] > dist[i][j-1] + operation_cost: 
                        dist[i][j] = min(dist[i][j], dist[i][j-1] + operation_cost)
                        solution[i][j] = solution[i][j-1] + ['delete ' + w2[j] + ' ' + str(i)+str(j)] 
                    #dist[i][j] = min(dist[i][j], dist[i][j-1] + 1)
            
            # usunięce litery w w1
            if i > 0: 
                operation_cost = addition_cost(w1[i], w1[i-1])
                if i == 1 : 
                    #dist[i][j] = min(dist[i][j], dist[i-1][j] + 2)
                    if dist[i][j] > dist[i-1][j] + operation_cost*2: 
                        dist[i][j] = min(dist[i][j], dist[i-1][j] + operation_cost*2)
                        solution[i][j] = solution[i-1][j] + ['add ' + w1[i] + ' ' + str(i)+str(j)] 
                else : 
                    #dist[i][j] = min(dist[i][j], dist[i-1][j] + 1)
                    if dist[i][j] > dist[i-1][j] + operation_cost: 
                        dist[i][j] = min(dist[i][j], dist[i-1][j] + operation_cost)
                        solution[i][j] = solution[i-1][j] + ['add ' + w1[i] + ' ' + str(i)+str(j)] 
                
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
                operation_cost = 1.5
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
                operation_cost = 1.5
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

print(ed_dist('kalapea', 'kalarepa'))
print(ed_dist('kalapea', 'kalaba'))

