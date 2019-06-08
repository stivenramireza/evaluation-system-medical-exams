#include "ctlr_command.h"

void command_ctlr(char* commands[], int* length){
    char *n = (char*)"evaluator";
    if (*length == 2){
    }
    else if(*length%2 != 0){
        cerr<<"command invalid\n";
        exit(EXIT_FAILURE);
    }
    else{
        
    }
}