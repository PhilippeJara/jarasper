#include "atoms.h"

template <> void set_styling(regist* obj){
  obj->display->setRect(0,0,60,30);
  obj->display->setBrush(Qt::gray);
  obj->display->info.setPos(15,10);
}

template <> void set_styling(control_unit* obj){
  obj->display->setRect(0,0,120,120);
  obj->display->setBrush(Qt::white);
}

template <> void set_styling(alu* obj){
  obj->display->setRect(0,0,120,120);
  obj->display->setBrush(Qt::blue);
  obj->display->info.setPos(15,10);
}
a
