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

