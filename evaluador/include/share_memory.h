#pragma once

#include <semaphore.h>

struct shared_memory{
    int i,ie,oe,q,b,d,s;
    int** input,types;
    int* output,pts_first;
    sem_t** semaphores;
};
