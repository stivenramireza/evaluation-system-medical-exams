#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include "../include/share_memory.h"
using namespace std;
int main(){
    int fd = shm_open("test3", O_RDWR, 0660);

    int sizeHeader = sizeof(head);
    int sizeExam   = sizeof(exam);

    void* dir = mmap(NULL, sizeHeader, PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0);

    char* init_dir = (char*)dir;
    char* init_queue = init_dir+sizeHeader;
    cout<<(int *)init_dir<<endl;
    head *pheader = (head *) init_dir;
    cout<<pheader->i<<endl;
    exam *pexam = (exam *)init_queue;
    cout<<pexam->id<<endl;
    pexam = (exam *)(init_queue + 3*sizeExam);
    cout<<pexam->id<<endl;
}



