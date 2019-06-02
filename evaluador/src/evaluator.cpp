#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "share_memory.h"
using namespace std;

void command_init(char* commands[], int* length){
    int i=5, ie=6, oe=10, b=100, d=100, s=100, q=6;
    char *n = (char*)"evaluator";
    if (*length == 2){
    }
    else if(*length%2 != 0){
        cerr<<"command invalid\n";
        exit(EXIT_FAILURE);
    }
    else{
        for(int it=2; it<*length; it+=2){
            if(strcmp(commands[it],"-i") == 0){
                i = atoi(commands[it+1]);
                if(i <= 0){
                    cerr<<"-i <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(strcmp(commands[it],"-ie")==0){
                ie = atoi(commands[it+1]);
                if(ie <= 0){
                    cerr<<"-ie <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(strcmp(commands[it],"-oe")==0){
                oe = atoi(commands[it+1]);
                if(oe <= 0){
                    cerr<<"-oe <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(strcmp(commands[it],"-n")==0){
                n = commands[it+1];
            }
            else if(strcmp(commands[it],"-b")==0){
                b = atoi(commands[it+1]);
                if(b <= 0){
                    cerr<<"-b <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(strcmp(commands[it],"-d")==0){
                d = atoi(commands[it+1]);
                if(d <= 0){
                    cerr<<"-d <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(strcmp(commands[it],"-s")==0){
                s = atoi(commands[it+1]);
                if(s <= 0){
                    cerr<<"-s <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(strcmp(commands[it],"-q")==0){
                q = atoi(commands[it+1]);
                if(q <= 0){
                    cerr<<"-q <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    cout<<i<<endl<<ie<<endl<<oe<<endl<<n<<endl<<b<<endl<<d<<endl<<s<<endl<<q<<endl;
}

void eval_command(char* commands[], int* length){
    char* current_command = commands[1];
    if (strcmp(current_command,"init") == 0){
        command_init(commands,length);
    }
    else if (strcmp(current_command,"reg") == 0){
        cout<<"ok2\n";
    }
    else if (strcmp(current_command,"ctrl") == 0){
        cout<<"ok3\n";
    }
    else if (strcmp(current_command,"rep") == 0){
        cout<<"ok4\n";
    }
    else{
        cerr<<"Command" << current_command << " not found\n";
        exit(EXIT_FAILURE);
    }
}
int
main(int argc, char* argv[]){
    eval_command(argv,&argc);
    exit(EXIT_SUCCESS);
}