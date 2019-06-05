#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include "share_memory.h"
#include "init_command.h"

using namespace std;

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
