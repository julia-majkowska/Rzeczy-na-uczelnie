#include<bits/stdc++.h>
#include"tango.h"
#include"splay.h"
#include"static_tree.h"


using namespace std;
const int num_reps = 50;
const int max_query = 10000;
const int num_tests = 5; 
const int num_gauses = 4; 
const int num_randws = 5; 
const int num_unis = 5; 

vector<double> experiment(const vector<int>& queries, int n, int seed){
    splay_tree<int> d_splay;
    br_tree<int> d_br;
    set<int> d_set;
    
    vector<int> liczby; 
    for(int i = 1; i<=n; i++){
        liczby.push_back(i);       
    }
    tango_tree<int> d_tango(liczby);//konstruktor przyjmuje posortowane liczby;
    static_tree<int> d_static(queries);
    srand(seed);
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
        
        start = chrono::system_clock::now();
        d_static.find(val);
        end = chrono::system_clock::now();
        elapsed_seconds = end - start; 
        ttstat += elapsed_seconds;
        
    } 
    
    vector<double> res;
    res.push_back(ttsplay.count());
    res.push_back(tttango.count());
    res.push_back(ttbr.count());
    res.push_back(ttset.count());
    res.push_back(ttstat.count());
    d_br.destroy();
    return res;
}


vector<double> experiment_gaussian(int seed, int q, int n, double e_v){
    default_random_engine generator(seed);
    srand(seed);
    normal_distribution<double> distribution(((double) n)/2, ((double) n)*e_v);
    
    vector<int> queries;
   // if(q == 16) cout<<"Gaussian "<<e_v<<"\n";
    for(int i = 0; i< q; i++){
        int val = distribution(generator);
        
        while(val > n || val < 1) val = distribution(generator) ;
       // if(q == 16) cout<<val<<" ";
        queries.push_back(val);
        
    } 
    //if(q == 16) cout<<"\n";
    return experiment(queries, n, seed);
}


vector<double> experiment_uniform(int seed, int q, int n, int of_mil){
    default_random_engine generator(seed);
    srand(seed);
    uniform_int_distribution<int> distribution (1, n);
    
    vector<int> queries;
    int val = 1;
    //if(q == 16) cout<<"Uniform "<<precent<<"\n";
    for(int i = 0; i< q; i++){
        
        int go_stop = rand()%1000000 + 1; 
        if(go_stop <= of_mil)
            val = distribution(generator);
            while(val > n || val < 1) val = distribution(generator) ;
        //if(q == 16) cout<<val<<" ";
        queries.push_back(val);
        
    } 
    //if(q == 16) cout<<"\n";
    return experiment(queries, n, seed);
}

int pruf[max_query+1];
int zlicz[max_query+1];
int ojciec[max_query+1];
vector<int> lista[max_query + 1];

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


vector<double> experiment_randwalk(int seed, int q, int n, int of_mil){
    make_graph(seed, n);
    srand(seed);
    vector<int> queries;
    int current = 1; 
    for(int i = 0; i< q; i++){
        int go_stop = rand()%1000000+1;
        if(go_stop < of_mil) current = lista[current][rand()%(lista[current].size())];
        queries.push_back(current);
    } 
    return experiment(queries, n, seed);
}

void all_exp_randwalk(ofstream files[num_randws], vector<int> stop){
//gauss 0.1*n
    vector<double> total_secs(7, 0.0);
    vector<double> max_secs(7, 0.0);
    vector<double> min_secs(7, 1e9);
    
    for(int n = 16; n<= max_query; n*=2){// to bedzie petla po n
        for(int q = n/4; q<=n*8; q*=2){
            
            for(int ii = 0; ii < num_randws; ii++){
                fill(total_secs.begin(), total_secs.end(), 0.0);
                fill(max_secs.begin(), max_secs.end(), 0.0);
                fill(min_secs.begin(), min_secs.end(), 1e9);
                for (int j = 0; j< num_reps; j++){
                    vector<double> cur_time = experiment_randwalk(j, q, n, stop[ii]); 
                    for(int k = 0; k<num_tests; k++){
                        max_secs[k] = max(max_secs[k], cur_time[k]);
                        total_secs[k]+= cur_time[k];
                        min_secs[k] = min( min_secs[k], cur_time[k]);
                    }
                }
                files[ii]<<n<<" "<<q<<" ";
                for(int k = 0; k<num_tests; k++){
                    total_secs[k]/= (double)num_reps;
                    files[ii]<<min_secs[k]<<" "<<total_secs[k]<<" "<<max_secs[k]<<" ";
                }
                files[ii]<<"\n";
            }

        }
    }
}

