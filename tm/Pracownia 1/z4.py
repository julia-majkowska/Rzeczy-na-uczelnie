
#from tokenize import tokenize
from keras.preprocessing.text import text_to_word_sequence
with open('cytaty.txt', 'rb') as f:
    """tokens = tokenize(f.readline)
    tokensr = [t.string for t in tokens]
    #print(tokensr)
    i = 0
    for token in tokens:
        #if i > 1000: 
        #    break
        i+=1
        print("'" + token.string + "'", end = ' ')"""
    
    text_to_word_sequence(text, filters='!"#$%&()*+,-./:;<=>?@[\\]^_`{|}~\t\n', lower=True, split=' ')

        