#pragma once

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <iostream>
#include <sys/types.h>
#include "share_memory.h"

void open_memory(char* name_memory);