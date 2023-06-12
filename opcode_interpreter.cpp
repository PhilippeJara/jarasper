#include "atoms.h"
// //inicialmente vamos decidir como ler os codigos, os opcodes são compostos pelo 

// Para assignment:
// encontra todos que estao conectados em um bus no seu "in" e depois de criar esta lista, encontra todos conectados no mesmo bus por meio do "out", todos da lista que estão conectados no "in" podem receber de todos que estão conectados no "out". For all X, Y : X <- Y // = // Yout, Xin

// Para ADD, SUB, SHR, SHL:
// encontra todos os ALUS e cria uma operação(ADD, SUB, SHR, SHL) para cada.

// Para WRITE, READ:
// Encontra todos os MDR's e cria uma operação para cada, usando como MAR o valor do MAR aberto no cu. Logo esta operação implicitamente necessita setor o "out" do MAR antes de aplicar a mesma.

/* a ideia inicial é conseguir uma forma de ler os códigos de uma
   fonte e criar opcodes por meio deles, a representaćão inicial dos
   microcodes será feita da seguinte forma: [microcode][op1][op2] e
   com as seguintes enumeraćões para os opcodes:

   00: halt
   01: assignment
   02: add   (what alu)
   03: read from memory adress
   04: write to memory adress
   05: sub   (what alu)
   06: shl   (what alu, how many bits)
   07: shr   (what alu, how many bits)
   08: branch on equal (what alu, if true or false)
   09: branch on zero   (what alu, if true or false)
   0A: branch on carry   (what alu, if true or false)
   0B: branch on negative   (what alu, if true or false)
   0C: assignment from literal (will take the literal from opcode operand)
   0D: increment instruction counter
*/
// ASSUMINDO QUE MICROCODES E OPCODES TEM O MESMO COUNT DE OPERANDOS E OPERADORES
// E MESMA QUANTIDADE DE BITS

using namespace std;


int control_unit::interpret_minst(microcode mcode, const vector<shared_ptr<memory>> &memories){
  auto operador = mcode.get_operator();
  auto operandos = mcode.get_operands();

  switch(operador){
  case 0x0:{
      //returns -1 in order to stop the operation period, not just of the opcode
      return -1;
  }
  case 0x1:{
    auto origem = operandos.at(0);
    set<size_t> destinos(operandos.begin(), operandos.end());
    for(const auto& destino: destinos){
      cout << "*new assignment*"<< endl;
      if (destino != origem){this->assignment(origem, destino);}
    }
    break;
  }
  case 0x2:{
    cout<<"*new add*" << endl;
    this->add(operandos.at(0));
    break;
  }
  case 0x3:{
    cout << "get_mdr: "
	 << operandos.at(1)
	 << endl;	
    auto mdr = get_mdr(operandos.at(1));
    cout << "get_mar: "
	 << operandos.at(0)
	 << endl;
    auto mar = get_mar(operandos.at(0));
    read(mar, mdr, memories);
    cout << "memread: " << endl;
    break;
  }
  case 0x4:{
    /// a ID do mdr e do mar utilizada é a sua sequencia em mdrs_id e mars_is, não a sua principal em registers_in_out!!!
    cout << "get_mdr: "
	 << operandos.at(1)
	 << endl;	
    auto mdr = get_mdr(operandos.at(1));
    cout << "get_mar: "
	 << operandos.at(0)
	 << endl;
    auto mar = get_mar(operandos.at(0));
    write(mar, mdr, memories);
    (cout << "memwrite: " << endl);
    break;
  }
  case 0x5:{
    this->sub(operandos.at(0));
    (cout<< "sub(overflow, carry?): " << endl);
    break;
  }
  case 0x6:{
    auto amnt = this->get_alu(0)->B->info.to_ulong();
    SHL(operandos.at(0), amnt);
    break;
  }
  case 0x7:{
    auto amnt = this->get_alu(0)->B->info.to_ulong();
    SHR(operandos.at(0), amnt);
    break;
  }
//      08: branch on equal
//      09: branch on zero
//      0A: branch on carry
//      0B: branch on negative


  case 0x8:{
      //returns 1 to stop just the opcode in question
      auto alu = this->get_alu(operandos.at(0));
      int condition = operandos.at(1);
      if(alu->get_equal() != condition){return 1;}
    break;
  }
  case 0x9:{
      //returns 1 to stop just the opcode in question
      auto alu = this->get_alu(operandos.at(0));
      int condition = operandos.at(1);
      if(alu->get_zero() != condition){return 1;}
    break;
  }
  case 0xA:{
      //returns 1 to stop just the opcode in question
      auto alu= this->get_alu(operandos.at(0));
      int condition = operandos.at(1);
      if(alu->get_carry() != condition){return 1;}
    break;
  }
  case 0xB:{
      //returns 1 to stop just the opcode in question
     auto alu = this->get_alu(operandos.at(0));
      int condition = operandos.at(1);
      if(alu->get_negative() != condition){return 1;}
    break;
  }
  case 0xC:{
      //auto literal = operandos.at(0);
      auto literal = trim_input(this->operand_amnt * this->operand_size,this->instruction_register->info).to_ulong();
      set<size_t> destinos(operandos.begin(), operandos.end());
//      for(const auto& destino: destinos){
//        cout << "*new assignment literal*"<< endl;
        /*if (destino != literal){*/
      this->assignment_literal(literal, operandos.at(1));
//      }
      break;
  }
  case 0xD:{
      //increment instruction counter
      auto current_val = this->instruction_counter->info;
      this->instruction_counter->set(current_val.to_ulong() + 1);
    break;
  }
  default:{cout << "código de microinstrućão inválido: " << operador << endl; exit(1);}
  }
  return 0;
}
void control_unit::sync_bus(){this->reg_out();this->reg_in();}
int control_unit::opcode_execute(const vector<shared_ptr<memory>> &memories){
  if (get_operator(this->instruction_register->info,
		   this->operator_size,
           this->operand_size,
		   this->operand_amnt) < this->opcodes.size()){
    auto opcode_inst = this->opcodes.at(get_operator(this->instruction_register->info,
						     this->operator_size,
						     this->operand_size,
						     this->operand_amnt));
    auto opcode_operand = opcode_inst.operand;
    for(auto mcode: opcode_inst.get_microcodes()){
      int ret = this->interpret_minst(mcode, memories);
      this->sync_bus();
      //if return is -1 we reached a HALT, so all the opcodes should stop
      if (ret == -1){return -1;}
      //if return is 1 we didn't satisfy a branch condition, so this opcode execution should stop
      if (ret == 1){break;}
    }
  
  }
  else{
    cout << "opcode não existe" << endl;
  }
  return 0;
}

