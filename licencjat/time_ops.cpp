#include<bits/stdc++.h>
#include"tango.h"
#include"splay.h"
#include"static_tree.h"


using namespace std;

const int qs[] = {10, 100, 1000, 10000, 100000, 1000000};
const int num_reps = 50;

vector<double> experiment_ops(int n, int seed){
    splay_tree<int> d_splay;
    br_tree<int> d_br;
    set<int> d_set;
    
    vector<int> liczby; 
    for(int i = 1; i<=n; i++){
        liczby.push_back(i);       
    }
    srand(seed);
    random_shuffle(liczby.begin(), liczby.end());
    std::chrono::duration<double> ttsplayi(0.0), ttbri(0.0), ttseti(0.0); 
    for(int i = 0; i<n; i++){
        std::chrono::duration<double> elapsed_seconds;
        std::chrono::time_point<std::chrono::system_clock> start, end;
        int val = liczby[i];
        start = chrono::system_clock::now();
        d_splay.insert(val);
        end = chrono::system_clock::now();
        elapsed_seconds = end - start; 
        ttsplayi += elapsed_seconds;
        
        start = chrono::system_clock::now();
        d_br.insert(val);
        end = chrono::system_clock::now();
        elapsed_seconds = end - start; 
        ttbri += elapsed_seconds;
        
        start = chrono::system_clock::now();
        d_set.insert(val);
        end = chrono::system_clock::now();
        elapsed_seconds = end - start; 
        ttseti += elapsed_seconds;
    }
    
    vector<double> res;
    res.push_back(ttsplayi.count());
    res.push_back(ttbri.count());
    res.push_back(ttseti.count());
    std::chrono::duration<double> ttsplay(0.0),ttbr(0.0), ttset(0.0); 
    random_shuffle(liczby.begin(), liczby.end());
    for(int i = 0; i< liczby.size(); i++){
        int val = liczby[i];
        
        std::chrono::duration<double> elapsed_seconds;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = chrono::system_clock::now();
        d_splay.erase(val);
        end = chrono::system_clock::now();
        elapsed_seconds = end - start; 
        ttsplay += elapsed_seconds;
        
        
        start = chrono::system_clock::now();
        d_br.erase(val);
        end = chrono::system_clock::now();
        elapsed_seconds = end - start; 
        ttbr += elapsed_seconds;
        
        start = chrono::system_clock::now();
        d_set.erase(val);
        end = chrono::system_clock::now();
        elapsed_seconds = end - start; 
        ttset += elapsed_seconds;
        
    }
    res.push_back(ttsplay.count());
    res.push_back(ttbr.count());
    res.push_back(ttset.count());
    d_br.destroy();
    return res;
}



int main(){
    
    int num_tests = 3; 
    ofstream inserts, deletes;
    inserts.open ("wynikiop/inserts.res");
    deletes.open ("wynikiop/deletes.res");

    
    for(int n = 16; n<= 2000024; n*=2){// to bedzie petla po n

            
        vector<double> total_secs(7, 0.0);
        vector<double> max_secs(7, 0.0);
        vector<double> min_secs(7, 1e9);
        for (int j = 0; j< num_reps; j++){
            vector<double> cur_time = experiment_ops(n, j); 
            for(int k = 0; k<cur_time.size(); k++){
                max_secs[k] = max(max_secs[k], cur_time[k]);
                total_secs[k]+= cur_time[k];
                min_secs[k] = min( min_secs[k], cur_time[k]);
            }
        }
        
        inserts<<n<<" ";
        for(int k = 0; k<num_tests; k++){
            total_secs[k]/= (double)num_reps;
            inserts<<min_secs[k]<<" "<<total_secs[k]<<" "<<max_secs[k]<<" ";
        }
        inserts<<"\n"; 

        deletes<<n<<" ";
        for(int k = num_tests; k<2*num_tests; k++){
            total_secs[k]/= (double)num_reps;
            deletes<<min_secs[k]<<" "<<total_secs[k]<<" "<<max_secs[k]<<" ";
        }
        deletes<<"\n"; 
        
    }
    
    inserts.close();
    deletes.close();    
}