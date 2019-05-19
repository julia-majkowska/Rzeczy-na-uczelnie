#include<bits/stdc++.h>
#include <cassert>
#include"br_tree.h"
using namespace std;
template<class T>
void checkv(br_vert<T>* v){
    int l_height = 0, r_height = 0;
    if(v->right!=NULL){
        checkv(v->right_son());
        r_height = v->right_son()->black_h;
    }
    if(v->left!=NULL){
        checkv(v->left_son());
        l_height = v->left_son()->black_h;
    }
    if(l_height!= r_height){
        v->wypisz();
        cout<<endl<<l_height<<" "<<r_height<<endl;
    }
    assert(l_height == r_height);
    
    /*if(v->black_h  != r_height + v->color){
        v->wypisz();
        cout<<endl<<v->black_h<<" "<<r_height<<endl;
    }
    assert(v->black_h == r_height + v->color);*/
    
    bool good = true;
    if(v->is_red() && (is_red(v->right_son()) || is_red(v->left_son()))){
        v->wypisz();
        cout<<endl;
        good = false;
    }
    assert(good);
}

template<class T>
void check_tree(br_tree<T>& t){
    if(t.root!=NULL) checkv(t.root);
}

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
        //drzewo.wypisz();
        //cout<<endl;
        check_tree(drzewo);
        
        //cout<<"Params :"<<drzewo.root->is_null<<" "<<drzewo.root->value<<endl;
        
        
    }
    drzewo.destroy();
    
}