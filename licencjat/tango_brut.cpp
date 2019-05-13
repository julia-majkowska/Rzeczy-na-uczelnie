#include<bits/stdc++.h>

using namespace std;

int main(){
    
    set<long long> drzewo;
    int n; 
    scanf("%d\n", &n);
    while(n--){
        long long a; 
        scanf("%lld", &a);
        drzewo.insert(a);
    }
    
    int q; 
    scanf("%d\n", &q);
    
    while(q--){
        long long val;
        scanf("%lld", &val);
        //printf("DEBUG %c %d\n", op, val);
    
        if(drzewo.empty()){
            printf("BRAK\n");
            continue;
        }
        std::set<long long>::iterator k = drzewo.lower_bound(val);
        
        if(((k == drzewo.begin()) && (*k > val)) || *k != val){
            //printf("%lld",*k);
            printf("BRAK\n"); 
        }
        else{
            if(k == drzewo.end() || (k!= drzewo.end() && *k > val)) k--;
            printf("%lld\n", *k);
            
        }

        
    }
    
}