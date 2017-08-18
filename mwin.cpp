#include "mwin.h"
#include "../builds/build-jarasper-Desktop_Qt_5_9_1_GCC_64bit-Debug/ui_mwin.h"

mwin::mwin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mwin)
{
    ui->setupUi(this);
}

mwin::~mwin()
{
    delete ui;
}
