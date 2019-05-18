#include<bits/stdc++.h>
#include"tango.h"

using namespace std; 

int main(){

    vector<int> elems;
    int n; 
    scanf("%d", &n);
    int n1 = n;
    while( n--){
        int a; 
        scanf("%d", &a);
        elems.push_back(a);
    }
    //sort(elems.begin(), elems.end());
        
    
    tango_tree<int> drzewo(elems);
    int q;
    scanf("%d", &q);
    //cerr<<endl<<endl;
    //drzewo.wypisz();
    //cerr<<endl<<endl;
    
    while(q--){
        int val;
        scanf("%d", &val);
        /*int s = drzewo.size();
        if(s!=n1){
            cerr<<"Różnica w drzewach to: "<<n1-s<<"\n";
            vector<int> c = drzewo.content();
            sort(c.begin(), c.end());
            for(int i = 0; i<c.size(); i++) cerr<<c[i]<<" "; 
        }
        assert(s == n1);*/
        //cerr<<"New query "<<val<<"\n";
        //printf("DEBUG %c %d\n", op, val);
        
       
        bool k = drzewo.find(val);
        //cerr<<"\n";
        if(!k ) printf("BRAK\n");
        else printf("%d\n",val);
        //cerr<<endl<<endl;
        //drzewo.wypisz();
        //cerr<<endl<<endl;

    }
    drzewo.destroy();
    
}