#include<bits/stdc++.h>
#include"tango_vert.h"


template<class T>
class tango_tree: public br_tree<T>{
    
    pair<tango_vert<T>*, tango_vert<T>* > find_interval(int d){
        if(this->root->max_depth <=  d) return make_pair(((tango_vert<T>*) NULL), ((tango_vert<T>*) NULL));
        tango_vert<T>* cand1 = (tango_vert<T>*)this->root; 
        while(cand1->max_depth >d){
            if(cand1->left_son() == NULL ) break;
            if(cand1->left_son()->max_depth> d) cand1= cand1->left_son();
            else{
                if(cand1->depth > d) break;
                cand1 = (tango_vert<T>*)cand1->right_son();
            }
        }
        
        tango_vert<T>* cand2 = (tango_vert<T>*)this->root; 
        while(cand2->max_depth >d){
            if(cand2->right_son() == NULL) break;
            if(cand2->right_son()->max_depth> d) cand2= cand2->right_son();
            else{
                if(cand2->depth > d) break;
                cand2 = (tango_vert<T>*)cand2->left_son();
            }
        }
        
        cand1 = ((tango_vert<T>*) cand1->prev());
        cand2 = ((tango_vert<T>*) cand2->next());
        return make_pair(cand1, cand2);
    }
    
    tango_vert<T>* find_root(){
        tango_vert<T>* pointer = (tango_vert<T>*) this->root;
        
        while(pointer -> min_depth != pointer -> depth){
            
            if(pointer -> left_son() != NULL && pointer -> left_son() -> min_depth == pointer -> min_depth) pointer = pointer->left_son();
            else pointer = pointer ->right_son();
        }
        return pointer;
    }
    
    void cut(tango_vert<T>* candidate){
        
        pair<tango_vert<T>*, tango_vert<T>* > inter = find_interval(candidate->depth);
        
        if(inter.first == NULL && inter.second == NULL) return;
        if(inter.first == NULL){
            splitted_tree<T> s = this->split2(inter.second->value);
            ((tango_tree<T>*) s.lesser)->become_unpreferred();
            s.greater->insert_vert(s.pivot);
            tango_tree<T>* joined = (tango_tree<T>*) s.greater;//(tango_tree<T>*) join(new tango_tree<T>(), s.greater, s.pivot);
            this->root = joined->root; 
            return;
        }
        if(inter.second == NULL){
            
            splitted_tree<T> s = this->split2(inter.first->value);
            ((tango_tree<T>*) s.greater)->become_unpreferred();
            s.lesser->insert_vert(s.pivot);
            tango_tree<T>* joined = (tango_tree<T>*) s.lesser;//(tango_tree<T>*) join(s.lesser,new  tango_tree<T>(), s.pivot);
            this->root = joined->root; 
            return;
        }
    
        splitted_tree<T> s1 = this->split2(inter.first->value);
        splitted_tree<T> s2 = s1.greater->split2(inter.second->value);
        ((tango_tree<T>*) s2.lesser)->become_unpreferred();
        tango_tree<T>* joined_greater = (tango_tree<T>*) join(new tango_tree<T>(), s2.greater, s2.pivot);
        tango_tree<T>* joined = (tango_tree<T>*) join(s1.lesser, s2.greater, s1.pivot);
        this->root = joined->root; 
        
    }
    
    tango_vert<T>* find_father(){
        tango_vert<T>* root = this -> find_root();
        return root->pref_father;
    }
    
protected : 
    tango_tree ():
    br_tree<T>()
    {}
    
    tango_tree (br_tree<T> t){
        this->root = t.root;
    }
    void make_tree(const vector<T>& v, int p, int k, int h)
    {
        if(p == k){
           this->root = new tango_vert<T>(v[p], h); 
        }
        else{
            int m = (p+k)/2;
            tango_tree<T>* left = NULL;
            tango_tree<T>* right = NULL;
            if(m<k)  right =  new tango_tree(v, m+1, k,  h+1);
            if(p<m)  left = new tango_tree(v, p, m-1, h+1);
            this->root = new tango_vert<T>(v[m], h, left, right); 
        }
    }
    
    tango_tree(const vector<T>& v, int p, int k, int h):
    br_tree<T>()
    {
        make_tree(v, p, k, h);

    }
    
public:
    
    tango_vert<T>* Root(){
        return (tango_vert<T>*) this->root;
    }
    
    void become_unpreferred(){
        tango_vert<T>* my_root =find_root();
        tango_vert<T>* parent = my_root->pref_father;
        if(my_root == NULL || my_root->is_null) return;
        if(parent == NULL) return;
        
        if(my_root->dir == RIGHT)
            parent->add_right(this);
        else
            parent->add_left(this);
        
    }    
    
    tango_tree(vector<T> v):
    br_tree<T>()
    {
        sort(v.begin(), v.end());
        make_tree(v, 0, v.size()-1, 0);
    }
    tango_tree(const tango_tree<T> &t){
        this->root= t.root;
    }
    
    ~tango_tree(){
        if(this->root != NULL){
            delete this->Root();
            this->root = NULL;
        }
    }
    void wypisz(){
        cerr<<"[ ";
        if(this->root != NULL ) ((tango_vert<T>*)this->root)-> wypisz();
        cerr<<" ]";
    }
    
    bool reorganize(T value){
        if(this -> root == NULL || this-> root->is_null) return false;
        tango_vert<T>* candidate = (tango_vert<T>*) this->root->search(value);
        if(candidate->value < value && !candidate->has_right()) candidate =  (tango_vert<T>*) candidate->next();
        else if(candidate->value > value && !candidate->has_left()) candidate = (tango_vert<T>*) candidate->prev();
        if(candidate == NULL) return false;
        bool found = (candidate->value  == value);
        
        tango_tree<T>* joined = this;
        if(candidate->value > value){
            this->cut(candidate);
            found = candidate -> reorganize_left(value);
            if(candidate -> not_pref_left_son != NULL){
                br_tree<T>* t = this->tree_union(candidate->not_pref_left_son);
                candidate->remove_left();
                joined = (tango_tree<T>*) t;
                
            }
        }
        else if(candidate->value < value){
            this->cut(candidate);
            found = candidate -> reorganize_right(value);
            if(candidate -> not_pref_right_son != NULL){
                joined = (tango_tree<T>*) this->tree_union(candidate->not_pref_right_son);
                candidate->remove_right();
            }
        }
        
        this->root = joined->root;
        return found;
        
    }
    
    
    int size(){
        return this->Root()->size();
    }
    
    vector<int> content(){
        return this->Root()->content();
    }
    
    bool find(T value){
        bool res = reorganize(value);
        tango_vert<T>* cand = ((tango_vert<T>*) this->root->tree_vert<T>::search(value));
        assert(res == (cand -> value == value));
        if(cand -> value == value)return true;
        return false;
    }
    
};
