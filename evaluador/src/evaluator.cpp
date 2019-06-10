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
#include "ctlr_command.h"
#include "rep_command.h"
#include "stop_command.h"

using namespace std;

void eval_command(char* commands[], int length){
    char* current_command = commands[1];
    if (strcmp(current_command,"init") == 0){
        command_init(commands,length);
    }else if (strcmp(current_command,"reg") == 0){
        cout<<"reg command in progress\n";
    }else if (strcmp(current_command,"ctlr") == 0){
        command_ctlr(commands,length);
    }else if (strcmp(current_command,"rep") == 0){
        command_rep(commands, length);
    }else if(strcmp(current_command, "stop") == 0){
        cout<<"stop command in progress\n";
    }else{
        cerr<<"Command " << current_command << " not found\n";
        exit(EXIT_FAILURE);
    }
}

int
main(int argc, char* argv[]){
    eval_command(argv,argc);
    exit(EXIT_SUCCESS);
}
