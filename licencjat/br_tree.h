#include"br_vert.h"

template<class T>
bool is_black(br_vert<T>* x){
    if(x == NULL) return true;
    if(x->is_null) return true;
    return x->color == BLACK;
}


template<class T>
bool is_red(br_vert<T>* x){
    return x!= NULL && !x->is_null && x->color == RED;
}

template<class T>
class br_tree{
public:    
    br_vert<T>* root; 
    br_tree<T>(const br_tree<T>& t){
        this->root = t.root;
    }
protected: 
    bool put_in_vert(br_vert<T>* new_vert){
        T value = new_vert->value;
        br_vert<T>* pointer = root; 
        if(this->root == NULL || (this->root != NULL && this->root -> is_null)){
            new_vert->make_black();
            this-> root = new_vert;
            return true;
        }
        while(true){
            if(pointer->value < value ){
                if(pointer->hook_up_right(new_vert)) return true;
                pointer = pointer->right_son();
            }
            if(pointer->value == value) return false;
            if(pointer->value > value ){
                if(pointer->hook_up_left(new_vert)) return true;
                pointer =pointer->left_son();
            }
        }
    }
    br_vert<T>* put_in(T value){

        br_vert<T>* new_vert = new br_vert<T>(value,0, false, RED, NULL,  new br_vert<T>(), new br_vert<T>());//new vertex with leaves
        if(this->put_in_vert(new_vert))   return new_vert;
        return NULL;
    }
    
    void restore_insert(br_vert<T>* x){
        while(!x->is_root() && x->parent()->is_red()){
            //P1a
            if(x->parent()->is_root()){;
                break;
               
            }            
            //P1b            
            if(x->parent()->is_red() && x->uncle()->is_red()){
                x->parent()->make_black();
                x->uncle()->make_black();
                x->grandparent()->make_red();
                x = x -> grandparent();
                continue;
            }
            
            if(x->parent()->is_red() && x->uncle()->is_black()){
                if(x->parent()->is_left()){
                    
                    if(x->is_right()){//P2
                        x->rotate_left();
                        if(x->parent()->is_root()) root = x -> parent();
                        x = x->left_son();//previous parent
                    }
                    
                    //P3
                    x->parent()->make_black(); 
                    x->grandparent()->make_red();
                    x->parent()->rotate_right();
                    if(x->parent()->is_root()) root = x -> parent();
                    continue;
                }
                else{
                    if(x->is_left()){//P2
                        x->rotate_right();
                        if(x->parent()->is_root()) root = x -> parent();
                        x = x->right_son();//previous parent
                    }
                    
                    //P3
                    x->parent()->make_black(); 
                    x->grandparent()->make_red();
                    x->parent()->rotate_left();
                    if(x->parent()->is_root()) root = x -> parent();
                    continue;
                }
                x-> update_black_height();
                x-> brother() -> update_black_height();
                x-> parent()->update_black_height();
            }            
        }
        while(!x->is_root()){
            x->update_black_height();
            x = x->parent();
        }
        this->root->make_black();
    }
    
