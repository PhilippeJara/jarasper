#ifndef MWIN_H
#define MWIN_H
#include "atoms.h"
#include <QtWidgets/QMainWindow>
#include "opmap.hpp"
#include <memory>
#include <iostream>
//#include "customrectitem.h"

namespace Ui {
class mwin;
}

class mwin : public QMainWindow
{
    Q_OBJECT

public:
  overseer ov;
  explicit mwin(QWidget *parent = 0);
  ~mwin();

private slots:
    void on_criar_cu_clicked();
    void on_repl_input_returnPressed();


private:
    Ui::mwin *ui;
};


#endif // MWIN_H
