#include<bits/stdc++.h>
#include"tree_vert.h"
#include <cassert>

const bool RED = false;
const bool BLACK = true;
template<class T>
class br_vert: public tree_vert<T> {
public: 
    bool color; //false - red , true - black
    int black_h;
    
    br_vert(T val, bool il = false, bool col = RED, tree_vert<T>*f = NULL, tree_vert<T>*l = NULL, tree_vert<T>*r = NULL):
    tree_vert<T>(val, f, l, r, il),
    color(col)
    {};
    
    br_vert()://constructor for an empty leaf
    tree_vert<T>(),
    color(BLACK)
    {};

    
    bool is_red(){
        return this->color==0;
    }
    
    bool is_black(){
        return this->color>0;
    }
    
    bool is_double_black(){
        this->color == 2;
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
        //assert(this->left_son()->black_h == this->right_son()->black_h);
        this->black_h = this->left_son()->black_h + this->color;
    }
    
    void wypisz(){
       //s if(this->is_null) return;
        //cout<<"(";
        if(this->left!=NULL) this -> left_son()-> wypisz();
        if(! this-> is_null) cout<<this->value<<" ";//<<","<< this -> color;
        if(this->right!=NULL) this -> right_son()-> wypisz();
        //cout<<")";
    }
    
};
template<class T>
bool is_black(br_vert<T>* x){
    if(x == NULL) return true;
    return x->color == BLACK;
}


template<class T>
bool is_red(br_vert<T>* x){
    return x!= NULL && x->color == RED;
}

template<class T>
class br_tree{
public:    
    br_vert<T>* root; 
protected: 
    br_vert<T>* put_in(T value){
        br_vert<T>* pointer = root; 
        br_vert<T>* new_vert = new br_vert<T>(value, false, RED, NULL,  new br_vert<T>(), new br_vert<T>());//new vertex with leaves
        if(this->root == NULL || (this->root != NULL && this->root -> is_null)){
            new_vert->color = BLACK;
            this-> root = new_vert;
            return new_vert;
        }
        while(true){
            if(pointer->value < value ){
                if(pointer->hook_up_right(new_vert)) return new_vert;
                pointer = pointer->right_son();
            }
            if(pointer->value == value) return pointer;
            if(pointer->value > value ){
                if(pointer->hook_up_left(new_vert)) return new_vert;
                pointer =pointer->left_son();
            }
        }
    }
    
