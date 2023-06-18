#ifndef OPCODE_DEF_HPP
#define OPCODE_DEF_HPP
#include <vector>
#include <cstddef> 
#include <iostream> 





class microcode {
 public:
  size_t operatr;
  std::vector<size_t> operands;
  std::string literal;


  microcode(size_t operatr = 0, std::vector<size_t> operands = {0}):operatr(operatr),operands(operands){}

  size_t get_operator(){return operatr;}
  std::vector<size_t> get_operands(){return operands;}
  size_t get_operand(int index){
    //if((operands.size() < index) || (index == 0)){return 0;}
    //else { return operands.at(index -1);}}
      return operands[index];}


};
class opcode{
public:
  std::vector<microcode> microcodes;
  std::string literal;
  //this was supposed to be name operator not operand wtf
  size_t operand;

  opcode(){}
  opcode(std::vector<microcode> microcods):microcodes(microcods){}
  opcode(std::vector<microcode> microcods, std::string literal):microcodes(microcods){}
  //opcode(std::vector<microcode> microcods, size_t operand=0):microcodes(microcods),operand(operand){}

  std::vector<microcode> get_microcodes(){return microcodes;}
  size_t get_operand(){return operand;}
  microcode get_microcode(int index){
    if((microcodes.size() < index) || (index == 0)){return 0;}
    else { return microcodes.at(index -1);}}
  std::string get_literal(){return literal;}
};

#endif
