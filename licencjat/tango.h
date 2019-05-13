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
    
    tango_vert(T val, int d, tango_tree<T> * npls = NULL, tango_tree<T> * nprs = NULL, tango_vert<T>* ps = NULL):
    br_vert<T>(val, d), 
    not_pref_left_son(npls),
    not_pref_right_son(nprs){
        this->depth = d;
        if(npls != NULL) npls->pref_father = this;
        if(nprs != NULL) nprs->pref_father = this;
    }
    
    void wypisz(){
        //cout<<"ISNULL "<<this->is_null<<"\n";
        if(this->is_null) return;
        cout<<"(";
        if(this->left!=NULL) this -> left_son()-> wypisz();
        cout<<"{";//<<endl;
        //cout<<(this->not_pref_left_son == NULL)<<" "<<(this->has_left())<<endl;
        if(this->has_left()) this->not_pref_left_son->wypisz();
        //cout<<"left "<<endl;
        cout<<this->value<<" ";//","<< this -> color<<", "<<black_h;
        //cout<<"val "<<endl;
        //cout<<this->has_right();//<<" "<<endl;
        if(this->has_right()) this->not_pref_right_son->wypisz();
        cout<<"}";//<<endl;//<<endl;
        if(this->right!=NULL) this -> right_son()-> wypisz();
        cout<<")";//<<endl;//<<endl;
        
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
        l->pref_father = this;
    }
    void add_right(tango_tree<T>* r){
        assert(!this->has_right());
        //r->wypisz();
        /*cout<<endl;
        (r)->wypisz();
        cout<<endl<<endl;*/
        this->not_pref_right_son = r;
        /*cout<<"Added right";
        this->wypisz();
        cout<<endl<<endl;*/
        r->pref_father = this;
    }
    void remove_left(){
        if(this->not_pref_left_son!= NULL) this->not_pref_left_son->pref_father = NULL;
        this->not_pref_left_son = NULL;
        
    }
    void remove_right(){
        if(this->not_pref_right_son!= NULL) this->not_pref_right_son->pref_father = NULL;
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
        //cout<<"finding interva l"<<(this->root == NULL)<<endl;
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
        //cout<<"Before prev i next"<<endl;
        cand1 = ((tango_vert<T>*) cand1->prev());
        cand2 = ((tango_vert<T>*) cand2->next());
        return make_pair(cand1, cand2);
    }
    
    void cut(tango_vert<T>* candidate){
        
        pair<tango_vert<T>*, tango_vert<T>* > inter = find_interval(candidate->depth);
        //cout<<"interval_ found\n"<<endl;//<< inter.first->value<<" "<<inter.second->value<<"\n";
        if(inter.first == NULL && inter.second == NULL) return;
        if(inter.first == NULL){
            //cout<<"first null "<<inter.second->value<<"\n";
            //this->br_tree<T>::wypisz();
            //cout<<endl;
            splitted_tree<T> s = this->split2(inter.second->value);
            //((tango_tree<T>*) s.lesser) -> wypisz();
            //cout<<endl;
            ((tango_vert<T>*) s.pivot) -> add_left((tango_tree<T>*) s.lesser);
            //((tango_vert<T>*) s.pivot) -> wypisz();
            //cout<<endl;
            tango_tree<T>* joined = (tango_tree<T>*) join(new tango_tree<T>(), s.greater, s.pivot);
            this->root = joined->root; 
            return;
        }
        if(inter.second == NULL){
            //cout<<"second null  "<<inter.first->value<<"\n";;
            splitted_tree<T> s = this->split2(inter.first->value);
            
            ((tango_vert<T>*) s.pivot) -> add_right((tango_tree<T>*) s.greater);
            //((tango_vert<T>*) s.pivot) -> wypisz();
            //cout<<endl;
            tango_tree<T>* joined = (tango_tree<T>*) join(s.lesser,new  tango_tree<T>(), s.pivot);
            this->root = joined->root; 
            return;
        }
        //cout<<"both good";
        splitted_tree<T> s1 = this->split2(inter.first->value);
        splitted_tree<T> s2 = s1.greater->split2(inter.second->value);
        ((tango_vert<T>*)s2.pivot)->add_left((tango_tree<T>*)s2.lesser);
        tango_tree<T>* joined = (tango_tree<T>*) join(s1.lesser, s2.greater, s1.pivot);
        this->root = joined->root; 
        
    }
    
