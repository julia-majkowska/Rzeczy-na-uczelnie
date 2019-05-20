#ifndef BR_VERT_H
#define BR_VERT_H
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
    int min_depth = 1<<30;
    int depth = 0; 
    
    br_vert(T val, int d, bool il = false, bool col = RED, br_vert<T>*f = NULL, br_vert<T>*l = NULL, br_vert<T>*r = NULL):
    tree_vert<T>(val, f, l, r, il),
    color(col)
    {
        depth = d;
        min_depth =d;
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
        this->min_depth = this->depth;
        if(this->left_son() != NULL){
            left_h= this->left_son()->black_h;
            this->max_depth = max(this->max_depth, this->left_son()->max_depth);
            this->min_depth = min(this->min_depth, this->left_son()->min_depth);
        }
        if(this->right_son() != NULL){
            right_h = this->right_son()->black_h;
            this->max_depth = max(this->max_depth, this->right_son()->max_depth);
            this->min_depth = min(this->min_depth, this->right_son()->min_depth);
        }
        this->black_h = right_h + this->color;
        
    }
    
    void wypisz(){
        if(this->is_null){
            return;
        }
        //cout<<"(";
        if(this->left!=NULL) this -> left_son()-> wypisz();
        if(! this-> is_null) cout<<this->value<<" ";//<<this->color<<" "<<this->black_h<<" ";
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
#endif