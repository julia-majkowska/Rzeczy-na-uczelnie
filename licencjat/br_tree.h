#include<bits/stdc++.h>
#include"tree_vert.h"
#include <cassert>

const int RED = 0;
const int BLACK = 1;
const int DOUBLE_BLACK = 2; 
template<class T> 
class splitted_tree;

template<class T>
class br_vert: public tree_vert<T> {
public: 
    int color; //false - red , true - black
    int black_h;
    int max_depth = 0; 
    int depth = 0; 
    
    br_vert(T val, int d, bool il = false, bool col = RED, br_vert<T>*f = NULL, br_vert<T>*l = NULL, br_vert<T>*r = NULL):
    tree_vert<T>(val, f, l, r, il),
    color(col)
    {
        depth = d;
        black_h = 0;
        if(l!= NULL) black_h= l->black_h;
        black_h+=col;
    };
    
    br_vert()://constructor for an empty leaf
    tree_vert<T>(),
    color(BLACK),
    black_h(1)
    {};

    
    bool is_red(){
        return this->color==0;
    }
    
    bool is_black(){
        return this->color>0;
    }
    
    void make_red(){
        this->color = RED;
        update_black_height();
    }
    void make_black(){
        this->color = BLACK;
        update_black_height();
    }
    
    void make_double_black(){
        this->color = DOUBLE_BLACK;
        this->update_black_height();
    }
    bool is_double_black(){
        this->color == 2;
    }
    bool hook_up_left(br_vert<T>* x){
        bool v= this->tree_vert<T>::hook_up_left(x);
        this->update_black_height();
        return v;
    }
    
    bool hook_up_right(br_vert<T>* x){
        bool v = this->tree_vert<T>::hook_up_right(x);
        this->update_black_height();
        return v;
    }
    br_vert<T>* parent(){
        return (br_vert<T>*) this->father;
        
    }
    br_vert<T>* left_son(){
        return (br_vert<T>*) this->left;
    }
    
    br_vert<T>* right_son(){
        return (br_vert<T>*) this->right;
        
    }
    br_vert<T>* grandparent(){
        if(this->father == NULL) return NULL;
        return (br_vert<T>*)this->father->father; 
    }
    
    br_vert* uncle(){
        if(this->father == NULL || this->grandparent() == NULL) return NULL;
        if(this->father -> is_left()) return this->grandparent()->right_son();
        return this->grandparent()->left_son();
    }
    
    br_vert* brother(){
        if(this->father == NULL) return NULL;
        if(this-> is_left()) return this->parent()->right_son();
        return this->parent()->left_son();
    }
    
    void update_black_height(){
        int left_h  = 0, right_h = 0;
        this->max_depth = this->depth;
        if(this->left_son() != NULL){
            left_h= this->left_son()->black_h;
            this->max_depth = max(this->max_depth, this->left_son()->max_depth);
        }
        if(this->right_son() != NULL){
            right_h = this->right_son()->black_h;
            this->max_depth = max(this->max_depth, this->right_son()->max_depth);
        }
        this->black_h = right_h + this->color;
        
    }
    
    void wypisz(){
        if(this->is_null) return;
        //cout<<"(";
        if(this->left!=NULL) this -> left_son()-> wypisz();
        if(! this-> is_null) cout<<this->value<<" ";//<<","<< this -> color<<", "<<black_h;
        if(this->right!=NULL) this -> right_son()-> wypisz();
        //cout<<")";
    }
    void rotate_left(){
        tree_vert<T>::rotate_left();
        if(this->left!=NULL) this->left_son()->update_black_height();
        this->update_black_height();
    }
    
