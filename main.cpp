#include "mwin.h"
#include <QtWidgets/QApplication>
//#include  "ecl/ecl.h"
#include <stdio.h>
#include "ecl_injection.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mwin w;
    w.show();
    //    cl_boot(argc,  argv);
    //cl_eval(c_string_to_object("(print \"deu certo !!!\")"));
    inject_ecl(argc, argv);
    // cl_eval(c_string_to_object("(print \"deu certo !!!\")"));
    return  a.exec();
    
}
