#include "rep_command.h"

void command_rep(char* commands[], int length){
    int i, m;
    char *n = (char*)"evaluator";
    if (length == 2){
    }
    else if(length%2 != 0){
        cerr<<"command invalid\n";
        exit(EXIT_FAILURE);
    }else{
        for(int it=2; it<length; it+=2){
            if(strcmp(commands[it],"-n")==0){
                n = commands[it+1];
            }
            if(strcmp(commands[it],"-i")==0){
                i = stoi(commands[it+1]);
                if(i <= 0){
                    cerr<<"-i <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }else{
                    interactive_mode(n, i);
                } 
            }else if(strcmp(commands[it],"-m")==0){
                m = stoi(commands[it+1]);
                if(m <= 0){
                    cerr<<"-m <integer>"<<endl;
                    exit(EXIT_FAILURE);
                }else{
                    obtener_examenes(n, m);
                } 
            }
        }
    }
}

void interactive_mode(char* name_memory, int seconds){
    sleep(seconds);
    cout << "Interactive mode reporting for " << name_memory << " shared memory" << endl;
}

void obtener_examenes(char* name_memory, int n_examenes){
    // Consumidor de exámenes
    cout << "Consume " << n_examenes << " from "  << name_memory << " shared memory"<< endl;
}