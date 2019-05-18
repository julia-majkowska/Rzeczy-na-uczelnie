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
    
    
public:
    
    void wypisz(){
        if(this-> root!= NULL) this->root->wypisz(); 
    }
    
    void splay(T splay_value){
        tree_vert<T>* new_root = search(splay_value); 
        new_root->splay();
        this -> root = new_root;
        
    };
    
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
vector<splay_tree<T>* > split(splay_tree<T>* tree, T searched){// spliting between less that,equal and greater than
    if(tree->root == NULL){
        vector<splay_tree<T>* > result;
        splay_tree<T> * empty1 = new splay_tree<T>();
        result.push_back(empty1);
        splay_tree<T> * empty2 = new splay_tree<T>();
        result.push_back(empty2);
        return result;
    }
    tree->splay(searched);
    vector<splay_tree<T>* > result;
    if(tree->root->value > searched){
        splay_tree<T>* lesser = new splay_tree<T>(tree->root->left);
        result.push_back(lesser);   
        tree->root->disown_left();
        result.push_back(tree);
        return result;
    }
    if(tree->root->value < searched){
        splay_tree<T>* greater = new splay_tree<T>(tree->root->right);
        tree->root->disown_right();
        result.push_back(tree);
        result.push_back(greater);
        return result;
    }
    if(tree->root->value == searched){
        splay_tree<T>* lesser = new splay_tree<T>(tree->root->left);
        result.push_back(lesser); 
        tree->root->disown_left();
        
        splay_tree<T>* greater = new splay_tree<T>(tree->root->right);
        tree->root->disown_right();
        result.push_back(tree);
        result.push_back(greater);
        return result;
    }
}
template<class T>
splay_tree<T>* join( splay_tree<T>* lesser, splay_tree<T>* greater){
    if(lesser->empty()) return greater;
    if(greater->empty()) return lesser;
    lesser->find(greater->root->value);
    lesser->root->hook_up_right(greater->root);
    return lesser;
}
template<class T>
bool splay_tree<T>::insert(T value){
    tree_vert<T>* new_root = new tree_vert<T>(value);
    if(this -> root == NULL){
        this ->root = new_root;
        return true;
    }
    T pivot = this->find(value); 
    if(pivot == value) return false; 
    vector<splay_tree<T>*> halves = split(this, value);
    new_root->hook_up_left(halves[0]->root); 
    new_root-> hook_up_right(halves[1]->root);
    this -> root = new_root;
    return true;
}

template<class T>
bool splay_tree<T>::erase(T value){
    T pivot = this->find(value); 
    if(pivot != value) return false; 
    vector<splay_tree<T>*> halves = split(this,value);
    this -> root = join(halves[0], halves[2])-> root;
    return true;
}
