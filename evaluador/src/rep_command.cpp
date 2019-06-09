#include "rep_command.h"

void command_rep(char* commands[], int* length){
    int i, m;
    char *n = (char*)"evaluator";
    if (*length == 2){
    }
    else if(*length%2 != 0){
        cerr<<"command invalid\n";
        exit(EXIT_FAILURE);
    }else{
        for(int it=2; it<*length; it+=2){
            if(strcmp(commands[it],"-n")==0){
                n = commands[it+1];
                cout << "n: " << n << endl;
            }
            if(strcmp(commands[it],"-i")==0){
                i = stoi(commands[it+1]);
                if(i <= 0){
                    cerr<<"-i <integer>"<<endl;
                    exit(EXIT_FAILURE);
                } 
            }
            if(strcmp(commands[it],"-m")==0){
                m = stoi(commands[it+1]);
                if(m <= 0){
                    cerr<<"-m <integer>"<<endl;
                    exit(EXIT_FAILURE);
                } 
            }
        }
    }
}