    void restore_delete(br_vert<T>* x){
        if(x->is_red()){
            x->make_black();
            x->update_black_height();
            return;
        }
        if(x->is_root()){
            x->make_black();
            return;
        }
        
        br_vert<T>* s = x->brother();
        if(s->is_null || s== NULL){
            return restore_delete(x->parent());
        }
        
        if(s->is_black()){//s can't be a leaf since its sibling had a black height of 2 
                //At least one of s's children is red
            x->make_black();
                if(is_black(s->left_son()) && is_black(s->right_son())){
                    s->make_red();
                    s->update_black_height();
                    
                    if(x->parent()->is_black()){
                        x->parent()->make_double_black();
                        return restore_delete(x->parent());
                    }
                    else{
                        x->parent()->make_black();
                        return;
                    }
                }
                if(s->is_right()){
                    //Right right case
                    
                    if(is_red(s->right_son())){
                        s->color = s->parent()->color;
                        s->right_son()->make_black();
                        s->parent()->make_black();
                        s->rotate_left();
                        if(s->is_root()) this->root = s;
                    }
                    else if(is_red(s->left_son())){
                        br_vert<T>* l = s->left_son();
                        s->color = s->parent()->color;
                        s->update_black_height();
                        l->make_black();
                        l->update_black_height();
                        l->rotate_right();       
                        l->rotate_left();
                        if(l->is_root()) this->root = l;
                        
                    }                   
                    
                }else{
                    if(is_red(s->left_son())){
                        s->color = s->parent()->color;
                        s->update_black_height();
                        s->left_son()->make_black();
                        s->parent()->make_black();
                        s->rotate_right();
                        if(s->is_root()) this->root = s;
                    }
                    else if(is_red(s->right_son())){
                        br_vert<T>*r = s->right_son();
                        s->color = s->parent()->color;
                        s->update_black_height();
                        r->make_black();
                        r->update_black_height();
                        r->rotate_left();       
                        r->rotate_right();
                        if(r->is_root()) this->root = r;
                        
                    }
                    
                }
            }else{
                br_vert<T>*f = x->parent();
                s->make_black();
                f->make_red();
                if(s->is_right()){
                    s->tree_vert<T>::rotate_left();  
                    
                }
                else{
                    
                    s->tree_vert<T>::rotate_right();
                    
                }
                if(s->is_root()) this->root = s;
                restore_delete(x);
            }
            
    }
    
    void remove(br_vert<T>* x){//remove a vertex that has at most one son
        
        //Step 1
        br_vert<T>* child = x->left->is_null? x->right_son() : x->left_son();//child possibly empty
        br_vert<T>* f = x->parent();
        if(child->is_left()) x->disown_left();
        else x->disown_right();
        if(x -> is_root()){
           this->root  = child; 
        }
        else if(x->is_right()){
            x->get_disowned();
            f->hook_up_right(child);
        }
        else{
            x->get_disowned(); 
            f->hook_up_left(child);
        }
        
        //Step 2
        
        if(x->is_red() || child->is_red()){
            child->make_black();
            if(f!= NULL && !f->is_null) f->update_black_height();
            delete(x);
            return;
        }
        //Step 3
        x->make_double_black();
        delete(x);
        restore_delete(child);
        
        
    }
    
    br_vert<T>* search(T value){
        if(this->empty()) return NULL;
        return ((br_vert<T>*) this->root->search(value));
    }
    

    void join_right(br_vert<T>* r_root, br_vert<T>* pivot){
        if(r_root == NULL || r_root -> is_null){
            
            this->insert_vert(pivot);
            //this->insert(pivot->value);
            return; 
        }
        if(this->root == NULL || this->root -> is_null){
            
            this->root = r_root;
            this->insert_vert(pivot);
            //this->insert(pivot->value);
            return;
        }
        br_vert<T> * l_root = this->root;
        while(l_root->black_h > r_root->black_h || l_root->is_red()) l_root = l_root -> right_son();

        br_vert<T>* father = l_root->parent();
        pivot->make_red();
        pivot -> disown_left();
        pivot -> disown_right();
        pivot ->hook_up_left(l_root);
        pivot ->hook_up_right(r_root);
        pivot ->update_black_height();
        
        if(father!=NULL && !father->is_null){
            father->disown_right();
            father->hook_up_right(pivot);
            father->update_black_height();
        }
        else this->root = pivot;
        
        restore_insert(pivot);
    }
    
    
    