void all_exp_uniform(ofstream files[num_unis], vector<int> stop){
//gauss 0.1*n
    vector<double> total_secs(7, 0.0);
    vector<double> max_secs(7, 0.0);
    vector<double> min_secs(7, 1e9);
    
    for(int n = 16; n<= max_query; n*=2){// to bedzie petla po n
        for(int q = n/4; q<=n*8; q*=2){
            
            for(int ii = 0; ii < num_unis; ii++){
                fill(total_secs.begin(), total_secs.end(), 0.0);
                fill(max_secs.begin(), max_secs.end(), 0.0);
                fill(min_secs.begin(), min_secs.end(), 1e9);
                for (int j = 0; j< num_reps; j++){
                    vector<double> cur_time = experiment_uniform(j, q, n, stop[ii]); 
                    for(int k = 0; k<num_tests; k++){
                        max_secs[k] = max(max_secs[k], cur_time[k]);
                        total_secs[k]+= cur_time[k];
                        min_secs[k] = min( min_secs[k], cur_time[k]);
                    }
                }
                files[ii]<<n<<" "<<q<<" ";
                for(int k = 0; k<num_tests; k++){
                    total_secs[k]/= (double)num_reps;
                    files[ii]<<min_secs[k]<<" "<<total_secs[k]<<" "<<max_secs[k]<<" ";
                }
                files[ii]<<"\n";
            }

        }
    }
}

void all_exp_gaussian(ofstream files[num_gauses], vector<double> e){
//gauss 0.1*n
    vector<double> total_secs(7, 0.0);
    vector<double> max_secs(7, 0.0);
    vector<double> min_secs(7, 1e9);
    
    for(int n = 16; n<= max_query; n*=2){// to bedzie petla po n
        for(int q = n/4; q<=n*8; q*=2){
            
            for(int ii = 0; ii < num_gauses; ii++){
                fill(total_secs.begin(), total_secs.end(), 0.0);
                fill(max_secs.begin(), max_secs.end(), 0.0);
                fill(min_secs.begin(), min_secs.end(), 1e9);
                for (int j = 0; j< num_reps; j++){
                    vector<double> cur_time = experiment_gaussian(j, q, n, e[ii]);  
                    for(int k = 0; k<num_tests; k++){
                        max_secs[k] = max(max_secs[k], cur_time[k]);
                        total_secs[k]+= cur_time[k];
                        min_secs[k] = min( min_secs[k], cur_time[k]);
                    }
                }
                files[ii]<<n<<" "<<q<<" ";
                for(int k = 0; k<num_tests; k++){
                    total_secs[k]/= (double)num_reps;
                    files[ii]<<min_secs[k]<<" "<<total_secs[k]<<" "<<max_secs[k]<<" ";
                }
                files[ii]<<"\n";
            }

        }
    }
}




int main(){
    

    ofstream gauses[num_gauses], randws[num_randws], unis[num_unis]; 
    
    string gausnames[] = {"wyniki/gaus50.res", "wyniki/gaus10.res", "wyniki/gaus1.res", "wyniki/gaus001.res"};
    double my_es[] = {0.5, 0.1, 0.01, 0.0001};
    std::vector<double> es (my_es, my_es + sizeof(my_es) / sizeof(double) );
    for(int i = 0; i<num_gauses; i++){
        gauses[i].open( gausnames[i]);
    }
    all_exp_gaussian(gauses, es);
    
    for(int i = 0; i<4; i++){
        gauses[i].close();
    }
    
    int my_likes[] = {1000000, 500000, 100000, 10000, 100}; //100%, 50%, 10%, 1%, 0,01%
    std::vector<int> likes (my_likes, my_likes + sizeof(my_likes) / sizeof(int) );
    
    string randwnames[] = {"wyniki/randwalk100.res", "wyniki/randwalk50.res", "wyniki/randwalk10.res", "wyniki/randwalk1.res", "wyniki/randwalk001.res"};
    for(int i = 0; i<num_randws; i++){
        randws[i].open( randwnames[i]);
    }
    all_exp_randwalk(randws, likes);
    for(int i = 0; i<5; i++){
        randws[i].close();
    }
    
    string uninames[] = {"wyniki/uniform100.res", "wyniki/uniform50.res", "wyniki/uniform10.res", "wyniki/uniform1.res", "wyniki/uniform001.res"};
    for(int i = 0; i<num_unis; i++){
        unis[i].open( uninames[i]);
    }
    all_exp_uniform(unis, likes);
    for(int i = 0; i<5; i++){
        unis[i].close();
    }
}