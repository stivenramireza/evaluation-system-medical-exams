#pragma once

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include "share_memory.h"

void command_rep(char* commands[], int length);
void interactive_mode(char* name_memory, int seconds);
void obtener_examenes(char* name_memory, int n_examenes);