    void join_left(br_vert<T>* l_root, br_vert<T>* pivot){
        if(l_root == NULL || l_root -> is_null){
            
            this->insert_vert(pivot);
            return;
        }
        if(this->root == NULL || this->root -> is_null){
            
            this->root = l_root;
            this->insert_vert(pivot);
            return;
        }
        br_vert<T> * r_root = this->root; 
        while(r_root->black_h > l_root->black_h || r_root->is_red()){
            r_root = r_root -> left_son();
        }
       
        br_vert<T>* father = r_root->parent(); 
        
        pivot->make_red();
        pivot -> disown_left();
        pivot -> disown_right();
        pivot ->hook_up_left(l_root);
        pivot ->hook_up_right(r_root); 
        pivot ->update_black_height();
        
        if(father!=NULL && !father->is_null){
            father->disown_left();
            father->hook_up_left(pivot);
            father->update_black_height();
        }
        else{
            this->root = pivot;
        }
        restore_insert(pivot);
    }
    
    
    
    
    
public:
    void join_right(br_tree<T>* r, br_vert<T>* pivot){
        join_right(r->root, pivot);
        r->root = NULL;
        delete r;
    }
    
    void join_left(br_tree<T>* l, br_vert<T>* pivot){
        join_left(l->root, pivot);
        l->root = NULL;
        delete l;
    }
    br_tree(){
        this-> root = new br_vert<T>();
    }
    
    br_tree(br_vert<T>* r):
    root(r)
    {
        if(r != NULL) this->root->make_black();
    };
    virtual ~br_tree(){
        if(this->root != NULL) delete this->root; 
    }
    int height(){
        if(this->root != NULL) return this->root->black_h;
    }
    
    void wypisz(){
        if(this->root != NULL) this->root->wypisz();
        else cout<<"EMPTY"<<endl;
    }
    bool empty(){
        if(this->root == NULL) return true;
        return this->root->is_null;
    }
    bool insert(T value);
    bool insert_vert(br_vert<T>* new_vert);
    
    pair<br_tree<T>*,br_tree<T>* > split(T pivot); 
    splitted_tree<T> split2(T pivot);
    
    bool erase(T value); 
    br_vert<T>* lower_bound(T searched);
    
    br_vert<T>* upper_bound(T searched);

    bool find(T searched);
    
};

template<class T>
bool br_tree<T>::insert_vert(br_vert<T>* new_vert){
        
        if(new_vert == NULL || new_vert ->is_null) return true;
        new_vert->color = RED;
        new_vert->black_h = 0;
        new_vert->disown_left();
        new_vert->hook_up_left(new br_vert<T>());
        new_vert->disown_right();
        new_vert->hook_up_right(new br_vert<T>());
        new_vert->get_disowned();
        if(!put_in_vert(new_vert)) return false;
        restore_insert(new_vert);
        this->root->make_black();
        return true;
} 

template<class T>
bool br_tree<T>::insert(T value){
        br_vert<T>* new_vert = this->put_in(value);
        if(new_vert == NULL) return false;
        restore_insert(new_vert);
        this->root->make_black();
        return true;
}



template<class T> br_tree<T>* join(br_tree<T>* left, br_tree<T>* right, br_vert<T>* pivot){
    if(left->height() > right->height()){
        left->join_right(right, pivot); 
        return left; 
    }
    else{
        right->join_left(left, pivot); 
        return right; 
    }
}

template<class T> 
br_tree<T>* tree_union(br_tree<T>* A, br_tree<T>* B){
    if(A->empty()) return B; 
    if(B->empty()) return A; 
    
    pair<br_tree<T>*, br_tree<T>* > splitted = A->split(B->root->value); 
    br_tree<T>* left_subtree = new br_tree<T>(B->root->left_son());
    br_tree<T>* right_subtree = new br_tree<T>(B->root->right_son()); 
    
    B->root->disown_right();
    B->root->disown_left();
    br_tree<T>* left_component = tree_union(splitted.first, left_subtree);
    br_tree<T>* right_component = tree_union(splitted.second, right_subtree);
    
    return join(left_component, right_component, B->root); 

}

template<class T> 
class splitted_tree{
public: 
    br_tree<T>* lesser; 
    br_vert<T> *pivot; //can be null if is not found
    br_tree<T>* greater; 
    
