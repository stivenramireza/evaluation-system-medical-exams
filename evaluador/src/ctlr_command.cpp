#include "ctlr_command.h"

void command_ctlr(char* commands[], int* length){
    char *n = (char*)"evaluator";
    bool isN = false;
    char* interactive_command[2][0];
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
       // Interactive command prompt
    }
}