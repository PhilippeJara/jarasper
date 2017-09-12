#include "mwin.h"
#include <qt5/QtWidgets/QApplication>
//#include "atoms.h"
//#include  "ecl/ecl.h"
#include <stdio.h>
//#include "opmap.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mwin w;
    w.show();

  return a.exec();
}
