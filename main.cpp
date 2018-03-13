#include "mwin.h"
#include <QtWidgets/QApplication>
#include <stdio.h>
#include "ecl_class_acess.hpp"
#include "ecl_injection.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mwin w;
    w.show();
    inject_ecl(argc, argv);
    parse_overseer(w.ov);
    return  a.exec();
    
}
