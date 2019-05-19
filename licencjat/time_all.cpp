#include<bits/stdc++.h>
#include"tango.h"
#include"splay.h"


using namespace std;

const int qs[] = {10, 100, 1000, 10000, 100000, 1000000};
const int num_reps = 50;

vector<double> experiment(const vector<int>& queries, int n){
    splay_tree<int> d_splay;
    br_tree<int> d_br;
    set<int> d_set;
    
    vector<int> liczby; 
    for(int i = 1; i<=n; i++){
        liczby.push_back(i);       
    }
    tango_tree<int> d_tango(liczby);//konstruktor przyjmuje posortowane liczby;
    random_shuffle(liczby.begin(), liczby.end());
    for(int i = 0; i<n; i++){
        d_splay.insert(liczby[i]);
        d_br.insert(liczby[i]);
        d_set.insert(liczby[i]);
    }
    std::chrono::duration<double> ttsplay(0.0), tttango(0.0), ttbr(0.0), ttset(0.0), ttstat(0.0); 
    
    for(int i = 0; i< queries.size(); i++){
        int val = queries[i];
        
        std::chrono::duration<double> elapsed_seconds;
        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = chrono::system_clock::now();
        d_splay.find(val);
        end = chrono::system_clock::now();
        elapsed_seconds = end - start; 
        ttsplay += elapsed_seconds;
        
        start = chrono::system_clock::now();
        d_tango.find(val);
        end = chrono::system_clock::now();
        elapsed_seconds = end - start; 
        tttango += elapsed_seconds;
        
        start = chrono::system_clock::now();
        d_br.find(val);
        end = chrono::system_clock::now();
        elapsed_seconds = end - start; 
        ttbr += elapsed_seconds;
        
        start = chrono::system_clock::now();
        d_set.find(val);
        end = chrono::system_clock::now();
        elapsed_seconds = end - start; 
        ttset += elapsed_seconds;
        
    } 
    
    vector<double> res;
    res.push_back(ttsplay.count());
    res.push_back(tttango.count());
    res.push_back(ttbr.count());
    res.push_back(ttset.count());
    d_br.destroy();
    return res;
}


vector<double> experiment_gaussian(int seed, int q, int n, double e_v){
    default_random_engine generator(seed);
    srand(seed);
    normal_distribution<double> distribution(((double) n)/2, ((double) n)*e_v);
    
    vector<int> queries;
    
    for(int i = 0; i< q; i++){
        int val;
        while(val > n || val < 1) val = distribution(generator) ;
        queries.push_back(i);
        
    } 
    
    return experiment(queries, n);
}


vector<double>  experiment_uniform(int seed, int q, int n){
    default_random_engine generator(seed);
    srand(seed);
    uniform_int_distribution<int> distribution (1, n);
    
    vector<int> queries;
    
    for(int i = 0; i< q; i++){
        int val;
        while(val > n || val < 1) val = distribution(generator) ;
        queries.push_back(i);
        
    } 
    
    return experiment(queries, n);
}

int pruf[10001];
int zlicz[10001];
int ojciec[10001];
vector<int> lista[10001];

void make_graph(int seed, int n){
    srand(seed);
    
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
    int jeden = a;
    ojciec[jeden] = ojciec[1];
    for(int i  = 2; i<=n; i++){
        if(ojciec[i] == 1) ojciec[i] = jeden;
        else if(ojciec[i] == jeden) ojciec[i] = 1;
        lista[i].push_back(ojciec[i]);
        lista[ojciec[i]].push_back(i);
    }
}


vector<double> experiment_randwalk(int seed, int n, int q){
    make_graph(seed, n);
    srand(seed);
    vector<int> queries;
    int current = 1; 
    for(int i = 0; i< q; i++){
        
        current = lista[current][rand()%(lista[current].size())];
        queries.push_back(current);
    } 
    return experiment(queries, n);
}


