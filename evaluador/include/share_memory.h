#pragma once

#include <semaphore.h>
#include <iostream>

using namespace std;

struct exam{
    int id,pila;
    char type;
};

struct head{
    int i,ie,oe,b,d,s,q,input_exit,output_exit;
    char n[30];
};
