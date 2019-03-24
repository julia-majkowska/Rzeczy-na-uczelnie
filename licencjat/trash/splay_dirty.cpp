#include<bits/stdc++.h>

using namespace std;

template<class T>
class splay_vert{
public:
    
    T value;
    
    splay_vert<T>* father;
    splay_vert<T>* left;
    splay_vert<T>* right;
    
    splay_vert(T val, splay_vert<T>*f = NULL, splay_vert<T>*l = NULL, splay_vert<T>*r = NULL):
    value(val),
    father(f),
    left(l),
    right(r)
    {};
    
    void wypisz(){
        cout<<"(";
        if(this->left!=NULL) this -> left-> wypisz();
        cout<<"| "<<this->value<<"|";
        if(this->right!=NULL) this -> right-> wypisz();
        cout<<")";
    }
    
    void disown_left(){
       if(this->left!= NULL){
           this->left->father = NULL;
           this->left = NULL;
       }
    };
    
    void disown_right(){
       if(this->right!= NULL){
           this->right->father = NULL;
           this->right = NULL;
       }
    };
    
    bool hook_up_left(splay_vert<T>* l){
        if(this -> left != NULL) return false; 
        this -> left = l;
        if(l != NULL ) l-> father = this; 
        return true; 
    };
    
    bool hook_up_right(splay_vert<T>*r){
        if(this -> right != NULL) return false; 
        this -> right = r;
        if(r != NULL ) r-> father = this; 
        return true; 
    };
        
    bool hook_onto(splay_vert<T>* new_father){
        this -> father = new_father;
        if(new_father == NULL) return false;
        if(new_father->value < this->value) new_father->hook_up_right(this);
        else new_father->hook_up_right(this);
        return true;
    }
    
    bool get_disowned(){
        if(this->father == NULL) return false; 
        if(this->is_left()) this->father->disown_left();
        else this->father->disown_right();
        return true;
    }
    
    bool is_root(){
       return this->father == NULL;  
    };
    
    bool is_left(){
        return this->father->left == this;       
    };
    
    bool is_right(){
        return this->father->right == this;
    };
    
    
    
    void ZIGleft(){// rotating x left once with the root (parent) prereq : parent is not NULL, x right son
        //cout<<"ZIGleft\n";
        splay_vert* f = this-> father; 
        splay_vert* b = this-> left;
        
        f-> disown_right();//cutting x off
        this-> disown_left(); 
        this-> hook_up_left(f);
        f-> hook_up_right(b);
    };
    
    void ZIGright(){ // rotating x right once with the root (parent) prereq : parent is not NULL, x left son
        //cout<<"ZIGright\n";
        splay_vert* f = this-> father; 
        splay_vert* b = this-> right;
        
        f-> disown_left();//cutting x off
        this-> disown_right(); 
        this-> hook_up_right(f);
        f-> hook_up_left(b);
        
    };
    
    void ZIGZIGleft(){
        //cout<<"ZIGZIGleft\n";
        splay_vert* f = this-> father; 
        splay_vert* gf = this-> father -> father;
        splay_vert* ggf = this->father -> father->father;
        splay_vert* a = this-> right; 
        splay_vert* b = this-> left; 
        splay_vert* c = this-> father-> left;
        
        gf->get_disowned();
        this-> disown_left();
        f-> disown_right();// cutting off x
        f-> disown_left();
        gf -> disown_right();
        
        this-> hook_up_left(f);
        f-> hook_up_right(b);
        f-> hook_up_left(gf);
        gf->hook_up_right(c);
        this->hook_onto(ggf);
    };
    
    void ZIGZIGright(){ // rotating x right twice with parent and grandparent - x and father both left sons
        //cout<<"ZIGZIGright\n";
        splay_vert* f = this-> father; 
        splay_vert* gf = this-> father -> father; 
        splay_vert* ggf = this->father -> father->father;
        splay_vert* a = this-> left; 
        splay_vert* b = this-> right; 
        splay_vert* c = this-> father-> right;
        
        gf->get_disowned();
        this-> disown_right();
        f-> disown_right();
        f-> disown_left();// cutting off x
        gf -> disown_left();
        
        this-> hook_up_right(f);
        f-> hook_up_left(b);
        f-> hook_up_right(gf);
        gf->hook_up_left(c);
        this->hook_onto(ggf);
    };
    
    void ZIGZAGleftright(){// rotating x left then right with parent and grandparent - x is right and father left son
        //cout<<"ZIGZAGleftright\n";
        splay_vert* f = this-> father; 
        splay_vert* gf = this-> father -> father;
        splay_vert* ggf = this->father -> father->father;
        splay_vert* b = this-> left; 
        splay_vert* c = this-> right; 
        
        gf->get_disowned();
        this-> disown_left();
        this-> disown_right();
        f-> disown_right();
        gf -> disown_left();
        f-> hook_up_right(b); 
        gf-> hook_up_left(c);
        this-> hook_up_left(f);
        this-> hook_up_right(gf);
        this->hook_onto(ggf);
    };
    
