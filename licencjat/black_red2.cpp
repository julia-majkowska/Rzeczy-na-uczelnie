#include<bits/stdc++.h>
#include"br_tree.h"

using namespace std;

vector<br_tree<int> > v;

void print_sets(){
    printf("Sets\n");
    for(int i = 0; i<v.size(); i++){
        v[i].wypisz();
        printf("\n");
    }
}
template<class T>
void checkv(br_vert<T>* w){
    int l_height = 0, r_height = 0;
    if(w->right!=NULL){
        assert(w->right_son()->father == w);
        checkv(w->right_son());
        r_height = w->right_son()->black_h;
    }
    if(w->left!=NULL){
        assert(w->left_son()->father == w);
        checkv(w->left_son());
        l_height = w->left_son()->black_h;
    }
    if(l_height!= r_height){
        w->wypisz();
        cout<<endl<<l_height<<" "<<r_height<<endl;
    }
    assert(l_height == r_height);

    
    bool good = true;
    if(w->is_red() && (is_red(w->right_son()) || is_red(w->left_son()))){
        w->wypisz();
        cout<<endl;
        good = false;
    }
    assert(good);
}

template<class T>
void check_tree(br_tree<T> t){
    if(t.root!=NULL) checkv(t.root);
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
        check_tree(x);
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
            check_tree(v[set]);
        }
        if(op == 'D'){
            scanf("%d %d", &set,&elem);
            v[set].erase(elem);
            print_sets();
            
            check_tree(v[set]);
        }
        if(op == 'S'){
            scanf("%d %d", &set,&elem);
            /*splitted_tree<int> my_pair = v[set].split2(elem);
            v[set] = my_pair.lesser;
            v.push_back(my_pair.greater);
            if(my_pair.pivot != NULL) cout<<"Result : "<<my_pair.pivot->value<<"\n";*/
            pair<br_tree<int>, br_tree<int> >res = v[set].split(elem);
            v[set] = res.first;
            v.push_back(res.second);
            print_sets();
            check_tree(v[set]);
            check_tree(v.back());
            
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
            check_tree(v[set]);
        }
        
    }
    
}
