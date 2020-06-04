
import fileinput
from collections import defaultdict as dd 
from highlight import highlight2, green, yellow_line
from nltk.tokenize import word_tokenize
import json
import jsonpickle
import psycopg2
import fileinput
from collections import defaultdict as dd
from nltk.tokenize import word_tokenize
import editdistance
import heapq
from sklearn.preprocessing import normalize
import numpy as np
import scipy.sparse as sp
keyboard = ['qwertyuiop[]', 'asdfghjkl;\'', '<zxcvbnm,./']
coords  = { keyboard[a][b] : (a, b) for a in range(len(keyboard)) for b in range(len(keyboard[a]))}
mistakes = [('ę', 'e'), ('u', 'ó'), ('ó', 'o'),('ą', 'a'), ('ś', 's'),('ł', 'l'), ('ł', 'u'), ('ż', 'z'), ('ź', 'z'), ('ch', 'h'), ('rz', 'ż'), ('ć', 'c'), ('ń', 'n')]

subst = dd(lambda: set())
for (a, b) in mistakes : 
    subst[a].add(b)
    subst[b].add(a)

def polskawa(w):
    w = w.lower()
    zmiany = {'e' : 'ę', 'o' : 'ó', 'u':'ó',  'a': 'ą', 's': 'ś','l': 'ł', 'z': 'ż', 'ź': 'ż', 'x': 'ż', 'c':'ć', 'n': 'ń'}
    slowo = ''
    for l in w: 
        lit = l
        if lit in zmiany:
            lit = zmiany[lit]
        slowo = slowo + lit
    return slowo
    
def read_dictionary() :
    titles = dd(lambda: set())
    artykuly = {}
    title_cont = {}
    size_of_window = 5
    with open('fp_wiki.txt', 'r') as f:
        first_line = ""
        i = 0
        line = f.readline()
        current_article=line
        while line :
            if line.startswith("TITLE:"): 
                artykuly[i] = current_article
                current_article = ""
                i+=1
                cur_title = line[7:-1]
                title_cont[i] = cur_title
                
                for ii in range(len(cur_title) - size_of_window+1): 
                    titles[polskawa(cur_title)[ii:ii+size_of_window]].add(i)
                if  len(cur_title)>=2 : 
                    titles[cur_title[0:2]].add(i)
                else: 
                    titles[cur_title[0]].add(i)
        
            current_article+=line
            line = f.readline()
            
    return titles, artykuly, title_cont

onegrams, articles, title_content = read_dictionary()

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
                operation_cost = 4
                if i == 1 : 
                    if dist[i][j] > dist[i][j-1] + operation_cost*2: 
                        dist[i][j] = min(dist[i][j], dist[i][j-1] + operation_cost*2)
                        solution[i][j] = solution[i][j-1] + ['delete ' + w2[j]] 
                    
                else : 
                    if dist[i][j] > dist[i][j-1] + operation_cost: 
                        dist[i][j] = min(dist[i][j], dist[i][j-1] + operation_cost)
                        solution[i][j] = solution[i][j-1] + ['delete ' + w2[j]] 
            
            # usunięce litery w w1
            if i > 0: 
                operation_cost = addition_cost(w1[i], w1[i-1])
                if i + 1 < len(w1): 
                    operation_cost = min(operation_cost, addition_cost(w1[i], w1[i+1]))
                if i == 1 : 
                    if dist[i][j] > dist[i-1][j] + operation_cost*2: 
                        dist[i][j] = min(dist[i][j], dist[i-1][j] + operation_cost*2)
                        solution[i][j] = solution[i-1][j] + ['add ' + w1[i]] 
                else : 
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
                            solution[i][j] = solution[i-1][j-1] + ['swap ' + w1[i] + " na " + w2[j]]  #zamiana bliska na początku
                    else: 
                        if dist[i][j] > dist[i-1][j-1] + operation_cost: 
                            dist[i][j] = min(dist[i][j], dist[i-1][j-1] + operation_cost)
                            solution[i][j] = solution[i-1][j-1] + ['swap ' + w1[i] + " na " + w2[j]]  #zamiana bliska w srodku
                
                    
            #swap
            if i < 2 or j < 2 : 
                continue
            
            if w1[i] == w2[j-1] and w1[i-1] == w2[j] : 
                operation_cost = 2.25
                if i == 2 or j == 2 :  #swap na początku
                    if dist[i][j] > dist[i-2][j-2] + operation_cost*2: 
                            dist[i][j] = min(dist[i][j], dist[i-2][j-2] + operation_cost*2)
                            solution[i][j] = solution[i-2][j-2] + ['neighbour swap ' + w1[i] + " na " + w2[j]] 
                else:  #swap w srodku
                    if dist[i][j] > dist[i-2][j-2] + operation_cost: 
                            dist[i][j] = min(dist[i][j], dist[i-2][j-2] + operation_cost)
                            solution[i][j] = solution[i-2][j-2] + ['neighbour swap ' + w1[i] + " na " + w2[j]] 
            
            #swap z literką w środku
            if i < 3 or j < 3 : 
                continue
            if w1[i] == w2[j-2] and w1[i-2] == w2[j] and w1[i-1] == w2[j-1]: 
                operation_cost = 2.75
                if i == 3 or j == 3 :  #swap na początku
                    if dist[i][j] > dist[i-3][j-3] + operation_cost*2: 
                            dist[i][j] = min(dist[i][j], dist[i-3][j-3] + operation_cost*2)
                            solution[i][j] = solution[i-3][j-3] + ['next neighbour swap ' + w1[i] + " na " + w2[j]] 
                else:  #swap w srodku
                    if dist[i][j] > dist[i-3][j-3] + operation_cost: 
                            dist[i][j] = min(dist[i][j], dist[i-3][j-3] + operation_cost)
                            solution[i][j] = solution[i-3][j-3] + ['next neighbour swap ' + w1[i] + " na " + w2[j]] 
            
    return dist[len(w1)-1][len(w2)-1], solution[len(w1)-1][len(w2)-1]

