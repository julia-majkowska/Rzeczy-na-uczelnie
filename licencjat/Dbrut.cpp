#include<bits/stdc++.h>

using namespace std;

int main(){
    
    int q; 
    scanf("%d\n", &q);
    set<long long> drzewo;
    while(q--){
        char op;
        long long val;
        scanf("\n%c %lld", &op, &val);
        //printf("DEBUG %c %d\n", op, val);
        if(op == 'I'){
            drzewo.insert(val);
        }
        if(op == 'D'){
            int cz = drzewo.erase(val);
            if(cz) printf("OK\n");
            else printf("BRAK\n");
        }
        if(op == 'L'){
            if(drzewo.empty()){
                printf("BRAK\n");
                continue;
            }
            std::set<long long>::iterator k = drzewo.lower_bound(val);
            
            if((k == drzewo.begin()) && (*k > val) ){
               //printf("%lld",*k);
               printf("BRAK\n"); 
            }
            else{
                if(k == drzewo.end() || (k!= drzewo.end() && *k > val)) k--;
                printf("%lld\n", *k);
                
            }
        }
        if(op == 'U'){
            std::set<long long>::iterator k = drzewo.lower_bound(val);
            if(k == drzewo.end()){
               printf("BRAK\n"); 
            }
            else printf("%lld\n", *k);
        }
    }
    
}