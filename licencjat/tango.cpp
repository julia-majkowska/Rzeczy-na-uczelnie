#include<bits/stdc++.h>
#include"tango.h"

using namespace std; 

int main(){

    vector<int> elems;
    int n; 
    scanf("%d", &n);
    while( n--){
        int a; 
        scanf("%d", &a);
        elems.push_back(a);
    }
    sort(elems.begin(), elems.end());
        
    
    tango_tree<int> drzewo(elems, 0, elems.size() -1, 0);
    int q;
    scanf("%d", &q);
    //cerr<<endl<<endl;
    //drzewo.wypisz();
    //cerr<<endl<<endl;
    
    while(q--){
        int val;
        scanf("%d", &val);
        //cerr<<"New query "<<val<<"\n";
        //printf("DEBUG %c %d\n", op, val);
        
       
        bool k = drzewo.find(val);
        if(!k ) printf("BRAK\n");
        else printf("%d\n",val);
        //cerr<<endl<<endl;
        //drzewo.wypisz();
        //cerr<<endl<<endl;

    }
    
}