#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void command_init(char* commands[], int* length){
    int i=5, ie=6, oe=10, b=100, d=100, s=100, q=6;
    char n[] = "evaluator";
    if (*length == 2){
        cout<<"ok\n";
    }
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