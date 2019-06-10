#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <semaphore.h>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
  shm_unlink("evaluator");
  for(int i = 0; i < 5; ++i){
    string _mem_name = "evaluator";
    string mutex_name = _mem_name + "_input_" + to_string(i).c_str() + "_mutex";
    string fulls_name = _mem_name + "_input_" + to_string(i).c_str() + "_fulls";
    string empty_name = _mem_name + "_input_" + to_string(i).c_str() + "_empty";
    sem_unlink(mutex_name.c_str());
    sem_unlink(fulls_name.c_str());
    sem_unlink(empty_name.c_str());
  }
  return 0;
}