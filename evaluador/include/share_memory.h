#pragma once

#include <semaphore.h>
#include <iostream>

using namespace std;


struct exam  {
    int id, _queue, _quant, _state;
    char type;
};

struct head{
    int i, ie, oe, b, d, s, q, input_exit, output_exit, _uuid;
    char n[30];
};