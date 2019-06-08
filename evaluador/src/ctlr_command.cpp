#include "ctlr_command.h"

void command_ctlr(char* commands[], int* length){
    char* type;
    string i;
    int d = 100;
    char *n = (char*)"evaluator";
    if (*length == 2){
        cerr<<"missing -n command\n";
        exit(EXIT_FAILURE);
    }else{
        for(int it=2; it<*length; it+=2){
            if(strcmp(commands[it],"-n")==0){
                    n = commands[it+1];
                    if(strcmp(commands[it+2], "list")==0){
                        if(strcmp(commands[it+3], "processing")==0){
                            cout << "Processing:\n";
                        }else if(strcmp(commands[it+3], "waiting")==0){
                            cout << "Waiting:\n";
                        }else if(strcmp(commands[it+3], "reported")==0){
                            cout << "Reported:\n";
                        }else if(strcmp(commands[it+3], "reactive")==0){
                            cout << d << endl;
                        }else if(strcmp(commands[it+3], "all")==0){
                            cout << "Processing:\n";
                            cout << "Waiting:\n";
                            cout << "Reported:\n";
                            cout << d << endl;
                        }else{
                            cerr<<"invalid subcommand";
                            exit(EXIT_FAILURE);
                        }
                    }else if(strcmp(commands[it+2], "update")==0){
                        if(strcmp(commands[it+3], "B") || strcmp(commands[it+3], "S") || strcmp(commands[it+3], "B")==0){
                            type = commands[it+4];
                        }else{
                            cerr<<"expected B|D|S";
                            exit(EXIT_FAILURE);
                        }
                    }else{
                        cout << "invalid subcommand" << endl;
                    }
            }
        }
    }
}