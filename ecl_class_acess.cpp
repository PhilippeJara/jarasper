#include "ecl_class_acess.hpp"


using namespace std;

auto bus_ecl(bus& busarg){
  //cl_print(1, ecl_make_integer(busarg.info.to_ulong()));
  return cl_list(2,
		 c_string_to_object("list"),
		 ecl_make_integer((int)busarg.bits));
}

auto memory_ecl(memory& memarg){
  return ecl_make_integer((int)memarg.len);
}

auto regist_ecl(regist& registarg){
  return cl_list(2,
		 c_string_to_object("list"),
		 ecl_make_integer((int)registarg.bits));
}

// auto alu_ecl(alu aluarg){
//   return 
// }


auto control_unit_ecl(control_unit& cuarg){
  return cl_list(10,
		 c_string_to_object("list"),
		 ecl_make_integer((int)cuarg.map_reg_counter),
		 ecl_make_integer((int)cuarg.map_bus_counter),
		 ecl_make_integer((int)cuarg.map_alu_counter),
		 ecl_make_integer((int)cuarg.map_mar_counter),
		 ecl_make_integer((int)cuarg.map_mdr_counter),
		 ecl_make_integer((int)cuarg.map_func_counter),
		 ecl_make_integer((int)cuarg.operator_size),
		 ecl_make_integer((int)cuarg.operand_size),
		 ecl_make_integer((int)cuarg.operand_amnt)
		 );
}





auto parse_control_units(control_unit& cuarg){
  // cl_eval(cl_append(3,
  // 		    c_string_to_object("("),
  // 		    control_unit_ecl(cuarg),
  // 		    c_string_to_object(")")));
  //cl_make_array
  auto cu_info = control_unit_ecl(cuarg); 
  cl_princ(1, cu_info);
  cl_eval(cl_list(2, c_string_to_object("parser:looker"), cu_info) );
  //cl_eval(control_unit_ecl(cuarg));
  auto bus = cl_list(1, c_string_to_object("list"));
  auto regs = cl_list(1,c_string_to_object("list"));
  
  for (auto& busarg:cuarg.buses){

    
    bus = cl_append(2, bus, cl_list(2,
				    ecl_make_integer(get<0>(busarg)),
				    bus_ecl(*(get<1>(busarg)))));
    cl_eval(cl_list(2, c_string_to_object("parser:looker"),bus));
    
  }
  
  for (auto& regarg:cuarg.regists_in_out){

    regs = cl_append(2,
		   regs,
		   cl_list(2,
			   ecl_make_integer(get<0>(regarg)),
			   regist_ecl(*get<0>(get<1>(regarg)))));
    
    cl_eval(cl_list(2, c_string_to_object("parser:looker"), regs));
    
  }

  return cl_list(3, cu_info, bus, regs);
}

cl_object parse_overseer(overseer& ovarg){
  auto cu_full = cl_list(0);
  for (auto& cuarg:ovarg.control_units){
    cu_full = cl_append(2,cu_full, parse_control_units(*cuarg));
  }
  for (auto& memarg:ovarg.memories){
    memory_ecl(*memarg);
  }
  
  return cu_full;
}


