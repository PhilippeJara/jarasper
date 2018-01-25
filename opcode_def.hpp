#ifndef OPCODE_DEF_HPP
#define OPCODE_DEF_HPP
#include <vector>
#include <cstddef> 
#include <iostream> 





class microcode {
  size_t operatr;
  std::vector<size_t> operands;

 public:
  microcode(size_t operatr = 0, std::vector<size_t> operands = {0}):operatr(operatr),operands(operands){};
  size_t get_operator(){return operatr;}
  std::vector<size_t> get_operands(){return operands;}
  size_t get_operand(int index){
    if((operands.size() < index) || (index == 0)){return 0;}
    else { return operands.at(index -1);}}
};
class opcode{
  std::vector<microcode> microcodes;
  
public:
  opcode(std::vector<microcode> microcods):microcodes(microcods){};
  std::vector<microcode> get_microcodes(){return microcodes;}
  microcode get_microcode(int index){
    if((microcodes.size() < index) || (index == 0)){return 0;}
    else { return microcodes.at(index -1);}}
};

#endif
