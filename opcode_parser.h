#ifndef OPCODE_PARSER_H
#define OPCODE_PARSER_H

//#include "opcode_def.hpp"
#endif // OPCODE_PARSER_H
#include "global_macros.h"
#include <string>
#include "atoms.h"
#include "opcode_def.hpp"

class opcodes;
std::map<size_t, opcode> parseAllOpcodes(std::string opcodef[MAXOPCODE][MAXMICROC], std::string Dopcode[100][MAXMICROC]);//, opcodes opcode_return[100][MAXMICROC]);
opcode parseOpcode(std::string opcodef[MAXMICROC], std::string Dopcode[MAXMICROC]);//, opcodes opcode_return[MAXMICROC]);
//std::string parseOpcodeLine(std::string opcodeLine, std::string Dopcode[MAXMICROC], int &lastIndx);
std::string parseOpcodeLine(std::string opcodeLine, std::string Dopcode[MAXMICROC], int &lastIndx, opcode* opcod);//, opcodes opcode_return[MAXMICROC], int &lastIndx);
