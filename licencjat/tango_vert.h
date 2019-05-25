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
        //cerr<<"ISNULL "<<this->is_null<<"\n";
        if(this->is_null) return;
        cerr<<"(";
        if(this->left!=NULL) this -> left_son()-> wypisz();
        //cerr<<"{";//<<endl;
        //cerr<<(this->not_pref_left_son == NULL)<<" "<<(this->has_left())<<endl;
        if(this->has_left()) this->not_pref_left_son->wypisz();
        //cerr<<"left "<<endl;
        cerr<<this->value<<" ";//","<< this -> color<<", "<<black_h;
        //cerr<<"val "<<endl;
        //cerr<<this->has_right();//<<" "<<endl;
        if(this->has_right()) this->not_pref_right_son->wypisz();
        //cerr<<"}";//<<endl;//<<endl;
        if(this->right!=NULL) this -> right_son()-> wypisz();
        cerr<<")";//<<endl;//<<endl;
        
    }
    
    ~tango_vert(){
        //cout<<"Deleting "<<this->value<<"\n";
        //this->wypisz();
        //cout<<endl;
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
        // cout<<"Deleted "<<this->value<<"\n";
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
    
    /*tango_vert<T>* leftest(){
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
    }*/
    
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
