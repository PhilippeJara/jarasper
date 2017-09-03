#include <qt5/QtWidgets/QWidget>
#include <qt5/QtGui/QMouseEvent>
#include <qt5/QtWidgets/QPushButton>
#include <qt5/QtCore/QPoint>
#include <iostream>
#ifndef CONTAINER_HPP
#define CONTAINER_HPP
template<class T>
class mov_cnt:public T{
public:
  QPoint old_pos;
  mov_cnt():T(){}
  mov_cnt(QWidget *parent):T(parent){}
  ~mov_cnt(){}

  void mousePressEvent(QMouseEvent *event){
    old_pos=event->globalPos();
  }
  void mouseMoveEvent(QMouseEvent *event){
    if(event && Qt::LeftButton){
      const QPoint delta = event->globalPos() - old_pos;
      this->move(this->x()+delta.x(), this->y()+delta.y());
      old_pos = event->globalPos();
    }
  }
};
  
#endif //CONTAINER.HPP
