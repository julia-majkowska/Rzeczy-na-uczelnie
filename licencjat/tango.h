#include<bits/stdc++.h>
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
        //if(this->has_left()) this->left->wypisz();
        assert(!this->has_left()); //TE ASSERTY POWINNY WRÓCIĆ
        this->not_pref_left_son = l;
        //l->pref_father = this;
    }
    void add_right(tango_tree<T>* r){
        //if(this->has_right()) this->right->wypisz();
        assert(!this->has_right());
        //r->wypisz();
        /*cerr<<endl;
        (r)->wypisz();
        cerr<<endl<<endl;*/
        this->not_pref_right_son = r;
        /*cerr<<"Added right";
        this->wypisz();
        cerr<<endl<<endl;*/
        //r->pref_father = this;
    }
    void remove_left(){
        //if(this->not_pref_left_son!= NULL) this->not_pref_left_son->pref_father = NULL;
        this->not_pref_left_son = NULL;
        
    }
    void remove_right(){
        //if(this->not_pref_right_son!= NULL) this->not_pref_right_son->pref_father = NULL;
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
    
    void reorganize_left(T value){
        if(this->not_pref_left_son != NULL && !this-> not_pref_left_son->empty())
            this->not_pref_left_son->reorganize(value);
    }
    
    void reorganize_right(T value){
        if(this->not_pref_right_son != NULL && !this-> not_pref_right_son->empty())
            this->not_pref_right_son->reorganize(value);
    }
   


};

template<class T>
class tango_tree: public br_tree<T>{
    
