#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include "share_memory.h"
#include "functions_memory.h"

void open_memory(char* name_memory){
    fd = shm_open(name_memory, O_RDWR, 0660);
    if (fd < 0) {
        cerr << "Error abriendo la memoria compartida: "
	        << errno << strerror(errno) << endl;
        exit(1);
    }
}