    void restore_insert(br_vert<T>* x){
        while(!x->is_root() && x->parent()->is_red()){
            //P1a
            if(x->parent()->is_root()){
                //cout<<"P1a\n";
                x->parent()->color = BLACK;//root is black
                x->parent()->update_black_height();
                return;
            }
            
            //P1b
            
            if(x->parent()->is_red() && x->uncle()->is_red()){
                //cout<<"P1b\n";
                x->parent()->color = BLACK; 
                x->parent()->update_black_height();
                x->uncle()->color = BLACK;
                x->uncle()->update_black_height();
                x->grandparent()->color = RED;
                x->grandparent()->update_black_height();
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
                    x->parent()->color = BLACK; 
                    x->grandparent()->color = RED;
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
                    //cout<<"P3rr\n";
                    x->parent()->color = BLACK; 
                    x->grandparent()->color = RED;
                    x->parent()->rotate_left();
                    if(x->parent()->is_root()) root = x -> parent();
                    continue;
                }
                x-> update_black_height();
                x-> brother() -> update_black_height();
                x-> parent()->update_black_height();
            }            
        }
        this->root->color = BLACK;
    }
    
    void restore_delete(br_vert<T>* x){
        //cout<<"wypisuje x\n";
        //x->wypisz();
        if(x->is_red()){
            x->color = BLACK;
            return;
        }
        if(x->is_root()) return;
        
        br_vert<T>* s = x->brother();
        if(s->is_null || s== NULL)
            return restore_delete(x->parent());
        ////cout<<"wypisuje ojca\n";
        //x->parent()->wypisz();
        
        if(s->is_black()){//s can't be a leaf since its sibling had a black height of 2 
                //At least one of s's children is red
            //cout<<"Black s";
                if(s->left_son()->is_black() && s->right_son()->is_black()){
                    //cout<<"Black sons ";
                    s->color = RED;
                    return restore_delete(x->parent());
                }
                if(s->is_right()){
                    //Right right case
                    
                    if(s->right_son()->is_red()){
                        //cout<<"Right right\n ";
                        s->right_son()->color = BLACK;
                        s->rotate_left();
                        if(s->is_root()) this->root = s;
                    }
                    else if(s->left_son()->is_red()){
                        //cout<<"Right left\n ";
                        br_vert<T>* l = s->left_son();
                        l->rotate_right();       
                        l->rotate_left();
                        if(l->is_root()) this->root = l;
                        l->color = BLACK;
                        s->color = RED;
                    }                   
                    
                }else{
                    if(s->left_son()->is_red()){
                        //cout<<"Left left\n ";
                        s->left_son()->color = BLACK;
                        s->rotate_right();
                        if(s->is_root()) this->root = s;
                        //cout<<"Left out"<<endl;
                    }
                    else if(s->right_son()->is_red()){
                        //cout<<"Left right\n ";
                        br_vert<T>*r = s->right_son();
                        r->rotate_left();       
                        r->rotate_right();
                        if(r->is_root()) this->root = r;
                        r->color = BLACK;
                        s->color = RED;
                    }
                    
                }
                
            }else{
                br_vert<T>*f = x->parent();
                f->color = RED;
                s->color = BLACK;
                if(s->is_right())
                    s->rotate_left();                    
                
                else
                    s->rotate_right();
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
            child->color = BLACK;
            delete(x);
            return;
        }
        //cout<<"Po swapie\n";
        //this->wypisz();
        //Step 3
        delete(x);
        restore_delete(child);
        
        
    }
    
    br_vert<T>* search(T value){
        if(this->empty()) return NULL;
        return ((br_vert<T>*) this->root->search(value));
    }
    
    void join_right(br_vert<T>* r_root, br_vert<T>* pivot){
        if(r_root == NULL || r_root -> is_null){
            this->insert(pivot->value);
            return; 
        }
        if(this->root == NULL || this->root -> is_null){
            this->root = r_root;
            this->insert(pivot->value);
            return;
        }
        br_vert<T> * l_root = this->root;
        while(l_root->black_h > r_root->black_h) l_root = l_root -> right_son();
        br_vert<T>* father = l_root->parent();
        if(l_root->is_left()){
            if(father!=NULL && !father->is_null) father->hook_up_left(pivot);
        }
        else{
            if(father!=NULL && !father->is_null) father->hook_up_right(pivot);
        }
        pivot ->hook_up_left(l_root);
        pivot ->hook_up_right(r_root); 
        if(pivot ->is_root() ) this->root = pivot;
        restore_insert(pivot);
    }
    
    
    void join_left(br_vert<T>* l_root, br_vert<T>* pivot){
        if(l_root == NULL || l_root -> is_null){
            this->insert(pivot->value);
            return; 
        }
        if(this->root == NULL || this->root -> is_null){
            this->root = l_root;
            this->insert(pivot->value);
            return;
        }
        br_vert<T> * r_root = this->root; 
        while(r_root->black_h > l_root->black_h) r_root = r_root -> right_son();
        br_vert<T>* father = r_root->parent(); 
        if(r_root->is_left()){
            if(father!=NULL && !father->is_null) father->hook_up_left(pivot);
        }
        else{
            if(father!=NULL && !father->is_null) father->hook_up_right(pivot);
        }
        pivot ->hook_up_left(l_root);
        pivot ->hook_up_right(r_root); 
        if(pivot->is_root() ) this->root = pivot;
        restore_insert(pivot);
    }
    
    
    
    
    
public:
    void join_right(br_tree<T> r, br_vert<T>* pivot){
        join_right(r.root, pivot);
    }
    
    void join_left(br_tree<T> l, br_vert<T>* pivot){
        join_right(l.root, pivot);
    }
    br_tree(){
        this-> root = new br_vert<T>();
    }
    
    br_tree(br_vert<T>* r):
    root(r)
    {};
    
    int height(){
        return this->root->black_h;
    }
    
    void wypisz(){
        if(this->root != NULL) this->root->wypisz();
        else cout<<"EMPTY"<<endl;
    }
    bool empty(){
        return this->root->is_null || this->root == NULL;
        
    }
    bool insert(T value){
        br_vert<T>* new_vert = this->put_in(value);
        restore_insert(new_vert);
        
    }
    pair<br_tree<T>,br_tree<T> > split(T pivot); 
    
    bool erase(T value); 
    br_vert<T>* lower_bound(T searched);
    
    br_vert<T>* upper_bound(T searched);

    
};

template<class T> 
br_tree<T> join(br_tree<T> left, br_tree<T> right, br_vert<T>* pivot);

template<class T> 
br_tree<T> tree_union(br_tree<T> A, br_tree<T> B);

#include"br_tree.tpp"