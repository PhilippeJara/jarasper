#ifndef STYLES_HPP
#define STYLES_HPP
#include "qt5/QtWidgets/QFrame"
#include "qt5/QtCore/QtCore"
template <typename T> void set_styling(T obj){
  obj->display->setFixedSize(75, 25);
  obj->display->setStyleSheet("background-color:white; border: 1px solid black; qproperty-alignment: AlignCenter");
}

#endif
