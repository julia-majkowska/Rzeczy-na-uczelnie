#include"br_tree.h"
bool LEFT = true; 
bool RIGHT = false;

template<class T>
class tango_tree;

template<class T>
class tango_vert: public br_vert<T>{
    
public:

   
    tango_tree<T>* not_pref_left_son=NULL; 
    tango_tree<T>* not_pref_right_son=NULL;
    tango_vert<T>* pref_father=NULL;
    bool dir = LEFT;
    
    tango_vert(T val, int d, tango_tree<T> * npls = NULL, tango_tree<T> * nprs = NULL, tango_vert<T>* ps = NULL):
    br_vert<T>(val, d), 
    not_pref_left_son(npls),
    not_pref_right_son(nprs){
        this->depth = d;
        if(npls != NULL && !npls->empty()){
            npls->Root()->pref_father = this;
            npls->Root()->dir = LEFT;
        }
        if(nprs != NULL && !nprs->empty()){
            nprs->Root()->pref_father = this;
            nprs->Root()->dir = RIGHT;
        }
    }
    
    tango_vert<T>* left_son(){
        return (tango_vert<T>*)this->left;
    }
    
    tango_vert<T>* right_son(){
        return (tango_vert<T>*)this->right;
    }
    bool has_left(){
        return this->not_pref_left_son != NULL && (!this->not_pref_left_son->empty());
    }
    bool has_right(){
        return this->not_pref_right_son != NULL && (!this->not_pref_right_son->empty());
    }
    
    void add_left(tango_tree<T>* l){
        assert(!this->has_left()); 
        this->not_pref_left_son = l;
    }
    void add_right(tango_tree<T>* r){
        assert(!this->has_right());
        this->not_pref_right_son = r;
    }
    void remove_left(){
        this->not_pref_left_son = NULL;        
    }
    void remove_right(){
        this->not_pref_right_son =NULL;
    }
    
    tango_vert<T>* leftest(){
        tree_vert<T>* cand  = this;
        while(cand->left_son() != NULL) cand = cand->left_son();
        if(cand->has_left()) return cand->not_pref_left_son->root->leftest();
        else return cand;
    }
    
    tango_vert<T>* rightest(){
        tree_vert<T>* cand  = this;
        while(cand->right_son() != NULL) cand = cand->right_son();
        if(cand->has_right()) return cand->not_pref_right_son->root->rightest();
        else return cand;
    }
    
    bool reorganize_left(T value){
        if(this->not_pref_left_son != NULL && !this-> not_pref_left_son->empty())
            return this->not_pref_left_son->reorganize(value);
        return false;
    }
    
    bool reorganize_right(T value){
        if(this->not_pref_right_son != NULL && !this-> not_pref_right_son->empty())
            return this->not_pref_right_son->reorganize(value);
        return false;
    }
    

};