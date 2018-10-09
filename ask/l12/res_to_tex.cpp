#include<bits/stdc++.h>


using namespace std;

string IntToString (int a)
{
    ostringstream temp;
    temp<<a;
    return temp.str();
}

int main(int argc, char*argv[]){
    
    ofstream out; 
    out.open (argv[argc-1]);
    out << "\\begin{center}\n\\begin{tabular}{|";
    //int tab[] = {4, 8, 12, 16, 20, 24, 28, 32, 36, 64, 128, 256, 512, 1024};
    int a = argc-1;
    double srednie[a];
    double maks[a];
    double mini[a];
    ifstream in[a];
    for(int j = 1; j< a; j++){
        //printf("%s", argv[j]);
        out << "c|";
        mini[j] = 100000000.0;
        maks[j] = 0.0;
        srednie[j] = 0.0;
        //string nazwa = "cache" + IntToString (j) + ".21_16";
        //string nazwa = "cache_16_16_" + IntToString(tab[j]);
        in[j].open (argv[j]);
        
    }
    out<<"}\n\\hline\n";
    
    for(int i = 0; i<10; i++){
        out<<i;
        for(int j = 1; j<a; j++){
           
            double d; 
            in[j]>>d;
            //in.close();
            out<<" & "<<d;
            srednie[j] +=d/10;
            maks[j] = max(maks[j], d);
            mini[j] = min(mini[j], d);
            
        }
        out<<"\\\\\n\\hline\n";
        
    }
    
    out<<"SREDNIE";
    for(int j = 1; j<a; j++){
        out<<" & "<<srednie[j];
        cout<<srednie[j]<<" ";
    }
    out<<"\\\\\n\\hline\n";
    
    out<<"MIN";
    for(int j = 1; j<a; j++)  out<<" & "<<mini[j];
    out<<"\\\\\n\\hline\n";
    
    out<<"MAKS";
    for(int j = 1; j<a; j++)  out<<" & "<<maks[j];
    out<<"\\\\\n\\hline\n";

    //out<<"\\\\\n\\hline\n";
    
    out << "\\end{tabular}\n\\end{center}\n";
    
    out.close();
}