#ifndef ECL_C_ACESS
#define ECL_C_ACESS
#include "atoms.h"
#include "ecl/ecl.h"
#include <string>
#include <iostream>



auto bus_ecl(bus& busarg){
  //cl_print(1, ecl_make_integer(busarg.info.to_ulong()));
  return ecl_make_integer(busarg.info.to_ulong());
}

auto memory_ecl(memory& memarg){
  return ecl_make_integer((int)memarg.len);
}

auto regist_ecl(regist& registarg){
  return ecl_make_integer((int)registarg.bits);
}

// auto alu_ecl(alu aluarg){
//   return 
// }


auto control_unit_ecl(control_unit& cuarg){
  return cl_list(9,
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
    std::get<0>(busarg);
    bus_ecl(*(std::get<1>(busarg)));
  }



  for (auto& regarg:cuarg.regists_in_out){
    std::get<0>(regarg);  
    regist_ecl(*std::get<0>(std::get<1>(regarg)));  }

  
}

auto parse_overseer(overseer& ovarg){
  for (auto& cuarg:ovarg.control_units){
    parse_control_units(*cuarg);
  }
  for (auto& memarg:ovarg.memories){
    memory_ecl(*memarg);
  }
}
#endif
