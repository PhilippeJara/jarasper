#ifndef MWIN_H
#define MWIN_H
#include <qt5/QtWidgets/QMainWindow>
#include "container.hpp"
#include "atoms.h"
#include "opmap.hpp"
#include <memory>
#include <iostream>

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
  private:
    Ui::mwin *ui;
};

#endif // MWIN_H
