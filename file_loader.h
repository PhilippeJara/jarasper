#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#endif // FILE_LOADER_H
#include<string>
#include <atoms.h>
#include "global_macros.h"

int loadMem(std::string path, memory* mem_target);

int loadOpcode(std::string opcode[MAXOPCODE][MAXMICROC], std::string path);
