import sys
from highlight import highlight, green, yellow_line
import time

lines = []
tokens = []

def match(query, line):
    return all(w in line for w in query)
  
def search(q):
    return [line for line in tokens if match(q, line)]

      
for line in open('tokenized_quotes.txt'):
    L = line.split()  
    tokens.append(L)
  
print ('No, dalej!')

t0 = time.time()

for x in sys.stdin:
    L = x.split() 
    print (green('QUERY: ') + ' '.join(L))
    search(L)
    for res in search(L):
        print ('   ', highlight(L, res)) 
    yellow_line() 
    print()   
print (time.time() - t0)        
