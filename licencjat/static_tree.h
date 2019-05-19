#include<bits/stdc++.h>
#include"tree_vert.h"
using namespace std;

template<class T>
class static_tree{
    tree_vert<T>* root;
    tree_vert<T>* rek_tree(int* rt, int n, int i, int j, vector<int>& values ){
        if(i == j) return new tree_vert<T>(values[i]);
        int my_root = rt[n*i + j]; 
        tree_vert<T>* l = NULL;
        if(my_root > i)  l = rek_tree(rt, n, i, my_root -1, values);
        tree_vert<T>* r = NULL;
        if(my_root < j)  r = rek_tree(rt, n, my_root + 1,j, values);
        return new tree_vert<T>(values[my_root], NULL, l, r);      
    }
    
    void make_tree(vector<T> queries){
        vector<pair<T, int> > counts;
        sort(queries.begin(), queries.end());
        T prev; 
        int counter = 0;
        for(int i = 0; i<queries.size(); i++){
            
            if(i == 0 || prev != queries[i]){
                if(i != 0) counts.push_back(make_pair(prev, counter));
                prev = queries[i];
                counter = 0;
            }
            counter++;
        }
        
        
        counts.push_back(make_pair(prev, counter));
        
        sort(counts.begin(), counts.end());
        vector<T> values; 
        for(int i = 0; i<counts.size(); i++){
            //cerr<<counts[i].first<<" "<<counts[i].second<<"|";
            values.push_back(counts[i].first);
            
        }
        
        
        int n = counts.size();
        long long sum[n+1];
        sum[0] = counts[0].second;
        for(int i = 1; i<n; i++) sum[i] = sum[i-1] + counts[i].second;
        long long cost[n+1][n+1];
        int r[n][n];
        for(int i = 0; i<n; i++){
            cost[i][i] = counts[i].second; 
            r[i][i] = i;
        }
        for(int dl = 1; dl <n; dl++){
            for(int i = 0; i+dl<n; i++){
                int j = dl + i;
                cost[i][j]  = __INT64_MAX__;
                for(int kand = r[i][j-1]; kand <= r[i+1][j]; kand++){
                    long long cost_left = 0, cost_right = 0; 
                    if(i < kand)   cost_left = cost[i][kand -1];
                    
                    if(kand+1 < n) cost_right = cost[kand+1][j];
                    
                    long long total_cost = cost_left + cost_right + sum[j]; 
                    if(i > 0 ) total_cost-= sum[i-1];
                    if(total_cost < cost[i][j]){
                        r[i][j] = kand; 
                        cost[i][j] = total_cost; 
                    }
                }
            }
        }
        
        this->root = rek_tree((int *)r, n, 0, n-1,  values);
    }
public:
    static_tree(vector<T> queries){
        make_tree(queries);
    }
    
    ~static_tree(){
        if(this->root != NULL){
            delete this->root; 
            this->root = NULL;
        }
    }
    
    void wypisz(){
        this->root->wypisz();
    }
    
    bool find(T val){
        if(this->root == NULL) return false;
        tree_vert<T>* candidate = this -> root -> search(val);
        return candidate->value == val;
    }
};