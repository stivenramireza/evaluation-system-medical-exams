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
    int fd = shm_open(name_memory, O_RDWR, 0660);
    void *dir = mmap(NULL, sizeof(struct head), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    head *phead = (head *) dir;
    int cantidad = 0;
    string sem_name_mutex = "_output_mutex";
    string sem_name_empty = "_output_empty";
    string sem_name_full  = "_output_fulls"; 
    sem_name_mutex = name_memory + sem_name_mutex;
    sem_name_empty = name_memory + sem_name_empty;
    sem_name_full = name_memory + sem_name_full;
    mutex = sem_open(sem_name_mutex.c_str(), 0);
    empty = sem_open(sem_name_empty.c_str(), 0);
    full = sem_open(sem_name_full.c_str(), 0);
    while(cantidad < n_examenes){
        sem_wait(full);
        sem_wait(mutex);

        sem_post(mutex);
        sem_post(empty);
    }
}