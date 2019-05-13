#include<bits/stdc++.h>

using namespace std;

vector<vector<int> > v;

void print_sets(){
    printf("Sets\n");
    for(int i = 0; i<v.size(); i++){
        for(int j = 0; j< v[i].size(); j++){
            printf("%d ", v[i][j]);
        }
        printf("\n");
    }
}

int main(){//operacje s
    int sets; 
    scanf("%d", &sets);
    for(int i = 0; i< sets; i++){
        int set_size;
        scanf("%d", &set_size);
        vector<int> x;
        for(int j =0; j< set_size; j++){
            int a;
            scanf("%d", &a);
            x.push_back(a);
        }
        sort(x.begin(), x.end());
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
            v[set].push_back(elem);
            sort(v[set].begin(), v[set].end());
            print_sets();
        }
        if(op == 'D'){
            scanf("%d %d", &set,&elem);
            int kand = lower_bound(v[set].begin(), v[set].end(), elem)-v[set].begin();
            if(!v[set].empty() && v[set][kand] == elem){
                int last = v[set].back();
                v[set][kand]  = last;
                v[set].pop_back();
                sort(v[set].begin(), v[set].end());
            }
            print_sets();
        }
        if(op == 'S'){
            scanf("%d %d", &set,&elem);
            int kand = lower_bound(v[set].begin(), v[set].end(), elem)-v[set].begin();
            if(!v[set].empty() && v[set][kand] >= elem){
                vector<int> nowy; 
                /*if(v[set][kand] == elem){
                    cout<<"Result : "<<elem<<"\n";
                    kand++;
                }*/
                for(int i = kand; i< v[set].size(); i++)
                    nowy.push_back(v[set][i]);
                int s = v[set].size();
                for(int i = kand; i< s; i++)
                    v[set].pop_back();
            
                v.push_back(nowy);
            }
            else{
                vector<int> nowy;  
                v.push_back(nowy);
            }
            print_sets();
            
        }
        if(op =='M'){
            scanf("%d", &set);//add last to set
            if(set >= v.size()-1) {
                print_sets();
                continue;
            }
            for(int i = 0; i<v.back().size(); i++){
                v[set].push_back(v.back()[i]);
            }
            v.pop_back();
            sort(v[set].begin(), v[set].end());
            print_sets();
        }
    }
    
}
