#include<bits/stdc++.h>
#include"tree_vert.h"
#include <cassert>

using namespace std;
const bool RED = false;
const bool BLACK = true;
template<class T>
class br_vert: public tree_vert{
    
public: 
    bool color; //false - red , true - black
    int black_h;
    br_vert(T val, col = RED, tree_vert<T>*f = NULL, tree_vert<T>*l = NULL, tree_vert<T>*r = NULL):
    tree_vert(val, f, l, r),
    color(col)
    {};
    br_vert(col = 0, tree_vert<T>*f = NULL, tree_vert<T>*l = NULL, tree_vert<T>*r = NULL)://constructor for an empty leaf
    color(col)
    {
        T val;
        tree_vert(val, f, l, r),
    };
    bool is_red(){
        return !this->color;
    }
    bool is_black(){
        return this->color;
    }
    br_vert* grandparent(){
        if(this->father == NULL) return NULL;
        return this->father->father; 
    }
    
    br_vert* uncle(){
        if(this->father == NULL || this->grandparent() == NULL) return NULL;
        if(this->father -> is_left()) return this->grandparent()->right;
        return this->grandparent()->left();
    }
    
    br_vert* brother(){
        if(this->father == NULL) return NULL;
        if(this-> is_left()) return this->father->right;
        return this->father->left();
    }
    
    void update_black_height(){
        assert(this->left->black_h == this->right->black_h);
        this->black_h = this->left->black_h + this->color;
    }
    

}

bool is_black(br_vert<T>* x){
    if(x == NULL) return true;
    return x->color == BLACK;
}

bool is_red(br_vert<T>* x){
    return x!= NULL && x->color == RED;
}

template<class T>
class br_tree{
    
    br_vert<T>* root; 
protected: 
    br_vert<T>* put_in(T value){
        br_vert<T>* pointer = root; 
        br_vert<T>* new_vert = new br_vert<T>(value);
        while(true){
            if(pointer->value < value ){
                if(pointer->hook_up_right(new_vert)) return new_vert;
                pointer = pointer->right;
            }
            if(pointer->value == value) return pointer;
            if(pointer->value > value ){
                if(pointer->hook_up_left(new_vert)) return new_vert;
                pointer = pointer->left;
            }
        }
    }
    
    void restore_insert(br_vert<T>* x){
        while(!x.is_root() && x->parent->is_red()){
            //P1a
            if(x->father.is_root()){
                x->father->color = BLACK;//root is black
                x->father->update_black_height();
                return;
            }
            
            //P1b
            if(x->father.is_red() && x->uncle().is_red()){
                x->father->color = BLACK; 
                x->father->update_black_height();
                x->uncle()->color = BLACK;
                x->uncle()->update_black_height();
                x->grandparent()->color = RED;
                x->grandparent()->update_black_height();
                x = x -> grandparent();
                continue;
            }
            
            if(x->father.is_red() && x->uncle().is_black()){
                if(x->father->is_left()){
                    if(x->is_right){//P2
                        x->rotate_left();
                        x = x->left;//previous parent
                    }
                    
                    //P3
                    x->father->color = BLACK; 
                    x->grandparent()->color = RED;
                    x->parent->rotate_right();
                    continue;
                }
                else{
                    if(x->is_left){//P2
                        x->rotate_right();
                        x = x->right;//previous parent
                    }
                    
                    //P3
                    x->father->color = BLACK; 
                    x->grandparent()->color = RED;
                    x->parent->rotate_left();
                    continue;
                }
                x-> update_black_height();
                x-> brother -> update_black_height();
                x-> father->update_black_height();
            }            
        }
        this->root->color = BLACK;
    }
    
    void remove(br_vert<T>* x){
        br_ver<T>* child = x->left? x->left : x->right;
        if(x->is_root()){
            this->root = child;
            delete x;
            return;
        }
        
        br_vert<T>*par = x->father;
        x->get_disowned();
        child->hook_onto(par);
        if(x->is_red()) return;
        if(child->is_red()){
            child->color = BLACK;
            return;
        }
        delete x;
        x = child; 
        while(!x->is_root()){
            
            br_vert<T>* brother = x->brother();
            if(brother -> is_red()){
                //case2
                x->parent->color = RED;
                brother -> colot = BLACK;
                if(brother->is_left()) brother->rotate_left();
                else brother->rotate_right();
            }
            //case 3
            brother = x->brother();
            if(x->father.is_
        }
        
    }
    
public:
    bool insert(T value){
        br_vert<T>* new_vert = this->put_in(value);
        restore_insert(new_vert);
        
    }
    vector<br_vert<T>*> split(){
        br_vert<T>* pointer = this-> root; 
        
        
    }
    bool erase(T value){
        br_vert<T>* key = this->root->search(value);
        if(key->value != value) return false;
        if(key->left==NULL || key->right == NULL) this->remove(key);
        else{
            br_vert<T>* key1 = key->next();
            key->value = key1 -> value;
            this->remove(key1);
        }
    }
    
    
}