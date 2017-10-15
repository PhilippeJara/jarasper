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



// class register_display : public mov_cnt<QLabel>{
//   Q_OBJECT

// public:

//   register_display(QWidget *);
//   ~register_display();
// public slots:

// signals:
  
// };
// class control_unit_display : public mov_cnt<QLabel>{
//   Q_OBJECT

// public:

//   control_unit_display(QWidget *);
//   ~control_unit_display();
// public slots:

// signals:
// };
// class alu_display : public mov_cnt<QLabel>{

//   Q_OBJECT

// public:

//   alu_display(QWidget *);
//   ~alu_display();
// public slots:

// signals:
// };
// class memory_display : public mov_cnt<QLabel>{

//   Q_OBJECT

// public:

//   memory_display(QWidget *);
//   ~memory_display();
// public slots:

// signals:
// }
//;
#endif //CONTAINER.HPP
