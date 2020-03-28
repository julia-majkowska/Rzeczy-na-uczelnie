from colorama import Fore, Style#, init
from copy import deepcopy
#init()

def highlight(q, L):
  return highlight2(q, L, lambda x,y: x==y)

def highlight2(q, L, match):
  r = []
  for w in L:
    if any(match(w,v) for v in q):
      r.append(Fore.RED + Style.BRIGHT + w + Fore.BLACK + Style.RESET_ALL)
    else:
      r.append(w) 
  return ' '.join(r)
  
def green(s):
  return Fore.GREEN + Style.BRIGHT + s + Fore.BLACK + Style.RESET_ALL
  
def yellow_line():
  print (Fore.YELLOW + Style.BRIGHT + 60 * '-' + Fore.BLACK + Style.RESET_ALL)  
