#include<bits/stdc++.h>
using namespace std;

template<class T>
void tree_vert<T>::wypisz(){
    cout<<"(";
    if(this->left!=NULL) this -> left-> wypisz();
    cout<<"| "<<this->value<<"|";
    if(this->right!=NULL) this -> right-> wypisz();
    cout<<")";
}

template<class T>
void tree_vert<T>::disown_left(){
    if(this->left!= NULL){
        this->left->father = NULL;
        this->left = NULL;
    }
}

template<class T>
void tree_vert<T>::disown_right(){
    if(this->right!= NULL){
        this->right->father = NULL;
        this->right = NULL;
    }
}


template<class T>
bool tree_vert<T>::hook_up_left(tree_vert<T>* l){
    if(this -> left != NULL) return false; 
    this -> left = l;
    if(l != NULL ) l-> father = this; 
    return true; 
}

template<class T>
bool tree_vert<T>::hook_up_right(tree_vert<T>*r){
    if(this -> right != NULL) return false; 
    this -> right = r;
    if(r != NULL ) r-> father = this; 
    return true; 
};


template<class T>
bool tree_vert<T>::hook_onto(tree_vert<T>* new_father){
    this -> father = new_father;
    if(new_father == NULL) return false;
    if(new_father->value < this->value) new_father->hook_up_right(this);
    else new_father->hook_up_left(this);
    return true;
}

template<class T>
bool tree_vert<T>::get_disowned(){
    if(this->father == NULL) return false; 
    if(this->is_left()) this->father->disown_left();
    else this->father->disown_right();
    return true;
}
/*
template<class T>
bool tree_vert<T>::is_root(){
    return this->father == NULL;  
}

template<class T>
bool tree_vert<T>::is_left(){
    return this->father!= NULL && this->father->left == this;       
}

template<class T>
bool tree_vert<T>::is_right(){
    return this->father!= NULL && this->father->right == this;
}*/

template<class T>
void tree_vert<T>::rotate_left(){
    tree_vert* f = this-> father; 
    tree_vert* b = this-> left;
    tree_vert* gf = this->father -> father;
    
    f-> get_disowned();
    f-> disown_right();//cutting x off
    this-> disown_left(); 
    this-> hook_up_left(f);
    f-> hook_up_right(b);
    this-> hook_onto(gf);
    
}


template<class T>
void tree_vert<T>::rotate_right(){
    tree_vert* f = this-> father; 
    tree_vert* b = this-> right;
    tree_vert* gf = this->father -> father;
    
    f-> get_disowned();
    f-> disown_left();//cutting x off
    this-> disown_right(); 
    this-> hook_up_right(f);
    f-> hook_up_left(b);
    this-> hook_onto(gf);
}

template<class T>
void tree_vert<T>::splay(){
    
    while(!this-> is_root()){ 
        if(this-> is_left()){
            if(this-> father-> is_root()){
                //cout<<"ZIGright\n";
                this->rotate_right();
                continue; 
            }
            if(this->father-> is_left()){// rotating x right twice with parent and grandparent - x and father both left sons
                //cout<<"ZIGZIGright\n";
                this->father->rotate_right();
                this->rotate_right();
            }
            else{// rotating x right then left with parent and grandparent - x is left and father right son
                //cout<<"ZIGZAGrightleft\n";
                this->rotate_right();
                this->rotate_left();
            }
        }
        else{
            if(this-> father-> is_root()){
                //cout<<"ZIGleft\n";
                this->rotate_left();    
                continue; 
            }
            if(this->father-> is_left()){
                //cout<<"ZIGZAGleftright\n";
                this->rotate_left();
                this->rotate_right();
            }
            else{// rotating x left then right with parent and grandparent - x is right and father left son
                //cout<<"ZIGZIGleft\n";
                this->father->rotate_left();
                this->rotate_left();
            
            } 
        }
    }
            
}


