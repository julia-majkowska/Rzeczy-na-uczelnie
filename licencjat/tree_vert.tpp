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
    if(this -> left != NULL){
        if(!this->left->is_null) return false; 
        delete(this->left);
    }
    this -> left = l;
    if(l != NULL ) l-> father = this; 
    return true; 
}

template<class T>
bool tree_vert<T>::hook_up_right(tree_vert<T>*r){
    if(this -> right != NULL){
        if(!this->right->is_null) return false; 
        delete(this->right);
    }
    this -> right = r;
    if(r != NULL ) r-> father = this; 
    return true; 
};

template<class T>
bool tree_vert<T>::get_disowned(){
    if(this->father == NULL) return false; 
    if(this->is_left()) this->father->disown_left();
    else this->father->disown_right();
    return true;
}

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
}

template<class T>
void tree_vert<T>::rotate_left(){
    tree_vert* f = this-> father; 
    tree_vert* b = this-> left;
    tree_vert* gf = this->father -> father;
    bool turn = this->father->is_left();
    
    f-> get_disowned();
    f-> disown_right();//cutting x off
    this-> disown_left(); 
    this-> hook_up_left(f);
    f-> hook_up_right(b);
    if(gf == NULL || gf->is_null) return;
    if(turn){
        gf->hook_up_left(this);
    }
    else{
        gf->hook_up_right(this);
    }
    
}


template<class T>
void tree_vert<T>::rotate_right(){
    tree_vert* f = this-> father; 
    tree_vert* b = this-> right;
    tree_vert* gf = this->father -> father;
    bool turn = this->father->is_left();
    
    f-> get_disowned();
    f-> disown_left();//cutting x off
    this-> disown_right(); 
    this-> hook_up_right(f);
    f-> hook_up_left(b);
    if(gf == NULL || gf->is_null) return;
    if(turn){
        gf->hook_up_left(this);
    }
    else{
        gf->hook_up_right(this);
    }
    
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

template<class T>
tree_vert<T>* tree_vert<T>::search( T search_value ){
        tree_vert<T>* pointer = this;
        while( pointer -> value!= search_value) {
            if( pointer -> value < search_value ){
                if(pointer-> right == NULL){
                    return pointer;
                }
                if(pointer-> right -> is_null){
                    return pointer; 
                }
                pointer = pointer-> right; 
            }
            else{
                if(pointer-> left == NULL){
                    return pointer;
                }
                if(pointer-> left -> is_null){
                    return pointer; 
                }
                pointer = pointer-> left;                
            }
        }
        return pointer;
};

template<class T>
tree_vert<T>* tree_vert<T>::next(){
    tree_vert<T>* current = this;
    if(current -> right != NULL && !current->right->is_null){
        current = current -> right; 
        while(current -> left != NULL && !current-> left->is_null) current = current -> left; 
        return current; 
    }
    while(current-> is_right() && !current->is_root() ) current = current->father; 
    if(current->is_root()) return NULL;//does not have next element
    current = current->father;
    return current;  
}

template<class T>
tree_vert<T>* tree_vert<T>::prev(){
    tree_vert<T>* current = this;
    if(current -> left != NULL && !current->left->is_null){
        current = current -> left; 
        while(current -> right != NULL && !current->right->is_null) current = current -> right; 
        return current; 
    }
    while(current-> is_left() && !current->is_root() ) current = current->father; 
    if(current->is_root()) return NULL;//does not have next element
    current = current->father;
    return current;      
}