    void rotate_right(){
        tree_vert<T>::rotate_right();
        if(this->right!=NULL) this->right_son()->update_black_height();
        this->update_black_height();
    }
 
};

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
                        //cout<<"P2 lr\n";
                        x->rotate_left();
                        if(x->parent()->is_root()) root = x -> parent();
                        x = x->left_son();//previous parent
                    }
                    
                    //P3
                    //cout<<"P3ll\n";
                    x->parent()->make_black(); 
                    x->grandparent()->make_red();
                    x->parent()->rotate_right();
                    if(x->parent()->is_root()) root = x -> parent();
                    continue;
                }
                else{
                    if(x->is_left()){//P2
                        //cout<<"P2rl\n";
                        x->rotate_right();
                        if(x->parent()->is_root()) root = x -> parent();
                        x = x->right_son();//previous parent
                    }
                    
                    //P3
                   // cout<<"P3rr\n";
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
        this->root->make_black();
    }
    
    void restore_delete(br_vert<T>* x){
        //cout<<"wypisuje x\n";
        //x->wypisz();
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
            //cout<<"No sibling";
            return restore_delete(x->parent());
        }
        
        if(s->is_black()){//s can't be a leaf since its sibling had a black height of 2 
                //At least one of s's children is red
            //cout<<"Black s";
            x->make_black();
                if(is_black(s->left_son()) && is_black(s->right_son())){
                    //cout<<"Black sons ";
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
                        //cout<<"Right right\n ";
                        //s->right_son()->color = s->parent()->color;
                        //s->update_black_height();
                        //s->color= 
                        s->color = s->parent()->color;
                        s->right_son()->make_black();
                        s->parent()->make_black();
                        s->rotate_left();
                        if(s->is_root()) this->root = s;
                    }
                    else if(is_red(s->left_son())){
                        //cout<<"Right left\n ";
                        br_vert<T>* l = s->left_son();
                        s->color = s->parent()->color;
                        s->update_black_height();
                        l->make_black();//color = x->parent()->color;
                        l->update_black_height();
                        l->rotate_right();       
                        l->rotate_left();
                        if(l->is_root()) this->root = l;
                        
                    }                   
                    
                }else{
                    if(is_red(s->left_son())){
                        //cout<<"Left left\n ";
                        //s->left_son()->color = s->parent()->color;
                        s->color = s->parent()->color;
                        s->left_son()->make_black();
                        s->parent()->make_black();
                        //s->update_black_height();
//                         s->color = s->parent()->color;
                        s->rotate_right();
                        if(s->is_root()) this->root = s;
                        //cout<<"Left out"<<endl;
                    }
                    else if(is_red(s->right_son())){
                        //cout<<"Left right\n ";
                        br_vert<T>*r = s->right_son();
                        s->color = s->parent()->color;
                        s->update_black_height();
                        r->make_black();//x->parent()->color;
                        r->update_black_height();
                        r->rotate_left();       
                        r->rotate_right();
                        if(r->is_root()) this->root = r;
                        
                    }
                    
                }
               // restore_delete(x);
            }else{
                br_vert<T>*f = x->parent();
                s->make_black();
                f->make_red();
                if(s->is_right()){
                    //cout<<"Red right"<<endl;
                    s->tree_vert<T>::rotate_left();  
                    
                }
                else{
                    //cout<<"Red left"<<endl;
                    s->tree_vert<T>::rotate_right();
                    
                }
                if(s->is_root()) this->root = s;
                //cout<<"Po rotacji i aktualizacji\n";
                //s->wypisz();
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
        //cout<<"LALALA"<<endl;
        //Step 2
        
        if(x->is_red() || child->is_red()){
            child->make_black();
            child->update_black_height();
            delete(x);
            return;
        }
        
        //cout<<"Po swapie"<<endl;
        //this->wypisz();
        //Step 3
        x->make_double_black();
        delete(x);
        restore_delete(child);
        
        
    }
    
    br_vert<T>* search(T value){
        if(this->empty()) return NULL;
        return ((br_vert<T>*) this->root->search(value));
    }
    
    bool insert_vert(br_vert<T>* new_vert){
        
        if(new_vert == NULL || new_vert ->is_null) return true;
        new_vert->color = RED;
        new_vert->black_h = 0;
        new_vert->disown_left();
        new_vert->hook_up_left(new br_vert<T>());
        new_vert->disown_right();
        new_vert->hook_up_right(new br_vert<T>());
        new_vert->get_disowned();
        /*cout<<"wypisuje new_vert ";
        new_vert->wypisz();
        cout<<endl;
        this->wypisz();
        cout<<endl;*/
        if(!put_in_vert(new_vert)) return false;
        restore_insert(new_vert);
        this->root->make_black();
        return true;
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
            //this->insert(pivot->value);
            return;
        }
        if(this->root == NULL || this->root -> is_null){
            
            this->root = l_root;
            this->insert_vert(pivot);
            //this->insert(pivot->value);
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
    void join_right(br_tree<T> r, br_vert<T>* pivot){
        join_right(r.root, pivot);
        r.root = NULL;
    }
    
    void join_left(br_tree<T> l, br_vert<T>* pivot){
        join_left(l.root, pivot);
        l.root = NULL;
    }
    br_tree(){
        this-> root = new br_vert<T>();
    }
    
    br_tree(br_vert<T>* r):
    root(r)
    {
        if(r != NULL) this->root->make_black();
    };
    
    int height(){
        if(this->root != NULL) return this->root->black_h;
    }
    
    void wypisz(){
        if(this->root != NULL) this->root->wypisz();
        else cout<<"EMPTY"<<endl;
    }
    bool empty(){
        if(this->root == NULL) return true;
        else this->root->is_null;
    }
    bool insert(T value);
    
    pair<br_tree<T>,br_tree<T> > split(T pivot); 
    
    splitted_tree<T> split2(T pivot);
    
    bool erase(T value); 
    br_vert<T>* lower_bound(T searched);
    
    br_vert<T>* upper_bound(T searched);

    
};

