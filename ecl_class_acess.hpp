#ifndef ECL_C_ACESS
#define ECL_C_ACESS
#include "atoms.h"
#ifdef slots
#undef slots
#endif
#include "ecl/ecl.h"

#include <string>
#include <iostream>





auto parse_control_units(control_unit& cuarg);
cl_object parse_overseer(overseer& ovarg);


#endif
