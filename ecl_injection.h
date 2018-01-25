#ifndef ECL_INJECTION_H
#define ECL_INJECTION_H
#ifdef slots
#undef slots
#endif
#include "ecl/ecl.h"
#include "stdlib.h"



extern "C"{
extern void init_lib_RUNTIME__ALL_SYSTEMS(cl_object);
}
void inject_ecl(int argc,char** argv){
/* Initialize ECL */
cl_boot(argc, argv);

/* Initialize the library we linked in. Each library
 * has to be initialized. It is best if all libraries
 * are joined using ASDF:MAKE-BUILD.
 */

ecl_init_module(NULL, init_lib_RUNTIME__ALL_SYSTEMS);
cl_load(1, c_string_to_object("\"./lisp_files/parser/parser--all-systems.fasb\"")); 
//cl_eval(c_string_to_object("(load \"./lisp_files/parser/parser--all-systems.fasb\")"));
//cl_eval(c_string_to_object("(load \"./lisp_files/parser/package.lisp\")"));
//cl_eval(c_string_to_object("(load \"./lisp_files/parser/parser.lisp\")"));
  //cl_eval(c_string_to_object("(parser:load-notice)"));
  atexit(cl_shutdown);
}
#endif