    void ZIGZAGrightleft(){// rotating x right then left with parent and grandparent - x is left and father right son
        //cout<<"ZIGZAGrightleft\n";
        splay_vert* f = this-> father; 
        splay_vert* gf = this-> father -> father;
        splay_vert* ggf = this->father -> father->father;  
        splay_vert* b = this-> right; 
        splay_vert* c = this-> left; 
        
        gf->get_disowned();
        this-> disown_left();
        this-> disown_right();
        f-> disown_left();
        gf -> disown_right();
        f-> hook_up_left(b); 
        gf-> hook_up_right(c);
        this-> hook_up_right(f);
        this-> hook_up_left(gf);
        this->hook_onto(ggf);
        
    };
    
    void splay(){
        
        if(this-> is_root()) return; 
        if(this-> is_left()){
            if(this-> father-> is_root()){
                this->ZIGright(); 
                return; 
            }
            if(this->father-> is_left()){
                this->ZIGZIGright();
                return;
            }
            if(this->father-> is_right()){
                this->ZIGZAGrightleft();
                return;
            }
        }
        else{
            if(this-> father-> is_root()){
                this->ZIGleft(); 
                return; 
            }
            if(this->father-> is_left()){
                this->ZIGZAGleftright();
                return;
            }
            if(this->father-> is_right()){
                this->ZIGZIGleft();
                return;
            } 
        }
                
    };
    
};


template<class T>
class splay_tree{
    
    
public:
    splay_vert<T>* root;
    splay_tree(){
        root = NULL;
    };
    splay_tree(splay_vert<T>* r){
        root = r;
    };
    
protected:
    
    splay_vert<T>* search( T splay_value ){
        splay_vert<T>* pointer = this -> root; 
        while( pointer -> value!= splay_value) {
            if( pointer -> value < splay_value ){
                if(pointer-> right == NULL) return pointer; 
                pointer = pointer-> right; 
            }
            else{
                if(pointer-> left == NULL) return pointer; 
                pointer = pointer-> left;                
            }
        }
        return pointer;
    };
    
    
public:
    
    void wypisz(){
        if(this-> root!= NULL) this->root->wypisz(); 
    }
    
    void splay(T splay_value){
        splay_vert<T>* new_root = search(splay_value); 
        while(!new_root->is_root()){
            new_root->splay();
        }
        this -> root = new_root;
        
    };
    
    T find(T searched){
        T res; 
        if(this ->root == NULL) return res;
        splay(searched);
        return this->root->value;
    };
    
    void insert(T value);
    void erase(T value);
};

template<class T>
vector<splay_tree<T>* > split(splay_tree<T>* tree, T searched){// spliting between less that,equal and greater than
    if(tree->root == NULL){
        vector<splay_tree<T>* > result;
        splay_tree<T> * empty1 = new splay_tree<T>();
        result.push_back(empty1);
        splay_tree<T> * empty2 = new splay_tree<T>();
        result.push_back(empty2);
        return result;
    }
    tree->splay(searched);
    vector<splay_tree<T>* > result;
    if(tree->root->value > searched){
        splay_tree<T>* lesser = new splay_tree<T>(tree->root->left);
        result.push_back(lesser); 
        tree->root->disown_left();
        result.push_back(tree);
        return result;
    }
    if(tree->root->value < searched){
        splay_tree<T>* greater = new splay_tree<T>(tree->root->right);
        tree->root->disown_right();
        result.push_back(tree);
        result.push_back(greater);
        return result;
    }
    if(tree->root->value == searched){
        splay_tree<T>* lesser = new splay_tree<T>(tree->root->left);
        result.push_back(lesser); 
        tree->root->disown_left();
        
        splay_tree<T>* greater = new splay_tree<T>(tree->root->right);
        tree->root->disown_right();
        result.push_back(tree);
        result.push_back(greater);
        return result;
    }
}
template<class T>
splay_tree<T> join( splay_tree<T>* lesser, splay_tree<T>* greater){
    if(lesser->root == NULL) return greater->root;
    lesser->find(greater->root->value);
    lesser->root->hook_up_right(greater->root);
    return lesser-> root;
}
template<class T>
void splay_tree<T>::insert(T value){
    splay_vert<T>* new_root = new splay_vert<T>(value);
    if(this -> root == NULL){
        this ->root = new_root;
        printf("HAPPY FIRST ONE\n");
        return;
    }
    T pivot = this->find(value); 
    if(pivot == value) return; 
    vector<splay_tree<T>*> halves = split(this, value);
    new_root->hook_up_left(halves[0]->root); 
    new_root-> hook_up_right(halves[1]->root);
    this -> root = new_root;
}

template<class T>
void splay_tree<T>::erase(T value){
    T pivot = this->find(value); 
    if(pivot != value) return; 
    vector<splay_tree<T>*> halves = this -> split(value);
    this -> root = join(halves[0]->root, halves[2]->root);
}

int main(){
    
    int n;
    scanf("%d", &n);
    splay_tree<int> drzewo;
    for(int i =0; i<n; i++){
        int a; 
        scanf("%d",&a);
        drzewo.insert(a);
        drzewo.wypisz();
    }
    
    int q;
    scanf("%d", &q);
    for(int i =0; i<q; i++){
        int a; 
        scanf("%d",&a);
        printf("%d\n", drzewo.find(a));
        drzewo.wypisz();
    }
    
}