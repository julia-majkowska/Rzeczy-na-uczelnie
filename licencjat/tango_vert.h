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
        if(this->left!= NULL){
            
        }
        if(nprs != NULL && !nprs->empty()){
            nprs->Root()->pref_father = this;
            nprs->Root()->dir = RIGHT;
        }
    }
    
    void wypisz(){
        if(this->is_null) return;
        if(this->left!=NULL) this -> left_son()-> wypisz();
        if(this->has_left()) this->not_pref_left_son->wypisz();
        if(this->has_right()) this->not_pref_right_son->wypisz();
        if(this->right!=NULL) this -> right_son()-> wypisz();
        
    }
    
    ~tango_vert(){
        if(this->left!=NULL){
            delete this->left_son();
            this->left = NULL;
        }
        
        if(this->right!=NULL){
            delete this->right_son();
            this->right = NULL;
        }
        
        if(this->not_pref_left_son!=NULL){
            delete this->not_pref_left_son;
            this->not_pref_left_son = NULL;
        }
        
        if(this->not_pref_right_son!=NULL){
            delete this->not_pref_right_son;
            this->not_pref_right_son = NULL;
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
        if(this->not_pref_left_son!= NULL){
            this->not_pref_left_son->root  = NULL;
            delete not_pref_left_son;
        }
        this->not_pref_left_son = NULL;        
    }
    void remove_right(){
        if(this->not_pref_right_son!= NULL){
            this->not_pref_right_son->root  = NULL;
            delete not_pref_right_son;
        }
        this->not_pref_right_son =NULL;
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