int main(){
    
    int q = 100;
    int n = 100; 
    ofstream gaus01, gaus025, gaus05, gaus075, randw, uni;
    gaus01.open ("wyniki/gaus01.res");
    gaus025.open ("wyniki/gaus025.res");
    gaus05.open ("wyniki/gaus05.res");
    gaus075.open ("wyniki/gaus075.res");
    randw.open ("wyniki/randwalk.res");
    uni.open ("wyniki/uniform.res");

    
    for(int n = 16; n<= 1024; n*=2){// to bedzie petla po n
        for(int q = n/4; q<=n*8; q*=2){
            //gauss 0.1*n
            vector<double> total_secs(4, 0.0);
            vector<double> max_secs(4, 0.0);
            vector<double> min_secs(4, 1e9);
            for (int j = 0; j< num_reps; j++){
                vector<double> cur_time = experiment_gaussian(j, q, n, 0.1); 
                for(int k = 0; k<4; k++){
                    max_secs[k] = max(max_secs[k], cur_time[k]);
                    total_secs[k]+= cur_time[k];
                    min_secs[k] = min( min_secs[k], cur_time[k]);
                }
            }
            
            gaus01<<n<<" "<<q<<" ";
            for(int k = 0; k<4; k++){
                total_secs[k]/= (double)num_reps;
                gaus01<<min_secs[k]<<" "<<total_secs[k]<<" "<<max_secs[k]<<" ";
            }
            gaus01<<"\n";
            //gauss 0.25 * n
            fill(total_secs.begin(), total_secs.end(), 0.0);
            fill(max_secs.begin(), max_secs.end(), 0.0);
            fill(min_secs.begin(), min_secs.end(), 1e9);

            for (int j = 0; j< num_reps; j++){
                vector<double> cur_time = experiment_gaussian(j, q, n, 0.25); 
                for(int k = 0; k<4; k++){
                    max_secs[k] = max(max_secs[k], cur_time[k]);
                    total_secs[k]+= cur_time[k];
                    min_secs[k] = min( min_secs[k], cur_time[k]);
                }
            }
            
            gaus025<<n<<" "<<q<<" ";
            for(int k = 0; k<4; k++){
                total_secs[k]/= (double)num_reps;
                gaus025<<min_secs[k]<<" "<<total_secs[k]<<" "<<max_secs[k]<<" ";
            }
            gaus025<<"\n";
            //gauss 0.5*n
            fill(total_secs.begin(), total_secs.end(), 0.0);
            fill(max_secs.begin(), max_secs.end(), 0.0);
            fill(min_secs.begin(), min_secs.end(), 1e9);
            for (int j = 0; j< num_reps; j++){
                vector<double> cur_time = experiment_gaussian(j, q, n, 0.5); 
                for(int k = 0; k<4; k++){
                    max_secs[k] = max(max_secs[k], cur_time[k]);
                    total_secs[k]+= cur_time[k];
                    min_secs[k] = min( min_secs[k], cur_time[k]);
                }
            }
            gaus05<<n<<" "<<q<<" ";
            for(int k = 0; k<4; k++){
                total_secs[k]/= (double)num_reps;
                gaus05<<min_secs[k]<<" "<<total_secs[k]<<" "<<max_secs[k]<<" ";
            }
            gaus05<<"\n";
            
            //gauss 0.75n
            fill(total_secs.begin(), total_secs.end(), 0.0);
            fill(max_secs.begin(), max_secs.end(), 0.0);
            fill(min_secs.begin(), min_secs.end(), 1e9);
            for (int j = 0; j< num_reps; j++){
                vector<double> cur_time = experiment_gaussian(j, q, n, 0.75); 
                for(int k = 0; k<4; k++){
                    max_secs[k] = max(max_secs[k], cur_time[k]);
                    total_secs[k]+= cur_time[k];
                    min_secs[k] = min( min_secs[k], cur_time[k]);
                }
            }
            
            gaus075<<n<<" "<<q<<" ";
            for(int k = 0; k<4; k++){
                total_secs[k]/= (double)num_reps;
                gaus075<<min_secs[k]<<" "<<total_secs[k]<<" "<<max_secs[k]<<" ";
            }
            gaus075<<"\n";
            
            //uniform
            
            fill(total_secs.begin(), total_secs.end(), 0.0);
            fill(max_secs.begin(), max_secs.end(), 0.0);
            fill(min_secs.begin(), min_secs.end(), 1e9);
            for (int j = 0; j< num_reps; j++){
                vector<double> cur_time = experiment_uniform(j, q, n); 
                for(int k = 0; k<4; k++){
                    max_secs[k] = max(max_secs[k], cur_time[k]);
                    total_secs[k]+= cur_time[k];
                    min_secs[k] = min( min_secs[k], cur_time[k]);
                }
            }
            uni<<n<<" "<<q<<" ";
            for(int k = 0; k<4; k++){
                total_secs[k]/= (double)num_reps;
                uni<<min_secs[k]<<" "<<total_secs[k]<<" "<<max_secs[k]<<" ";
            }
            uni<<"\n";
            
            //randwalk
            
            fill(total_secs.begin(), total_secs.end(), 0.0);
            fill(max_secs.begin(), max_secs.end(), 0.0);
            fill(min_secs.begin(), min_secs.end(), 1e9);
            for (int j = 0; j< num_reps; j++){
                vector<double> cur_time = experiment_randwalk(j, q, n); 
                for(int k = 0; k<4; k++){
                    max_secs[k] = max(max_secs[k], cur_time[k]);
                    total_secs[k]+= cur_time[k];
                    min_secs[k] = min( min_secs[k], cur_time[k]);
                }
            }
            randw<<n<<" "<<q<<" ";
            for(int k = 0; k<4; k++){
                total_secs[k]/= (double)num_reps;
                randw<<min_secs[k]<<" "<<total_secs[k]<<" "<<max_secs[k]<<" ";
            }
            randw<<"\n";
        
        }
        
    }
    
    gaus01.close();
    gaus025.close();
    gaus05.close();
    gaus075.close();
    randw.close();
    uni.close();
    
}