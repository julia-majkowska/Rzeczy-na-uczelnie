#include<bits/stdc++.h>

using namespace std;

template<class T>
class tree_vert{
public:
    
    T value;
    bool is_null = false; //true with extra null vertexes
    
    tree_vert<T>* father;
    tree_vert<T>* left;
    tree_vert<T>* right;
    
    tree_vert(T val, tree_vert<T>*f = NULL, tree_vert<T>*l = NULL, tree_vert<T>*r = NULL, bool is_null = false):
    value(val),
    father(f),
    left(l),
    right(r)
    {
        if(l!=NULL) l->father = this;
        if(r!=NULL) r->father = this; 
    };
    
    tree_vert()://constructor of a null vertex
    value(),
    father(NULL),
    left(NULL),
    right(NULL), 
    is_null(true)
    {};
    
    ~tree_vert(){
        this->get_disowned();
        if(this->left!=NULL && this->left->is_null){
            delete(this->left);
        }
        if(this->left!=NULL && this->right->is_null){
            delete(this->right);
        }
    };
    
    void wypisz();
    
    void disown_left();
    
    void disown_right();
    
    bool hook_up_left(tree_vert<T>* l);
    
    bool hook_up_right(tree_vert<T>*r);
    
    bool get_disowned();
    bool is_root();
    
    bool is_left();
    bool is_right();

    void rotate_left();
    
    void rotate_right();
    
    void splay();
    
    tree_vert<T>* search( T search_value );
    
    tree_vert<T>* next();
    
    tree_vert<T>* prev();
    
};

#include"tree_vert.tpp"

