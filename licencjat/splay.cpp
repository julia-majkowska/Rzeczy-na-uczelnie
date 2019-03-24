#include<bits/stdc++.h>
#include"tree_vert.h"
#include"splay.h"

using namespace std;


int main(){
    int q;
    scanf("%d", &q);
    splay_tree<int> drzewo;
    while(q--){
        char op;
        int val;
        scanf("\n%c %d", &op, &val);
        //printf("DEBUG %c %d\n", op, val);
        //drzewo.wypisz();
        //cout<<endl;
        if(op == 'I'){
            drzewo.insert(val);
        }
        if(op == 'D'){
            bool cz = drzewo.erase(val);
            if(cz) printf("OK\n");
            else printf("BRAK\n");
        }
        if(op == 'L'){
            tree_vert<int>* k = drzewo.lower_bound(val);
            if(k == NULL ) printf("BRAK\n");
            else printf("%d\n",k -> value);

        }
        if(op == 'U'){
            tree_vert<int>* k = drzewo.upper_bound(val);
            if(k == NULL ) printf("BRAK\n"); 
            else printf("%d\n", k-> value);
        }
    }
    
}