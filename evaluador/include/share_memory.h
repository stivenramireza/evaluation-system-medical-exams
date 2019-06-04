#pragma once

#include <semaphore.h>
#include <iostream>

using namespace std;

struct shared_memory{
    int i,ie,oe,q,b,d,s;
    int** input,types;
    int* output,pts_first;
    sem_t** semaphores;

    shared_memory(int i, int ie, int oe,int q,int b,int d,int s):i(i),ie(ie),oe(oe),q(q),b(b),d(d),s(s){        
    }
};