    splitted_tree(br_tree<T>* l, br_tree<T>* g,  br_vert<T> *p = NULL):
    lesser(l), 
    greater(g), 
    pivot(p){};
};

template<class T> 
splitted_tree<T> br_tree<T>::split2(T pivot){//splitting into lesser and greater or equal
        br_vert<T>* pointer = this-> root;
        br_tree<T>* l= new br_tree<T>(); 
        br_tree<T>* r= new br_tree<T>();
        if(pointer == NULL || pointer -> is_null) return splitted_tree<T>(l, r);
        br_vert<T> * l_point = pointer->left_son();
        br_vert<T> * r_point = pointer->right_son();
        pointer->disown_left();
        pointer->disown_right();
        if(pointer->value > pivot){
            splitted_tree<T> splitted = br_tree<T>(l_point).split2(pivot);
            return splitted_tree<T>(
                splitted.lesser, 
                join(splitted.greater,new br_tree<T>(r_point), pointer),
                splitted.pivot);
        }
        else if (pointer->value < pivot) {
            splitted_tree<T> splitted = br_tree<T>(r_point).split2(pivot);
            return splitted_tree<T>(
                join(new br_tree<T>(l_point),splitted.lesser, pointer),
                splitted.greater,
                splitted.pivot);
        }
        
        return splitted_tree<T>(
            new br_tree<T>(l_point), 
            new br_tree<T>(r_point),
            pointer); 
        
    }

template<class T> 
pair<br_tree<T>*,br_tree<T>* > br_tree<T>::split(T pivot){//splitting into lesser and greater or equal
        br_vert<T>* pointer = this-> root;
        br_tree<T>* l = new br_tree<T>(); 
        br_tree<T>* r = new br_tree<T>();
        if(pointer == NULL || pointer -> is_null) return make_pair(l, r);
        br_vert<T> * l_point = pointer->left_son();
        br_vert<T> * r_point = pointer->right_son();
        pointer->disown_left();
        pointer->disown_right();
        if(pointer->value >= pivot){
            pair<br_tree<T>*, br_tree<T>* > splitted = br_tree<T>(l_point).split(pivot);
            return make_pair(splitted.first, join(splitted.second, new br_tree<T>(r_point), pointer));
        }
        else if (pointer->value < pivot) {
            pair<br_tree<T>*, br_tree<T>* > splitted = br_tree<T>(r_point).split(pivot);
            return make_pair(join(new br_tree<T>(l_point),splitted.first, pointer), splitted.second);
        }
        
        return make_pair(l, r); 
        
    }
 
template<class T> 
bool br_tree<T>::erase(T value){
    br_vert<T>* key = search(value);
    if(key== NULL) return false;
    if(key->is_null) cerr<<"Stop me there is a mistake";
    if(key->value != value) return false;
    if(key->left==NULL || key->right == NULL || key->left->is_null || key->right->is_null) this->remove(key);
    else{
        br_vert<T>* key1 = ((br_vert<T>*) key->next());
        key->value = key1 -> value;
        this->remove(key1);
    }
    return true;
}

template<class T> 
bool br_tree<T>::find(T searched){
    if(this->empty()) return false;
    br_vert<T>* candidate = (br_vert<T>*)search(searched); 
    if(candidate == NULL) return false; 
    return candidate->value == searched;    
}

template<class T> 
br_vert<T>* br_tree<T>::lower_bound(T searched){
    if(this->empty()) return NULL;
    br_vert<T>* candidate = (br_vert<T>*)search(searched); 
    if(candidate == NULL) return NULL; 
    if(candidate->value > searched) candidate =  ((br_vert<T>*)candidate->prev());
    return candidate;
    
}

template<class T> 
br_vert<T>* br_tree<T>::upper_bound(T searched){
    if(this->empty()) return NULL;
    br_vert<T>* candidate = (br_vert<T>*) search(searched);
    if(candidate == NULL) return NULL;
    if(candidate->value < searched) candidate = ((br_vert<T>*)candidate->next());
    return candidate;
    
}

