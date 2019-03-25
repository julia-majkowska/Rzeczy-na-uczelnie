#include<bits/stdc++.h>
#include <cassert>
#include"br_tree.h"
using namespace std;

int main(){
    int q;
    scanf("%d", &q);
    br_tree<int> drzewo;
    while(q--){
        char op;
        int val;
        scanf("\n%c %d", &op, &val);
        //printf("%c %d ", op, val);
        //printf("DEBUG %c %d\n", op, val);

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
        //cout<<"Params :"<<drzewo.root->is_null<<" "<<drzewo.root->value<<endl;
        //drzewo.wypisz();
        //cout<<endl;
    }
    
}