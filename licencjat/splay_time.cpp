#include<bits/stdc++.h>
#include"tree_vert.h"
#include"splay.h"


using namespace std;

const int qs[] = {10, 100, 1000, 10000, 100000, 1000000};
const int num_reps = 100;



double experiment_gaussian(int seed, int q){
    char syms[] = { 'I', 'D','L', 'U'};
    default_random_engine generator(seed);
    srand(seed);
    normal_distribution<double> distribution (0.0, 1e9);
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
            tree_vert<double>* k = drzewo.lower_bound(val);
            end = chrono::system_clock::now();
            //if(k == NULL ) printf("BRAK\n");
            //else printf("%d\n",k -> value);

        }
        if(op == 'U'){
            start = chrono::system_clock::now();
            tree_vert<double>* k = drzewo.upper_bound(val);
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
            tree_vert<double>* k = drzewo.lower_bound(val);
            end = chrono::system_clock::now();
            //if(k == NULL ) printf("BRAK\n");
            //else printf("%d\n",k -> value);

        }
        if(op == 'U'){
            start = chrono::system_clock::now();
            tree_vert<double>* k = drzewo.upper_bound(val);
            end = chrono::system_clock::now();
            //if(k == NULL ) printf("BRAK\n"); 
            //else printf("%d\n", k-> value);
        }
        
        elapsed_seconds = end - start; 
        total_time += elapsed_seconds;
        
    } 
    return total_time.count();
}
using namespace std;
int pruf[1000001];
int zlicz[1000001];
int ojciec[1000001];
vector<int> lista[1000001];

void make_graph(seed, n){
    srand(seed);
    int zap =1 +  rand()%1000001;
    int n =3 +  rand()%101;
    
    for(int i = 1; i<= n-2; i++){
        
        pruf[i] = 1 + rand()%n;
        zlicz[pruf[i]] ++;
    }
    priority_queue<int> q;
    for(int i = 1; i<=n; i++) 
        if (zlicz[i] == 0) q.push(i);
        
    
    for(int i = 1; i<=n-2; i++){
        int a = q.top();
        q.pop();
        ojciec[a] = pruf[i];
        zlicz[pruf[i]]--;
        if(zlicz[pruf[i]]==0) 
            q.push(pruf[i]);
    }
    int a = q.top();
    q.pop();
    int b = q.top();
    ojciec[b] = a;  
    //printf("ojciec wszystkich %d", a);
    int jeden = a;
    ojciec[jeden] = ojciec[1];
    printf("%d %d\n",n, zap);
    for(int i  = 2; i<=n; i++){
        //printf("%d\n", ojciec[i]);
        if(ojciec[i] == 1) ojciec[i] = jeden;
        else if(ojciec[i] == jeden) ojciec[i] = 1;
        //printf("%d\n", ojciec[i]);
        lista[i].push_back(ojciec[i]);
        lista[ojciec[i]].push_back(i);
    }
}

void randwalk(int steps){
    int curreuniformnt = 1; 
    for(int i = 0; i< steps; i++){
        
        current = lista[current][rand()%(lista[current].size*())];
    }
    
}

double experiment_randwalk(int seed, int q){
    
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
            tree_vert<double>* k = drzewo.lower_bound(val);
            end = chrono::system_clock::now();
            //if(k == NULL ) printf("BRAK\n");
            //else printf("%d\n",k -> value);

        }
        if(op == 'U'){
            start = chrono::system_clock::now();
            tree_vert<double>* k = drzewo.upper_bound(val);
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