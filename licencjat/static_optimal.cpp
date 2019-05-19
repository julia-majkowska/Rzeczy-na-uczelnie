#include<bits/stdc++.h>
#include"static_tree.h"
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
    int q;
    scanf("%d", &q);
    vector<int> queries; 
    while(q--){
        int val;
        scanf("%d", &val);
        queries.push_back(val);
    }
    
    static_tree<int> drzewo(queries);
    //drzewo.wypisz();
    
    for(int i = 0; i< queries.size(); i++){
        if(!drzewo.find(queries[i]))
            cout<<"BRAK\n";
        else cout<<queries[i]<<"\n";
    }
}