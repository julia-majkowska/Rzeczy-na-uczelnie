#include<bits/stdc++.h>



using namespace std;

const int qs[] = {10, 100, 1000, 10000, 100000, 1000000};
const int num_reps = 100;



double experiment_gaussian(int seed, int q){
    char syms[] = { 'I', 'D','L', 'U'};
    default_random_engine generator(seed);
    srand(seed);
    normal_distribution<double> distribution (0.0, 1e9);
    std::chrono::duration<double> total_time(0.0);
    set<double> drzewo;
    for(int i = 0; i< q; i++){
        int ind = rand()%4, val = distribution(generator) ;
        char op = syms[ind];
        std::chrono::duration<double> elapsed_seconds;
        std::chrono::time_point<std::chrono::system_clock> start, end;
        if(op == 'I'){
            start = chrono::system_clock::now();
            drzewo.insert(val);
            end = chrono::system_clock::now();
        }
        if(op == 'D'){
            start = chrono::system_clock::now();
            bool cz = drzewo.erase(val);
            end = chrono::system_clock::now();
            //if(cz) printf("OK\n");
            //else printf("BRAK\n");
        }
        if(op == 'L'){
            start = chrono::system_clock::now();
            auto k = drzewo.lower_bound(val);
            end = chrono::system_clock::now();
            //if(k == NULL ) printf("BRAK\n");
            //else printf("%d\n",k -> value);

        }
        if(op == 'U'){
            start = chrono::system_clock::now();
            auto k = drzewo.upper_bound(val);
            end = chrono::system_clock::now();
            //if(k == NULL ) printf("BRAK\n"); 
            //else printf("%d\n", k-> value);
        }
        
        elapsed_seconds = end - start; 
        total_time += elapsed_seconds;
        
    } 
    return total_time.count();
}


double experiment_uniform(int seed, int q){
    
    char syms[] = { 'I', 'D','L', 'U'};
    default_random_engine generator(seed);
    srand(seed);
    uniform_real_distribution<double> distribution (-(1e9), 1e9);
    std::chrono::duration<double> total_time(0.0);
    splay_tree<double> drzewo;
    for(int i = 0; i< q; i++){
        int ind = rand()%4, val = distribution(generator) ;
        char op = syms[ind];
        std::chrono::duration<double> elapsed_seconds;
        std::chrono::time_point<std::chrono::system_clock> start, end;
        if(op == 'I'){
            start = chrono::system_clock::now();
            drzewo.insert(val);
            end = chrono::system_clock::now();
        }
        if(op == 'D'){
            start = chrono::system_clock::now();
            bool cz = drzewo.erase(val);
            end = chrono::system_clock::now();
            //if(cz) printf("OK\n");
            //else printf("BRAK\n");
        }
        if(op == 'L'){
            start = chrono::system_clock::now();
            auto k = drzewo.lower_bound(val);
            end = chrono::system_clock::now();
            //if(k == NULL ) printf("BRAK\n");
            //else printf("%d\n",k -> value);

        }
        if(op == 'U'){
            start = chrono::system_clock::now();
            auto k = drzewo.upper_bound(val);
            end = chrono::system_clock::now();
            //if(k == NULL ) printf("BRAK\n"); 
            //else printf("%d\n", k-> value);
        }
        
        elapsed_seconds = end - start; 
        total_time += elapsed_seconds;
        
    } 
    return total_time.count();
}


int main(){
    
    q = 16;
    for(int i = 0; i< 15; i++){
        double total_secs = 0.0, max_secs = 0, min_secs = 1e9;
        for (int j = 0; j< num_reps; j++){
            double cur_time = experiment_gaussian(j, q); 
            max_secs = max(max_secs, cur_time);
            total_secs+= cur_time;
            min_secs = min( min_secs, cur_time);
        }
        total_secs/= (double)num_reps;
        
        cout<<q<" "<<min_secs<<" "<<total_secs<<" "<<max_secs<<"\n";
        q*=2;
        
    }
    
}