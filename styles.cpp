#include "styles.hpp"
#include "atoms.h"
template <> void set_styling(regist* obj){
  obj->display->setFixedSize(75, 25);
  obj->display->setStyleSheet("background-color:white; \
                               border: 1px solid black; \
                               qproperty-alignment: AlignCenter");
}
template <> void set_styling(std::shared_ptr<regist> obj){
  obj->display->setFixedSize(75, 25);
  obj->display->setStyleSheet("background-color:white; \
                               border: 1px solid black; \
                               qproperty-alignment: AlignCenter");
}
template <> void set_styling(control_unit* obj){
  obj->display->setFixedSize(150, 150);
  obj->display->setStyleSheet("background-color:white; \
                               border: 1px solid black; \
                               qproperty-alignment: AlignCenter");
}
template <> void set_styling(std::shared_ptr<control_unit> obj){
  obj->display->setFixedSize(150, 150);
  obj->display->setStyleSheet("background-color:white; \
                               border: 1px solid black; \
                               qproperty-alignment: AlignCenter");
}
