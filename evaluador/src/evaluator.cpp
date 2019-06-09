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
#include "reg_command.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

using namespace std;

void eval_command(char* commands[], int* length){
    char* current_command = commands[1];
    if (strcmp(current_command,"init") == 0){
        command_init(commands,length);
    }
    else if (strcmp(current_command,"reg") == 0){
        for(int i = 0; i < 5; ++i){
            string _mem_name = "evaluator";
            string mutex_name = _mem_name + "_input_" + to_string(i).c_str() + "_mutex";
            string fulls_name = _mem_name + "_input_" + to_string(i).c_str() + "_fulls";
            string empty_name = _mem_name + "_input_" + to_string(i).c_str() + "_empty";
            sem_t * new_sem_mutex = sem_open(mutex_name.c_str(), O_CREAT | O_EXCL, 0660, 1);
            sem_t * new_sem_fulls = sem_open(fulls_name.c_str(), O_CREAT | O_EXCL, 0660, 0);
            sem_t * new_sem_empty = sem_open(empty_name.c_str(), O_CREAT | O_EXCL, 0660, 6);
        }
        RegistratorCommand *command = new RegistratorCommand(commands, *length);
        command->start();
        //command->put_sample(0, 0, 0);
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

void usage();

int
main(int argc, char* argv[]){
    if(argc < 2){
        usage();
        printf("Error\n");
        exit(EXIT_FAILURE);
    }
    eval_command(argv,&argc);
    exit(EXIT_SUCCESS);
}

void usage(){
    // .... Como usar el programa .......
}