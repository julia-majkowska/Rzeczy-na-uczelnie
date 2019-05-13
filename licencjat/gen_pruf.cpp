#include<bits/stdc++.h>

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

int main(int argc, char* argv[]){
    int seed = atoi(argv[1]);
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
