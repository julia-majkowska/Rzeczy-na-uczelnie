#include<bits/stdc++.h>

template<class T>
class splay_tree{
    
    
public:
    tree_vert<T>* root;
    splay_tree(){
        root = NULL;
    };
    splay_tree(tree_vert<T>* r){
        root = r;
    };
    
    ~splay_tree(){
        if(this->root != NULL){
            delete this->root;
        }
    }

protected:
    
    tree_vert<T>* search( T splay_value ){
        tree_vert<T>* pointer = this -> root; 
        if(this -> root == NULL) return NULL;
        while( pointer -> value!= splay_value) {
            if( pointer -> value < splay_value ){
                if(pointer-> right == NULL) return pointer; 
                pointer = pointer-> right; 
            }
            else{
                if(pointer-> left == NULL) return pointer; 
                pointer = pointer-> left;                
            }
        }
        return pointer;
    };
    
    tree_vert<T>* next( tree_vert<T>* current) {
        if(current -> right != NULL){
            current = current -> right; 
            while(current -> left != NULL) current = current -> left; 
            return current; 
        }
        while(current-> is_right() && !current->is_root() ) current = current->father; 
        if(current->is_root()) return NULL;//does not have next element
        current = current->father;
        return current;         
    }
    
    
    tree_vert<T>* prev( tree_vert<T>* current) {
        if(current -> left != NULL){
            current = current -> left; 
            while(current -> right != NULL) current = current -> right; 
            return current; 
        }
        while(current-> is_left() && !current->is_root() ) current = current->father; 
        if(current->is_root()) return NULL;//does not have next element
        current = current->father;
        return current;         
    }
    
    T find1(T searched){
        T res;
        if(this->root == NULL) return false;
        splay(searched);
        return this->root->value;
    }
    
    void splay(T splay_value){
        tree_vert<T>* new_root = search(splay_value); 
        new_root->splay();
        this -> root = new_root;
        
    }
    
    vector<splay_tree<T>* > split(T searched);
    
public:
    
    void wypisz(){
        if(this-> root!= NULL) this->root->wypisz(); 
    }
    
    bool find(T searched){
        T res; 
        if(this ->root == NULL) return false;
        splay(searched);
        return this->root->value == searched;
    };
    
    
    tree_vert<T>* lower_bound(T searched){
        if(this->empty()) return NULL;
        tree_vert<T>* candidate = search(searched); 
        if(candidate->value > searched) candidate =  this->prev(candidate);
        if(candidate!= NULL){
            candidate->splay();
            this->root = candidate; 
        }
        return candidate;
        
    }
    
    tree_vert<T>* upper_bound(T searched){
        if(this->empty()) return NULL;
        tree_vert<T>* candidate = search(searched); 
        if(candidate->value < searched) candidate = this->next(candidate);
        if(candidate!= NULL){
            candidate->splay();
            this->root = candidate;
        }
        return candidate;
        
    }
    
    bool empty(){
        return this->root == NULL;
    };
    
    bool insert(T value);
    bool erase(T value);
};

template<class T>
vector<splay_tree<T>* > splay_tree<T>::split(T searched){// spliting between less that,equal and greater than
    if(this->root == NULL){
        vector<splay_tree<T>* > result;
        splay_tree<T> * empty1 = new splay_tree<T>();
        result.push_back(empty1);
        splay_tree<T> * empty2 = new splay_tree<T>();
        result.push_back(empty2);
        return result;
    }
    this->splay(searched);
    vector<splay_tree<T>* > result;
    if(this->root->value > searched){
        splay_tree<T>* lesser = new splay_tree<T>(this->root->left);
        result.push_back(lesser);   
        this->root->disown_left();
        result.push_back(new splay_tree<T>(this->root));
        return result;
    }
    if(this->root->value < searched){
        splay_tree<T>* greater = new splay_tree<T>(this->root->right);
        this->root->disown_right();
        result.push_back(new splay_tree<T>(this->root));
        result.push_back(greater);
        return result;
    }
    if(this->root->value == searched){
        splay_tree<T>* lesser = new splay_tree<T>(this->root->left);
        result.push_back(lesser); 
        this->root->disown_left();
        splay_tree<T>* greater = new splay_tree<T>(this->root->right);
        this->root->disown_right();
        result.push_back(new splay_tree<T>(this->root));
        result.push_back(greater);
        return result;
    }
}
template<class T>
splay_tree<T>* join( splay_tree<T>* lesser, splay_tree<T>* greater){
    splay_tree<T>* res;
    if(lesser->empty()){
        res = new splay_tree<T>(greater->root);
        
    }
    else if(greater->empty()){
        res = new splay_tree<T>(lesser->root);
    }
    else{
        lesser->find(greater->root->value);
        lesser->root->hook_up_right(greater->root);
        
        res = new splay_tree<T>(lesser->root);
    }
    greater->root = NULL;
    lesser->root = NULL;
    return res;
}
template<class T>
bool splay_tree<T>::insert(T value){
    tree_vert<T>* new_root = new tree_vert<T>(value);
    if(this -> root == NULL){
        this ->root = new_root;
        return true;
    }
    T pivot = this->find1(value); 
    if(pivot == value) return false; 
    vector<splay_tree<T>*> halves = this->split(value);
    new_root->hook_up_left(halves[0]->root); 
    new_root-> hook_up_right(halves[1]->root);
    this -> root = new_root;
    halves[0]->root = NULL;
    halves[1]->root = NULL;
    if(halves[0] != NULL) delete halves[0];
    if(halves[1] != NULL) delete halves[1];
    return true;
}

template<class T>
bool splay_tree<T>::erase(T value){
    if(this->root == NULL) return false;
    tree_vert<T>* pivot = this->search(value);
    if(pivot->value != value) return false; 
    vector<splay_tree<T>*> halves = this->split(value);
    splay_tree<T>* joined = join(halves[0], halves[2]);
    this -> root = joined-> root;
    joined->root = NULL;
    if(joined != NULL) delete joined; 
    if(halves[0] != NULL) delete halves[0];
    if(halves[1] != NULL) delete halves[1];
    if(halves[2] != NULL) delete halves[2];
    return true;
}
