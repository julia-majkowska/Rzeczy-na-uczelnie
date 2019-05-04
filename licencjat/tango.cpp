#include<bits/stdc++.h>
#include"tango.h"

using namespace std;


int main(){
    int q;
    scanf("%d", &q);
    tango_tree<int> drzewo;
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
        if(op == 'F'){
            bool k = drzewo.find(val);
            if(!k ) printf("BRAK\n");
            else printf("%d\n",val);

        }
    }
    
}