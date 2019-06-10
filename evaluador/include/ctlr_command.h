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
void subcommand_list(char* name_memory, string interactive_subcommand1);
void subcommand_processing(char* name_memory);
void subcommand_waiting(char* name_memory);
void subcommand_reported(char* name_memory);
void subcommand_reactive(char* name_memory);
void subcommand_all(char* name_memory);
void subcommand_update(char* name_memory, string interactive_subcommand1, string interactive_subcommand2);
void update_reactive(string reactive, int reactive_level);