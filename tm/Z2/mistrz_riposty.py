from wyszukiwarka_indeks import lemats, indeks, quotes
from collections import defaultdict as dd 
from keras.preprocessing.text import text_to_word_sequence
from highlight import highlight2, green, yellow_line
import fileinput
import random 
ranks_global = [100.]*len(quotes)
last_reply = ""
generyczne_cytaty = ["abwehra wie wszystko .", "aby do wiosny !"]

def denote_pronouns(docs):#possibly already cropped
    pronouns = []
    ranks = [100.]* len(docs)
    with open('zaimki.txt') as f:
        l = f.readline()
        while l: 
            words = l.split(' ')
            pronouns += words
            l= f.readline()
    for i in range(len(docs)): 
        bad_quote = False
        for tok in docs[i]: 
            for z in pronouns :
                if z == tok : 
                    bad_quote = True
                    ranks[i] = 75.
                    break
            if bad_quote: 
                break
    return ranks
      
def crop(doc, start, end): 
    
    while start > 0 and not ('.' in doc[start-1]) :
        start-=1
        
    while end < len(doc) and not ('.' in doc[end]) :
        end += 1
    return doc[start:end]

def match_tokens(query_tok, text_tok): 
    a = lemats[query_tok]
    b = lemats[text_tok]
    intersec = a.intersection(b)
    return len(intersec) != 0
    

def my_highlight(q, L): 
    return highlight2(q, L, lambda x, y :match_tokens(x, y))


def filter_bad_docs(sel_toks, doc_ind): 
    doc = quotes[doc_ind]
    
    cur_sent = [""]*len(sel_toks)
    sent = []
    for tok in doc : 
        if tok == "." : 
            if cur_sent == sel_toks: 
                #print(sent)
                return True
            cur_sent = [""]*len(sel_toks)
            sent = []
        else : 
            sent.append(tok)
            for i in range(len(sel_toks)): 
                if(match_tokens(sel_toks[i], tok)): 
                    cur_sent[i] = sel_toks[i]
    return False

    
def check_radius(radius, prefsum, all_occurances): 
    for i in range(1, len(prefsum), 1): 
        good = True
        for ii in range(len(prefsum[i])): 
            koniec = i
            while koniec< len(prefsum) and all_occurances[koniec]  <=  i + radius: 
                koniec += 1
            koniec-=1
            if prefsum[koniec][ii] <= prefsum[i-1][ii] : 
                good = False
                break
        if good : 
            return i
    return None
            
def calc_radius(selected_tokens, doc): 
    occurances = [[] for i in range(len(selected_tokens))]
    i = 0
    all_occurances = [0]
    for t in doc : 
        for ii in range(len(selected_tokens)) : 
            if match_tokens(t, selected_tokens[ii]) : 
                occurances[ii].append(i)
                all_occurances.append(i)
        i+=1
                
    prefsum = [[0]*len(occurances) for i in all_occurances]
    for i in range(1, len(all_occurances), 1): 
        for ii in range(len(occurances)): 
            if len(occurances[ii]) == 0: 
                prefsum[i][ii] = prefsum[i-1][ii]
                continue
            if occurances[ii][0] <= all_occurances[i]: 
                prefsum[i][ii] = prefsum[i-1][ii] + 1
                occurances[ii] = occurances[ii][1:]
            else: 
                prefsum[i][ii] = prefsum[i-1][ii]
                
    for i in range(len(selected_tokens), len(doc), 1): 
        start = check_radius(i, prefsum, all_occurances)
        if start != None : 
            return all_occurances[start], i
    
def rank(good, selected_tokens, docs, seed = None) : 
    global last_reply
    #docs = sorted(docs, key = lambda d: calc_radius(selected_tokens, quotes[d]))
    short_docs = []
    docs = list(docs)
    for i in docs: 
        start, r = calc_radius(selected_tokens, quotes[i])
        #print(quotes[i])
        #print(start, r)
        short_docs.append(crop(quotes[i], start, start+r))
    ranks_pro = denote_pronouns(short_docs)
    ranks_final = [ranks_pro[i]*ranks_global[docs[i]] for i in range(len(docs))]
    cand = ""
    docnum = 0
    if seed == None : 
        final_rank = sorted(zip(short_docs, ranks_final, docs), key= lambda x : x[0], reverse = True)
        cand = final_rank[0][0]
        docnum = final_rank[0][2]
        if cand == last_reply and len(final_rank) > 1 : 
            cand = final_rank[1][0]
            docnum = final_rank[1][2]
    else : 
        prefsum = [0]*len(ranks_final)
        prefsum[0] = ranks_final[0]
        suma = ranks_final[0]
        for i in range(1, len(ranks_final), 1) : 
            prefsum[i] = prefsum[i-1] + ranks_final[i]
            suma += ranks_final[i]
        random.seed(seed) 
        while cand == last_reply: 
            number = random.randrange(0, suma, 1)
            for i in range(len(prefsum)): 
                if i > number: 
                    cand = short_docs[i]
                    docnum = docs[i]
                    break
    last_reply = cand
    ranks_global[docnum]*=0.5
    
    return cand
    
    

def generate_response(query): 
    global last_reply
    q_toks = text_to_word_sequence(query, filters='!"#$%&()*+,-./:;<=>?@[\\]^_`{|}~\t\n', lower=True, split=' ')
    t_indices = []
    for t in q_toks : 
        #print(t)
        lem = lemats[t]
        ind = set()
        for l in lem : 
            ind|= indeks[l]
            
        t_indices.append((t, ind))
    
    t_indices = sorted(t_indices, key = lambda x : len(x[1]))
    #print([len(i) for (t, i) in t_indices])
    cur_indices = t_indices[0][1]
    selected_tokens = [t_indices[0][0]]
    i = 1
    good = 0
    while len(cur_indices) > 20 and i < len(t_indices): 
        new_indices = cur_indices & t_indices[i][1]
        if len(new_indices) == 0: 
               break
        cur_indices = new_indices
        selected_tokens.append(t_indices[i][0])
        a = {ind for ind in cur_indices if filter_bad_docs(selected_tokens, ind)}
        if len(a) > 0:
            cur_indices = a
            good= i
        i+=1
    
    #if len(cur_indices) > 20:
    #    print("Weź mów precyzyjnie" + str(len(cur_indices)))
    #else: 
    print(selected_tokens)
        #for ind in cur_indices: 
        #    print(my_highlight(selected_tokens, quotes[ind]))
        
    if len(cur_indices) == 0 : 
        response = generyczne_cytaty[0]
        if response == last_reply : 
            response = generyczne_cytaty[1]
        last_reply = response
        print(response)
    else : 
        print(my_highlight(selected_tokens, rank(good, selected_tokens, cur_indices)))
        
        
print("Dzień dobry\n")
for query in fileinput.input():
    generate_response(query)