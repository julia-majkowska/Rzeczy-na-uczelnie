#include<bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]){ 
    int n = 10000;//atoi(argv[2]);
    int q =n;//200; 
    srand(atoi(argv[1]));
    vector<int> v; 
    printf("%d\n", n);
    for(int i = 1; i<= n; i++){
        printf("%d ", i);
        v.push_back(i);
    }   
    random_shuffle(v.begin(), v.end());
    printf("\n%d\n", q);
    for(int i = 0; i< q; i++){
        int v = rand()%(n)+1 ;
        printf("%d ", v);
        
    }
    
}