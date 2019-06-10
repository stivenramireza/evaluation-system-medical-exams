#pragma once

#include <iostream>
#include <time.h>

using namespace std;


struct exam  {
    int id, _queue, _quant, _state;
    char type;
    time_t t_start, t_end;
};

struct head{
    int i, ie ,oe ,b ,d, s , q, in_oe, out_oe, 
        first_exit, end_exit, first_b, first_o, 
        end_b, first_d, end_d, first_s, end_s, end_o, _uuid, stop,
        qua_o,qua_b,qua_d,qua_s;
    char n[30];
};