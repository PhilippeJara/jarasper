#ifndef STYLES_HPP
#define STYLES_HPP
#include "qt5/QtWidgets/QFrame"
#include "qt5/QtCore/QtCore"
//#include "atoms.h"
template <typename T> void set_styling(T obj){
  obj->display->setRect(3,4,60,30);
  obj->display->setBrush(Qt::gray);
}

#endif
