#include "ctlr_command.h"

void command_ctlr(char* commands[], int* length){
    bool isN = false;
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
                isN = true;
            }
        }
    }
    if(isN){
       // Do subcommands
    }
}