import fileinput
keyboard = ['qwertyuiop[]', 'asdfghjkl;\'', '<zxcvbnm,./']
def letters_close(l1, l2) : 
    l1 = l1.lower()
    l2 = l2.lower()
    surround = [(1, 0), (0, 1), (-1, 1), (-1, 0), (0, -1) , (1, -1)]
    for j in range(len(keyboard)): 
        for i in range(len(keyboard[j])):
            if(keyboard[j][i] == l1) : 
                for (i1, j1) in surround : 
                    j2 = j1+j
                    if j2 < 0 or j2 > 2:
                        continue
                    i2 = i1+i 
                    if i2 < 0 or i2 > len(keyboard[j2]) :
                        continue
                    if keyboard[j2][i2] == l2: 
                        return True
    return False
                    
def ed_dist(w1, w2) : 
    w1 = '#' + w1
    w2 = '#' + w2
    dist = [[0]*len(w2) for i in w1]
    for i in range(len(w1)):
        for j in range(len(w2)): 

            #operacje wagi 1 - usuniecie, zmiana bliska
            dist[i][j] = 100000000000
            if i == 0 and j == 0 : 
                dist[i][j] = 0 
                continue
            if i > 0 and j > 0 and w1[i] == w2[j]: #litery sie zgadzają
                dist[i][j] = dist[i-1][j-1]
                
            # dodanie litery w w2
            if j > 0 : 
                if j == 1 : 
                    dist[i][j] = min(dist[i][j], dist[i][j-1] + 2)
                else : 
                    dist[i][j] = min(dist[i][j], dist[i][j-1] + 1)
            
            # usunięce litery w w2
            if i > 0: 
                if i == 1 : 
                    dist[i][j] = min(dist[i][j], dist[i-1][j] + 2)
                else : 
                    dist[i][j] = min(dist[i][j], dist[i-1][j] + 1)
                
            # zamiana litery
            if i > 0 and j > 0 : 
                if letters_close(w1[i], w2[j]) : 
                    if i == 1 or j == 1 : 
                        dist[i][j] = min(dist[i][j], dist[i-1][j-1] + 2) #zamiana bliska na początku
                    else: 
                        dist[i][j] = min(dist[i][j], dist[i-1][j-1] + 1) #zamiana bliska w srodku
                else : 
                    if i == 1 or j == 1 : 
                        dist[i][j] = min(dist[i][j], dist[i-1][j-1] + 4) #zamiana daleka na początku
                    else: 
                        dist[i][j] = min(dist[i][j], dist[i-1][j-1] + 2) #zamiana daleka w srodku
                    
            #swap
            if i < 2 or j < 2 : 
                continue
            
            if w1[i] == w2[j-1] and w1[i-1] == w2[j] : 
                if i == 2 or j == 2 : 
                    dist[i][j] = min(dist[i][j], dist[i-2][j-2] + 2) #swap na początku
                else: 
                    dist[i][j] = min(dist[i][j], dist[i-2][j-2] + 1) #swap w srodku
            
            #swap z literką w środku
            if i < 3 or j < 3 : 
                continue
            if w1[i] == w2[j-2] and w1[i-2] == w2[j] and w[i-1] == w[j-1]: 
                if i == 3 or j == 3 : 
                    dist[i][j] = min(dist[i][j], dist[i-2][j-2] + 2) #swap na początku
                else: 
                    dist[i][j] = min(dist[i][j], dist[i-2][j-2] + 1) #swap w srodku
                    
    print(dist)
    return dist[len(w1)-1][len(w2)-1]


for query in fileinput.input():
     qs = query.split()
     print(ed_dist(qs[0], qs[1]))