template<class T>
bool br_tree<T>::insert(T value){
        br_vert<T>* new_vert = this->put_in(value);
        if(new_vert == NULL) return false;
        restore_insert(new_vert);
        this->root->make_black();
        return true;
}



template<class T> 
br_tree<T> join(br_tree<T> left, br_tree<T> right, br_vert<T>* pivot){
    
    if(left.height() > right.height()){
        left.join_right(right, pivot); 
        return left; 
    }
    else{
        right.join_left(left, pivot); 
        return right; 
    }
}

template<class T> 
br_tree<T> tree_union(br_tree<T> A, br_tree<T> B){
    cout<<"jestem w union ";
    A.wypisz();
    cout<<endl<<A.empty()<<endl;
    B.wypisz();
    cout<<endl<<B.empty()<<endl;
    if(A.empty()) return B; 
    if(B.empty()) return A; 
    cout<<"Dalej unionuuje\n";
    pair<br_tree<T>, br_tree<T> > splitted = A.split(B.root->value); 
    br_tree<T> left_subtree(B.root->left_son());
    br_tree<T> right_subtree(B.root->right_son()); 
    
    B.root->disown_right();
    B.root->disown_left();
    br_tree<T> left_component = tree_union(splitted.first, left_subtree);
    br_tree<T> right_component = tree_union(splitted.second, right_subtree);
    
    return join(left_component, right_component, B.root); 

}

template<class T> 
class splitted_tree{
public: 
    br_tree<T> lesser; 
    br_vert<T> *pivot; //can be null if is not found
    br_tree<T> greater; 
    
    splitted_tree(br_tree<T> l, br_tree<T> g,  br_vert<T> *p = NULL):
    lesser(l), 
    greater(g), 
    pivot(p){};
};

template<class T> 
splitted_tree<T> br_tree<T>::split2(T pivot){//splitting into lesser and greater or equal
        br_vert<T>* pointer = this-> root;
        br_tree<T> l; 
        br_tree<T> r;
        if(pointer == NULL || pointer -> is_null) return splitted_tree<T>(l, r);
        br_vert<T> * l_point = pointer->left_son();
        br_vert<T> * r_point = pointer->right_son();
        pointer->disown_left();
        pointer->disown_right();
        if(pointer->value > pivot){
            splitted_tree<T> splitted = br_tree<T>(l_point).split2(pivot);
            return splitted_tree<T>(
                splitted.lesser, 
                join(splitted.greater, br_tree<T>(r_point), pointer),
                splitted.pivot);
        }
        else if (pointer->value < pivot) {
            splitted_tree<T> splitted = br_tree<T>(r_point).split2(pivot);
            return splitted_tree<T>(
                join(br_tree<T>(l_point),splitted.lesser, pointer),
                splitted.greater,
                splitted.pivot);
        }
        
        return splitted_tree<T>(
            tree_union(l,br_tree<T>(pointer->left_son())), 
            tree_union(br_tree<T>(pointer->right_son()),r),
            pointer); 
        
    }

template<class T> 
pair<br_tree<T>,br_tree<T> > br_tree<T>::split(T pivot){//splitting into lesser and greater or equal
        br_vert<T>* pointer = this-> root;
        br_tree<T> l; 
        br_tree<T> r;
        if(pointer == NULL || pointer -> is_null) return make_pair(l, r);
        br_vert<T> * l_point = pointer->left_son();
        br_vert<T> * r_point = pointer->right_son();
        pointer->disown_left();
        pointer->disown_right();
        if(pointer->value > pivot){
            pair<br_tree<T>, br_tree<T> > splitted = br_tree<T>(l_point).split(pivot);
            return make_pair(splitted.first, join(splitted.second, br_tree<T>(r_point), pointer));
        }
        else if (pointer->value < pivot) {
            pair<br_tree<T>, br_tree<T> > splitted = br_tree<T>(r_point).split(pivot);
            return make_pair(join(br_tree<T>(l_point),splitted.first, pointer), splitted.second);
        }
        
        return make_pair(l, r); 
        
    }
 
template<class T> 
bool br_tree<T>::erase(T value){
    br_vert<T>* key = search(value);
    if(key== NULL) return false;
    if(key->is_null) printf("Stop me there is a mistake");
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

