#include<bits/stdc++.h>
#include"br_tree.h"
bool LEFT = true; 
bool RIGHT = false;

template<class T>
class tango_tree;

template<class T>
class tango_vert: public br_vert<T>{
    
public:
   
    
    tango_tree<T>* not_pref_left_son; 
    tango_tree<T>* not_pref_right_son;
    tango_vert<T>* pref_father; 
    bool my_dir; 
    
    bool has_left(){
        return this->not_pref_left_son != NULL && !this->not_pref_left_son->empty();
    }
    bool has_right(){
        return this->not_pref_right_son != NULL && !this->not_pref_right_son->empty();
    }
    
    void add_left(tango_tree<T> l){
        assert(!this->has_left());
        this->not_pref_left_son = &l;
    }
    void add_right(tango_tree<T> r){
        assert(!this->has_right());
        this->not_pref_right_son =r;
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
    
    void reorganize_left(T value){
        if(this->not_pref_left_son != NULL && !this-> not_pref_left_son->empty())
            this->not_pref_left_son->reorganize(value);
    }
    
    void reorganize_right(T value){
        if(this->not_pref_right_son != NULL && !this-> not_pref_right_son->empty())
            this->not_pref_right_son->reorganize(value);
    }
    

    /*void next(){
        if(this->has_right()) return this->not_pref_right_son->leftest();
        tango_vert<T>* cand = tree_vert::next();
        if(cand->min_depth > this->min_depth){
            if(cand->has_left) return cand->not_pref_left_son->leftest();
            else return cand;
        }
        if(cand->is_root() && cand->value<this->value){
            
        }
    }*/
};

template<class T>
class tango_tree: public br_tree<T>{
    
    pair<tango_vert<T>*, tango_vert<T>* > find_interval(int d){
        tango_vert<T>* cand1 = (tango_vert<T>*)this->root; 
        while(cand1->max_depth >d){
            if(cand1->left_son()->max_depth> d) cand1= (tango_vert<T>*)cand1->left_son();
            else{
                if(cand1->min_depth >= d) break;
                cand1 = (tango_vert<T>*)cand1->right_son();
            }
        }
        tango_vert<T>* cand2 = (tango_vert<T>*)this->root; 
        while(cand2->max_depth >d){
            if(cand2->right_son()->max_depth> d) cand2= (tango_vert<T>*)cand2->right_son();
            else{
                if(cand2->min_depth >= d) break;
                cand2 = (tango_vert<T>*)cand2->left_son();
            }
        }
        return make_pair(cand1, cand2);
    }
    
    void cut(tango_vert<T>* candidate){
        
        pair<tango_vert<T>*, tango_vert<T>* > inter = find_interval(candidate->min_depth);
        cout<<"Interval found "<< inter.first->value<<" "<<inter.second->value<<"\n";
        splitted_tree<T> s1 = this->split2(inter.first->value);
        pair<tango_tree<T>, tango_tree<T> > s2 = s1.greater.split(inter.second->value);
        inter.second->add_left(s2.first);
        tango_tree<T> joined = join(s1.lesser, s2.second, s1.pivot);
        this->root = joined.root; 
    }
public:
    tango_tree ():
    br_tree<T>()
    {}
    
     tango_tree (br_tree<T> t){
        this->root = t.root;
    }
    void reorganize(T value){
        if(this -> root == NULL || this-> root->is_null) return;
        tango_vert<T>* candidate = (tango_vert<T>*) this->root->search(value);
        cout<<"Candidate searched\n";
        //if(candidate->value < value && !candidate->has_right()) candidate =  (tango_vert<T>*) candidate->next();
        //if(candidate->value > value && !candidate->has_left()) candidate = (tango_vert<T>*) candidate->prev();
        cout<<"Candidate found\n";
        this->cut(candidate);
        cout<<"Candidate cut\n";
        tango_tree<T> joined = *this;
        if(candidate->value > value){
            candidate -> reorganize_left(value);
            cout<<"Candidate left reorgranized\n";
            if(candidate -> not_pref_left_son != NULL) joined = (tango_tree<T>) tree_union(*this, *candidate->not_pref_left_son);
            cout<<"Candidate left joined\n";
        }
        else if(candidate->value < value){
            candidate -> reorganize_right(value);
            cout<<"Candidate right reorgranized\n";
            if(candidate -> not_pref_right_son != NULL) joined = (tango_tree<T>) tree_union(*this, *candidate->not_pref_right_son);
            cout<<"Candidate right joined\n";
        }
        this->root = joined.root;
        
    }
    
    
 
    bool insert(T value){
        reorganize(value);
        br_tree<T>::insert(value);
        
    }
    
    bool find(T value){
        reorganize(value);
        tango_vert<T>* cand = ((tango_vert<T>*) this->root->tree_vert<T>::search(value));
        if(cand -> value == value) return true;
        return false;
    }
    
};
