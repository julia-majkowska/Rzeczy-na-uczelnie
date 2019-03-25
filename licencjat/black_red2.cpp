#include<bits/stdc++.h>
#include"br_tree.h"

using namespace std;

vector<br_tree<int> > v;

void print_sets(){
    printf("Sets");
    for(int i = 0; i<v.size(); i++){
        v[i].wypisz();
        printf("\n");
    }
}

int main(){//operacje s
    int sets; 
    scanf("%d", &sets);
    for(int i = 0; i< sets; i++){
        int set_size;
        scanf("%d", &set_size);
        br_tree<int> x;
        for(int j =0; j< set_size; j++){
            int a;
            scanf("%d", &a);
            x.insert(a);
        }
        v.push_back(x);
    }
    int q;
    scanf("%d", &q);
    while(q--){
        char op;
        int val;
        scanf("\n%c", &op);
        //printf("DEBUG %c %d\n", op, val);
        int set, elem;
        if(op == 'I'){
            scanf("%d %d", &set,&elem);
            v[set].insert(elem);
            print_sets();
        }
        if(op == 'D'){
            scanf("%d %d", &set,&elem);
            v[set].erase(elem);
            print_sets();
        }
        if(op == 'S'){
            scanf("%d %d", &set,&elem);
            pair< br_tree<int> ,br_tree<int> > my_pair = v[set].split(elem);
            v[set] = my_pair.first;
            v.push_back(my_pair.second);
            print_sets();
            
        }
        if(op =='M'){
            scanf("%d", &set);//add last to set
            if(set >= v.size()-1) {
                print_sets();
                continue;
            }
            v[set] = tree_union(v[set], v.back());
            v.pop_back();
            print_sets();
        }
    }
    
}
