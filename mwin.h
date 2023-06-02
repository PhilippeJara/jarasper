#ifndef MWIN_H
#define MWIN_H
#include "atoms.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <ui_mwin.h>
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
  void fill_opcodes_tree();
  void fill_memory_list();
  ~mwin();

private slots:
  void on_criar_cu_clicked();
  void on_repl_input_returnPressed();
  void on_criar_regist_clicked();
  void on_criar_bus_clicked();
  void on_criar_alu_clicked();
  void on_microcode_repl_input_returnPressed();


  void on_pushButton_clicked();

  void on_memory_list_itemChanged(QListWidgetItem *item);

  void on_toggle_hex_memory_list_stateChanged(int arg1);

private:
    Ui::mwin *ui;
};


#endif // MWIN_H
