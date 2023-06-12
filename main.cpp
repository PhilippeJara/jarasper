#include "opcode_def.hpp"
#include "mwin.h"
#include <QtWidgets/QApplication>
//#include  "ecl/ecl.h"
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mwin w;
    w.show();
    return  a.exec();
    
}
