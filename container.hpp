#ifndef CONTAINER_HPP
#define CONTAINER_HPP
#include <QtWidgets/QWidget>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QPushButton>
#include <QtCore/QPoint>
#include <iostream>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
//#include </QtCore/QObject>
template<class T>
class mov_cnt:public T{
public:
  QPoint old_pos;
  mov_cnt():T(){}
  mov_cnt(QObject *parent):T(parent){}
  ~mov_cnt(){}
};

#endif //CONTAINER.HPP
