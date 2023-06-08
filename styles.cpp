#include "atoms.h"

template <> void set_styling(regist* obj){
  obj->display->setRect(0,0,60,30);
  obj->display->setBrush(Qt::gray);
  obj->display->info.setPos(15,10);
  obj->display->setZValue(1);
}

template <> void set_styling(control_unit* obj){
  obj->display->setRect(0,0,120,120);
  obj->display->setBrush(Qt::white);
  obj->display->setZValue(1);
}

template <> void set_styling(alu* obj){
  obj->display->setRect(0,0,150,150);
  obj->display->setText(QString("E:%1 Z:%2 N:%3 O:%4 C:%5").arg(obj->f_equal).arg(obj->f_zero).arg(obj->f_negative).arg(obj->f_overflow).arg(obj->f_carry));
  obj->display->setBrush(Qt::darkGray);
  obj->display->info.setPos(15,10);
  obj->display->setZValue(1);
}
template <> void set_styling(memory* obj){
  obj->display->setRect(0,0,30,60);
  obj->display->setBrush(Qt::magenta);
}


