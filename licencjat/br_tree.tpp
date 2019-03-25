template<class T> 
br_tree<T> join(br_tree<T> left, br_tree<T> right, br_vert<T>* pivot){
    if(left.height() > right.height()){
        left.join_right(right, pivot); 
        return left; 
    }
    else{
        right.join_left(left, pivot); 
        return right; 
    }
}

template<class T> 
br_tree<T> tree_union(br_tree<T> A, br_tree<T> B){
    if(A.empty()) return B; 
    if(B.empty()) return A; 
    pair<br_tree<T>, br_tree<T> > splitted = A.split(B.root->value); 
    br_tree<T> left_subtree(B.root->left_son());
    br_tree<T> right_subtree(B.root->right_son()); 
    B.root->disown_right();
    B.root->disown_left();
    return join(tree_union(splitted.first, left_subtree), tree_union(splitted.second, right_subtree), B.root); 
}

template<class T> 
pair<br_tree<T>,br_tree<T> > br_tree<T>::split(T pivot){//splitting into lesser and greater or equal
        br_vert<T>* pointer = this-> root;
        br_tree<T> l; 
        br_tree<T> r; 
        while(pointer != NULL && !pointer->is_null){
            //cout<<"Current value "<<pointer->value<<"\n";
            br_vert<T> * l_point = pointer->left_son();
            br_vert<T> * r_point = pointer->right_son();
            pointer->disown_left();
            pointer->disown_right();
            if(pointer->value >= pivot){
                r.join_left(r_point, pointer);
                pointer = l_point; 
            }
            else{
                l.join_right(l_point, pointer);
                pointer = r_point; 
            }
            //cout<<"L ";
            //l.wypisz();
            //cout<<"\n R";
            //r.wypisz();
            //cout<<"\n";
            
        }
        vector<br_tree<T> > res; 
        return make_pair(l, r); 
        
    }
    

template<class T> 
bool br_tree<T>::erase(T value){
    br_vert<T>* key = search(value);
    if(key== NULL) return false;
    if(key->is_null) printf("Stop me there is a mistake");
    if(key->value != value) return false;
    if(key->left==NULL || key->right == NULL || key->left->is_null || key->right->is_null) this->remove(key);
    else{
        br_vert<T>* key1 = ((br_vert<T>*) key->next());
        key->value = key1 -> value;
        this->remove(key1);
    }
    return true;
}
template<class T> 
br_vert<T>* br_tree<T>::lower_bound(T searched){
    if(this->empty()) return NULL;
    br_vert<T>* candidate = (br_vert<T>*)search(searched); 
    if(candidate == NULL) return NULL; 
    if(candidate->value > searched) candidate =  ((br_vert<T>*)candidate->prev());
    return candidate;
    
}

template<class T> 
br_vert<T>* br_tree<T>::upper_bound(T searched){
    if(this->empty()) return NULL;
    br_vert<T>* candidate = (br_vert<T>*) search(searched);
    //cout<<candidate->value<<"\n";
    if(candidate == NULL) return NULL;
    if(candidate->value < searched) candidate = ((br_vert<T>*)candidate->next());
    return candidate;
    
}