#include "stop_command.h"
#include "share_memory.h"
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <vector>
#include "thread_info.h"

void command_stop(char* commands[], int length){
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
        }
    }
    shm_unlink(n); 
    for(int i = 0; i < 5; ++i){
        string _mem_name = n;
        string mutex_name = _mem_name + "_input_" + to_string(i).c_str() + "_mutex";
        string fulls_name = _mem_name + "_input_" + to_string(i).c_str() + "_fulls";
        string empty_name = _mem_name + "_input_" + to_string(i).c_str() + "_empty";
        sem_unlink(mutex_name.c_str());
        sem_unlink(fulls_name.c_str());
        sem_unlink(empty_name.c_str());
    }
    sem_unlink(("evaluator_inter_b_mutex"));
    sem_unlink(("evaluator_inter_b_empty"));
    sem_unlink(("evaluator_inter_b_full" ));
    sem_unlink(("evaluator_inter_d_mutex"));
    sem_unlink(("evaluator_inter_d_empty"));
    sem_unlink(("evaluator_inter_d_full"));
    sem_unlink(("evaluator_inter_s_mutex"));
    sem_unlink(("evaluator_inter_s_empty"));
    sem_unlink(("evaluator_inter_s_full"));
    string _mem_name = n;
    string sem_name_mutex = "_output_mutex";
    string sem_name_empty = "_output_empty";
    string sem_name_full  = "_output_fulls"; 
    sem_name_mutex = _mem_name + sem_name_mutex;
    sem_name_empty = _mem_name + sem_name_empty;
    sem_name_full = _mem_name + sem_name_full;
    sem_unlink(sem_name_mutex.c_str());
    sem_unlink(sem_name_empty.c_str());
    sem_unlink(sem_name_full.c_str());
}