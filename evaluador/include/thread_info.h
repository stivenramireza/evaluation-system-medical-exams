#pragma once

struct Input_info
{
    int input;
    void* init_dir;
    sem_t *semaforo;    
    Input_info(int input,void* init_dir,sem_t *semaforo):input(input),init_dir(init_dir),semaforo(semaforo){   }
};

