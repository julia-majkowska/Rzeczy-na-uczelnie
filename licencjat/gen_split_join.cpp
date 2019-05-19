#include<bits/stdc++.h>

using namespace std;
 

int main(int argc, char* argv[]){//operacje s
    char syms[] = {'M', 'S', 'D', 'I'};
    srand(atoi(argv[1]));
    
    int sets =30; 
    int set_size[sets+10];
    int q=50;
    int sum = q;
    for(int i = 0; i< sets; i++){
        set_size[i] = rand()%50 + 1;
        sum += set_size[i];
    }
    vector<int> elems;
    for(int i = 0; i< sum; i++){
        elems.push_back(i);
    }
    random_shuffle(elems.begin(), elems.end());
    int elem_pointer = 0;
    printf("%d\n", sets);
    for(int i = 0; i< sets; i++){
        printf("%d ", set_size[i]);
        vector<int> x;
        for(int j =0; j< set_size[i]; j++){
            int a = elems[elem_pointer++];
            printf("%d ", a);
        }
        printf("\n");
    }
    
    printf("%d\n", q);
    while(q--){
        char op = syms[rand()%4];
        int set = rand()%sets;
        while(sets == 1 && op == 'M') op = syms[rand()%4];
        int elem = elems[elem_pointer++];
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
