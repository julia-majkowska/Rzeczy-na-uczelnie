#include<bits/stdc++.h>

using namespace std;

template<class T>
class tree_vert{
public:
    
    T value;
    
    tree_vert<T>* father;
    tree_vert<T>* left;
    tree_vert<T>* right;
    
    tree_vert(T val, tree_vert<T>*f = NULL, tree_vert<T>*l = NULL, tree_vert<T>*r = NULL):
    value(val),
    father(f),
    left(l),
    right(r)
    {};
    
    void wypisz();
    
    void disown_left();
    
    void disown_right();
    
    bool hook_up_left(tree_vert<T>* l);
    
    bool hook_up_right(tree_vert<T>*r);
        
    bool hook_onto(tree_vert<T>* new_father);
    
    bool get_disowned();
    bool is_root(){
        return this->father == NULL;  
    };
    
    bool is_left(){
        return this->father!= NULL && this->father->left == this;       
    };
    bool is_right(){
        return this->father!= NULL && this->father->right == this;
    };

    void rotate_left();
    
    void rotate_right();
    
    void splay();
    
    tree_vert<T>* tree_vert::search( T search_value );
    
};

#include"tree_vert.tpp"

