#include<bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]){//operacje s
    char syms[] = {'M', 'I', 'D', 'S'};
    srand(atoi(argv[1]));
    
    int sets =10; 
    printf("%d\n", sets);
    for(int i = 0; i< sets; i++){
        int set_size = rand()%10+1;
        printf("%d ", set_size);
        vector<int> x;
        for(int j =0; j< set_size; j++){
            int a = rand()%40 - 20;
            printf("%d ", a);
        }
        printf("\n");
    }
    int q=10;
    printf("%d\n", q);
    while(q--){
        char op = syms[rand()%4];
        int set = rand()%sets;
        int elem = rand()%40 -20;
        printf("%c %d", op, set);
        
        
        if(op == 'I' || op == 'D'||op == 'S'){
            printf(" %d\n",elem);
        }
        if(op == 'S'){
            sets++;
            
        }
        if(op =='M'){
            printf("\n");
            sets--;
            
        }
    }
    
}
