#include "atoms.h"
#include <string>

using namespace std;

enum opt{
	 quit = 3,
	 make_cu = 4,
	 make_alu = 5,
	 make_register= 6,
	 make_memory= 7,
	 make_bus = 8
};

int decode_input(string in){
  if(in == "oi"){
    return 1;
  }
  else if (in == "ola"){
    return 2;
  }
  else if(in == "quit"){
    return 3;
  }
  else if(in == "make_cu"){
    return 4;
  }
  else if(in == "make_alu"){
    return 5;
  }
  else if(in == "make_register"){
    return 6;
  }
  else if(in == "make_memory"){
    return 7;
  }
  else if(in == "make_bus"){
    return 8;
  }
  return -1;
}


size_t  call_make_cu(overseer &ov){
  size_t in;
  cout << "tamanho em bits do registrador interno da CU: ";
  cin >> in;
  ov.control_units.push_back(make_shared<control_unit<4,4>>(in));
  return ov.control_units.size() - 1;
}

size_t  call_make_alu(overseer &ov){
  size_t a, b, z, cu_id;
  cout << "id da unidade de controle : ";
  cin >> cu_id;
  cout << "tamanho em bits do registrador A: ";
  cin >> a;
  cout << "tamanho em bits do registrador B: ";
  cin >> b;
  cout << "tamanho em bits do registrador Z: ";
  cin >> z;
  auto cu = ov.control_units.at(cu_id);
  return cu->make_alu(cu->get_register(cu->make_regist(a)),
		      cu->get_register(cu->make_regist(b)),
		      cu->get_register(cu->make_regist(z)));
}
size_t call_make_regist(overseer &ov){
  size_t sze, cu_id;
  cout << "id da unidade de controle : ";
  cin >> cu_id;
  cout << "tamanho em bits do registrador : ";
  cin >> sze;
  return ov.control_units.at(cu_id)->make_regist(sze);
}


size_t  call_make_memory(overseer &ov){
  size_t size, mem_block_len, addr_bus_len, data_bus_len;
  cout << "tamanho em unidades da memória : ";
  cin >> size;
  cout << "tamanho em bits de cada unidade da memória : ";
  cin >> mem_block_len;
  cout << "tamanho em bits do adress bus : ";
  cin >> addr_bus_len;
  cout << "tamanho em bits do data bus : ";
  cin >> data_bus_len;
  ov.memories.push_back(make_shared<memory>(size,
					    mem_block_len,
					    addr_bus_len,
					    data_bus_len));
  return  ov.memories.size() - 1;
}
size_t  call_make_bus(overseer &ov){
  size_t sze, cu_id;
  cout << "id da unidade de controle : ";
  cin >> cu_id;
  cout << "tamanho em bits do bus : ";
  cin >> sze;
  return ov.control_units.at(cu_id)->make_bus(sze);
}

void start_builder_repl(){
  string scope= "OVERSEER> ";
  int input = 0;
  string input_str;
  overseer ov;
  while(input != quit){
    input = 0;
    cout << scope; 
    cin >> input_str; 
    cin.ignore();
    input = decode_input(input_str);
    
    switch(input){
      
    case make_cu:{
      auto id = call_make_cu(ov);
      cout << "Control Unit "<< id << endl;
      break;
    }
    case make_memory:{
      auto id = call_make_memory(ov);
      cout << "Memory "<< id << endl;
      break;
    }
    case make_register:{
      auto id = call_make_regist(ov);
      cout << "Register "<< id << endl;
      break;
    }
    case make_bus:{
    
      auto id = call_make_bus(ov);
      cout << "Bus "<< id << endl;
      break ;
    }
    case make_alu:{
      auto id = call_make_alu(ov);
      cout << "ALU  "<< id << endl;
      break;
    }
    case quit:{break;}
    default:{cout<< "input inválido" << endl; break;}
    }
  }
};



