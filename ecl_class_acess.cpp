#include "ecl_class_acess.hpp"


using namespace std;

auto bus_ecl(bus& busarg){
  //cl_print(1, ecl_make_integer(busarg.info.to_ulong()));
  return cl_list(2,
		 c_string_to_object("list"),
		 (int)busarg.bits);
}

auto memory_ecl(memory& memarg){
  return ecl_make_integer((int)memarg.len);
}

auto regist_ecl(regist& registarg){
  return cl_list(2,
		 c_string_to_object("list"),
		 (int)registarg.bits);
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
  cl_eval(control_unit_ecl(cuarg));
  
  for (auto& busarg:cuarg.buses){
    get<0>(busarg);
    bus_ecl(*(get<1>(busarg)));
  }



  for (auto& regarg:cuarg.regists_in_out){
    get<0>(regarg);  
    regist_ecl(*get<0>(get<1>(regarg)));  }

  
}

cl_object parse_overseer(overseer& ovarg){
  for (auto& cuarg:ovarg.control_units){
    parse_control_units(*cuarg);
  }
  for (auto& memarg:ovarg.memories){
    memory_ecl(*memarg);
  }
  return NULL;
}