protected : 
    tango_tree ():
    br_tree<T>()
    {}
    
    tango_tree (br_tree<T> t){
        this->root = t.root;
    }
public:
    tango_vert<T>* pref_father; 
    tango_tree(vector<T> v, int p, int k, int h):
    br_tree<T>()
    {
        //cout<<p<<" "<<k<<" ";
        if(p == k){
           this->root = new tango_vert<T>(v[p], h); 
        }
        else{
        
        int m = (p+k)/2;
        //cout<<" "<<m<<" "<<v[m]<<"\n";
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
        cout<<"[ ";//<<endl;
        //cout<<(this->root == NULL)<<" "<<this->root->is_null<<endl;
        if(this->root != NULL ) ((tango_vert<T>*)this->root)-> wypisz();
        cout<<" ]";//<<endl;
    }
    
    void reorganize(T value){
        if(this -> root == NULL || this-> root->is_null) return;
        tango_vert<T>* candidate = (tango_vert<T>*) this->root->search(value);
        /*cout<<"Candidate searched\n";
        this->wypisz();
        cout<<endl;*/
        //if(candidate->value < value && !candidate->has_right()) candidate =  (tango_vert<T>*) candidate->next();
        //if(candidate->value > value && !candidate->has_left()) candidate = (tango_vert<T>*) candidate->prev();
        
        
        tango_tree<T>* joined = this;
        if(candidate->value > value){
            //cout<<"Candidate found "<<candidate->value<<"\n";
            this->cut(candidate);
            /*cout<<"Candidate cut\n";
            this->wypisz();
            cout<<endl;
            cout<<"REORG LEFT\n";*/
            candidate -> reorganize_left(value);
            //cout<<"Candidate left reorgranized\n"<<((bool) candidate->not_pref_left_son == NULL)<<"\n";
            if(candidate -> not_pref_left_son != NULL){
                //cout<<"left son pointer "<<candidate->not_pref_left_son<<"\n";
                br_tree<T>* t = tree_union(this, candidate->not_pref_left_son);
                candidate->remove_left();
                //cout<<"JOINED\n"<<endl;
                joined = (tango_tree<T>*) t;
                
            }
            //cout<<"Candidate left joined\n";
        }
        else if(candidate->value < value){
            //cout<<"Candidate found "<<candidate->value<<"\n";
            this->cut(candidate);
            //cout<<"Candidate cut\n";
            //this->wypisz();
            //cout<<endl;
            //cout<<"REORG RIGHT\n";
            candidate -> reorganize_right(value);
            //cout<<"Candidate right reorgranized\n";
            if(candidate -> not_pref_right_son != NULL){
                /*cout<<"I will be joining ";
                this->br_tree<T>::wypisz();
                cout<<"\n and this ";
                candidate->not_pref_right_son->br_tree<T>::wypisz();
                cout<<endl;*/
                joined = (tango_tree<T>*) tree_union(this, candidate->not_pref_right_son);
                candidate->remove_right();
                //cout<<"Candidate right joined\n";
            }
        }
        //cout<<"Left son pointer "<<joined.root->left_son()<<<"\n";
        /*joined.root->wypisz();
        cout<<endl<<endl;
        this->wypisz();
        cout<<endl<<endl;*/
        
        this->root = joined->root;
        /*this->wypisz();
        cout<<endl<<endl;*/
        
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
