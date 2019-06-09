#pragma once

#include <iostream>

using namespace std;

struct exam{
    int id,pila;
    char type;
};

struct head{
    int i,ie,oe,b,d,s,q, first_exit, end_exit, first_b, end_b, first_d, end_d, first_s, end_s;
    char n[30];
};
