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
   02: add
   03: read from memory adress
   04: write to memory adress
   05: sub
   06: shl
   07: shr
   08: branch on equal
   09: branch on zero
   0A: branch on carry
   0B : branch on negative
*/
// ASSUMINDO QUE MICROCODES E OPCODES TEM O MESMO COUNT DE OPERANDOS E OPERADORES
// E MESMA QUANTIDADE DE BITS

using namespace std;

void control_unit::interpret_minst(microcode mcode, const vector<shared_ptr<memory>> &memories){
  auto operador = mcode.get_operator();
  auto operandos = mcode.get_operands();
  switch(operador){
  case 1:{
    auto origem = operandos.at(0);
    set<size_t> destinos(operandos.begin(), operandos.end());
    for(const auto& destino: destinos){
      cout << "*new assignment*"<< endl;
      if (destino != origem){this->assignment(origem, destino);}
    }
    break;
  }
  case 2:{
    cout<<"*new add*" << endl;
    this->add(operandos.at(0));
    break;
  }
  case 3:{
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
  case 4:{
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
  case 5:{
    this->sub(operandos.at(0));
    (cout<< "sub(overflow, carry?): " << endl);
    break;
  }
  case 6:{
    SHL(operandos.at(0), operandos.at(1));
    break;
  }
  case 7:{
    SHR(operandos.at(0), operandos.at(1));
    break;
  }
  default:{cout << "código de microinstrućão inválido: " << operador << endl; exit(1);}
  }
}
void control_unit::sync_bus(){this->reg_out();this->reg_in();}
void control_unit::opcode_execute(const vector<shared_ptr<memory>> &memories){
  if (get_operator(this->cu_reg->info,
		   this->operator_size,
           this->operand_size,
		   this->operand_amnt) < this->opcodes.size()){
    auto opcode_inst = this->opcodes.at(get_operator(this->cu_reg->info,
						     this->operator_size,
						     this->operand_size,
						     this->operand_amnt));
    for(auto mcode: opcode_inst.get_microcodes()){
      this->interpret_minst(mcode, memories);
      this->sync_bus();
    }
  
  }
  else{
    cout << "opcode não existe" << endl;
  }
}