    pair<tango_vert<T>*, tango_vert<T>* > find_interval(int d){
        //cerr<<"finding interva l"<<(this->root == NULL)<<endl;
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
        //cerr<<"Before prev i next"<<endl;
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
        //cerr<<"interval_ found\n"<<endl;//<< inter.first->value<<" "<<inter.second->value<<"\n";
        if(inter.first == NULL && inter.second == NULL) return;
        if(inter.first == NULL){
            //cerr<<"first null "<<inter.second->value<<"\n";
            //this->wypisz();
            //cerr<<endl;
            //this->br_tree<T>::wypisz();
            //cerr<<endl;
            splitted_tree<T> s = this->split2(inter.second->value);
            //((tango_tree<T>*) s.lesser) -> wypisz();
            //cerr<<endl;
            ((tango_tree<T>*) s.lesser)->become_unpreferred();
            //((tango_vert<T>*) s.pivot) -> wypisz();
            //cerr<<endl;
            //parent -> remove_right();
            tango_tree<T>* joined = (tango_tree<T>*) join(new tango_tree<T>(), s.greater, s.pivot);
            this->root = joined->root; 
            return;
        }
        if(inter.second == NULL){
            //cerr<<"second null  "<<inter.first->value<<"\n";;
            splitted_tree<T> s = this->split2(inter.first->value);
            
            ((tango_tree<T>*) s.greater)->become_unpreferred();
            
            //((tango_vert<T>*) s.pivot) -> wypisz();
            //cerr<<endl;
            //parent -> remove_left();
            tango_tree<T>* joined = (tango_tree<T>*) join(s.lesser,new  tango_tree<T>(), s.pivot);
            this->root = joined->root; 
            return;
        }
        //cerr<<"both good "<<inter.first->value<<" "<<inter.second->value<<"\n";;
        splitted_tree<T> s1 = this->split2(inter.first->value);
        //if(inter.first->value == candidate->value) ((tango_vert<T>*) s1.pivot) ->remove_right();
        splitted_tree<T> s2 = s1.greater->split2(inter.second->value);
        //if(inter.second->value == candidate->value) ((tango_vert<T>*) s2.pivot) ->remove_left();                                                                                     
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
public:
    
    tango_vert<T>* Root(){
        return (tango_vert<T>*) this->root;
    }
    
    void become_unpreferred(){
        tango_vert<T>* my_root =find_root();
        tango_vert<T>* parent = my_root->pref_father;
        if(my_root == NULL || my_root->is_null) return;
        if(parent == NULL) 
            cerr<<"COŚ DZIWNEGO ODPINAM ROOTA\n";
        if(my_root->dir == RIGHT)
            parent->add_right(this);
        else
            parent->add_left(this);
        
    }
    
    void become_preferred(){
        tango_vert<T>* my_root =find_root();
        tango_vert<T>* parent = my_root->pref_father;
        if(my_root == NULL || my_root->is_null) return;
        //if(parent == NULL) cerr<<"COŚ DZIWNEGO ODPINAM ROOTA\n";
        
        if(my_root->dir == RIGHT)
            parent->remove_right();
        else
            parent->remove_left();
    }
    
    tango_tree(vector<T> v, int p, int k, int h):
    br_tree<T>()
    {
        //cerr<<p<<" "<<k<<" ";
        if(p == k){
           this->root = new tango_vert<T>(v[p], h); 
        }
        else{
        
        int m = (p+k)/2;
        //cerr<<" "<<m<<" "<<v[m]<<"\n";
        tango_tree<T>* left = NULL;
        tango_tree<T>* right = NULL;
        if(m<k)  right =  new tango_tree(v, m+1, k,  h+1);
        if(p<m)  left = new tango_tree(v, p, m-1, h+1);
        this->root = new tango_vert<T>(v[m], h, left, right); 
        }
    }
    tango_tree(const tango_tree<T> &t){
        this->root= t.root;
    }
    
    void wypisz(){
        cerr<<"[ ";//<<endl;
        //cerr<<(this->root == NULL)<<" "<<this->root->is_null<<endl;
        if(this->root != NULL ) ((tango_vert<T>*)this->root)-> wypisz();
        cerr<<" ]";//<<endl;
    }
    
    void reorganize(T value){
        if(this -> root == NULL || this-> root->is_null) return;
        tango_vert<T>* candidate = (tango_vert<T>*) this->root->search(value);
        /*cerr<<"Candidate searched\n";
        this->wypisz();
        cerr<<endl;*/
        if(candidate->value < value && !candidate->has_right()) candidate =  (tango_vert<T>*) candidate->next();
        else if(candidate->value > value && !candidate->has_left()) candidate = (tango_vert<T>*) candidate->prev();
        if(candidate == NULL) return;
        /*if(candidate -> value < value){
            tango_vert<T>* n = (tango_vert<T> *)candidate ->next();
            if(n != NULL && n->depth > candidate->depth) candidate = n; 
        }
        else if (candidate -> value > value){
            tango_vert<T>* p = (tango_vert<T> *)candidate ->prev();
            if(p != NULL && p->depth > candidate->depth) candidate = p; 
        }*/
        
        tango_tree<T>* joined = this;
        if(candidate->value > value){
            //cerr<<"Candidate found "<<candidate->value<<"\n";
            this->cut(candidate);
            //cerr<<"Candidate cut\n";
            //this->wypisz();
            //cerr<<endl;
            //cerr<<"REORG LEFT\n";
            candidate -> reorganize_left(value);
            //cerr<<"Candidate left reorgranized\n"<<((bool) candidate->not_pref_left_son == NULL)<<"\n";
            if(candidate -> not_pref_left_son != NULL){
                //cerr<<"I will be joining ";
                //this->br_tree<T>::wypisz();
                //cerr<<"\n and this ";
                //candidate->not_pref_left_son->br_tree<T>::wypisz();
                //cerr<<endl;
                br_tree<T>* t = tree_union(this, candidate->not_pref_left_son);
                candidate->remove_left();
                //cerr<<"JOINED\n"<<endl;
                joined = (tango_tree<T>*) t;
                
            }
            //cerr<<"Candidate left joined\n";
        }
        else if(candidate->value < value){
            //cerr<<"Candidate found "<<candidate->value<<"\n";
            this->cut(candidate);
            //cerr<<"Candidate cut\n";
            //this->wypisz();
            //cerr<<endl;
            //cerr<<"REORG RIGHT\n";
            candidate -> reorganize_right(value);
            //cerr<<"Candidate right reorgranized\n";
            if(candidate -> not_pref_right_son != NULL){
                //cerr<<"I will be joining ";
                //this->br_tree<T>::wypisz();
                //cerr<<"\n and this ";
                //candidate->not_pref_right_son->br_tree<T>::wypisz();
                //cerr<<endl;
                joined = (tango_tree<T>*) tree_union(this, candidate->not_pref_right_son);
                candidate->remove_right();
                //cerr<<"Candidate right joined\n";
            }
        }
        //cerr<<"Left son pointer "<<joined->root->left_son()<<"\n";
        //joined->root->wypisz();
        //cerr<<endl<<endl;
        //this->wypisz();
        //cerr<<endl<<endl;
        
        this->root = joined->root;
        //this->wypisz();
        //cerr<<endl<<endl;
        
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