def almost_same_title(w1, w2) : 
    #print("Comparing titles", w1.split(' (')[0] , w2.split(' (')[0], w1.split(' (')[0] == w2.split(' (')[0])
    return w1.split(' (')[0] == w2.split(' (')[0]

def correct_word(word1, ans = '') :
    cands = []
    cand_set = set()
    min_dist = 10000000000000000
    solution = ''
    size_of_window=5
    ans_in_search = False
    for i in range(len(word1) - size_of_window+1): 
        window = polskawa(word1[i:i+size_of_window])
        for wi in onegrams[window]: 
            if wi in cand_set: 
                continue
            w = title_content[wi]
            if w == ans: 
                ans_in_search = True
            dist = editdistance.eval(word1, w)
             
            heapq.heappush(cands, (-1*dist, wi))
            cand_set.add(wi)
            if len(cands)>20 : 
                heapq.heappop(cands)
    for wi in onegrams[word1[0:2]]: 
        if wi in cand_set: 
                continue
        w = title_content[wi]
        if len(w) - len(word1) > 4: 
            continue
        if len(word1) - len(w) > 4:
            continue
        if w == ans: 
            ans_in_search = True
        dist = editdistance.eval(word1, w)
        heapq.heappush(cands, (-1*dist, wi))
        cand_set.add(wi)
        if len(cands)>20 : 
            heapq.heappop(cands)
    #print(cands)
    cand = []
    for dist, wi in cands: 
        w = title_content[wi]
        #print(w, cand, min_dist)
        dist, sol = ed_dist(w, word1)
        #print(word1, w, dist)
        if len(cand) > 0 and almost_same_title(title_content[cand[0]], w): 
            cand.append(wi)
            continue
        if dist < min_dist:
                    cand = [wi]
                    min_dist = dist
        elif  dist == min_dist and len(cand) > 0 :
            if len(title_content[cand[0]]) > len(w):
                cand = [wi]
                min_dist = dist
            elif len(title_content[cand[0]]) == len(w) and wi < cand[0]: 
                cand = [wi]
                min_dist = dist
    return cand

conn = psycopg2.connect("dbname=indeks user=julia")

def get_dokument(indeks): 
    cur = conn.cursor()
    cur.execute('''SELECT content FROM articles where id = \'%s\''''%indeks)
    dokument = cur.fetchall()
    cur.close()
    conn.commit()
    return dokument[0][0]

my_matrix= []
with open('indeksy/sparse_matrix.txt', 'r') as f:
    my_matrix = jsonpickle.decode(f.read())
    
#print("diffing rows")
#print(my_matrix.getrow(22547) - my_matrix.getrow(801626))
        
    
def closest_K_document(query_doc_id, K = 20):
    #print(query_doc_id)
    coll = my_matrix.getrow(query_doc_id)
    #print(my_matrix.get_shape(), coll.get_shape())
    dists = -1.0 *(my_matrix.dot(coll.T)).toarray()
    #print(dists.shape)
    #print(np.partition(dists, K, axis = None)[:K])
    return np.argpartition(dists, K, axis = None)[:K]

print("Ready for input\n")
for query in fileinput.input():
    matched = False
    indices = correct_word(query)
    i = indices[0] 
    matched = True
    print("Found a matched title")
    print(get_dokument(i))
    print('_______________________________________\nResults:')
    close_docs = closest_K_document(i)
    for doc_id in close_docs : 
        print(get_dokument(doc_id))
    print(close_docs)
    