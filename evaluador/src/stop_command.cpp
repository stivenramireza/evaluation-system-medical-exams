#include "stop_command.h"

void command_stop(char* commands[], int* length){
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
            }
        }
    }
    cout << "name_memory: " << n << endl;
}