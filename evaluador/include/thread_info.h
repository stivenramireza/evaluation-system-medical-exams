#pragma once

struct Input_info
{
    int input;
    void* init_dir;
    sem_t *mutex;
    sem_t *full;
    sem_t *empty;
    sem_t **b;
    sem_t **d;
    sem_t **s;     
    Input_info(int input,void* init_dir,sem_t *mutex,sem_t *full, sem_t *empty, sem_t **b, sem_t **d, sem_t **s)
    :input(input),init_dir(init_dir),mutex(mutex),full(full),empty(empty),b(b),d(d),s(s){    }
};

struct Input_info_inter
{
    sem_t **sem;
    int* reactiv;
    char type;
    head *header;
    int min_ran,max_ran;
    char* current_dir;
    Input_info_inter(sem_t **sem, int*reactiv, char type, head *header, char *current_dir, int min_ran, int max_ran )
    :sem(sem),reactiv(reactiv),type(type),header(header),current_dir(current_dir) ,min_ran(min_ran),max_ran(max_ran)
    {}
};

