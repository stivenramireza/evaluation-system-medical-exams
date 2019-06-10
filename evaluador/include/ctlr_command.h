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

void command_ctlr(char* commands[], int length);