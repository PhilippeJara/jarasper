#ifndef ECL_INJECTION_H
#define ECL_INJECTION_H
#ifdef slots
#undef slots
#endif
#include "ecl/ecl.h"

extern "C"{
extern void init_lib_EXAMPLE_WITH_DEP_2__ALL_SYSTEMS(cl_object);
}
void inject_ecl(int argc,char** argv){
/* Initialize ECL */
cl_boot(argc, argv);

/* Initialize the library we linked in. Each library
 * has to be initialized. It is best if all libraries
 * are joined using ASDF:MAKE-BUILD.
 */

ecl_init_module(NULL, init_lib_EXAMPLE_WITH_DEP_2__ALL_SYSTEMS);
}
#endif
