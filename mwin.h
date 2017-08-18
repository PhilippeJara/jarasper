#ifndef MWIN_H
#define MWIN_H

#include <qt5/QtWidgets/QMainWindow>

namespace Ui {
class mwin;
}

class mwin : public QMainWindow
{
    Q_OBJECT

public:
    explicit mwin(QWidget *parent = 0);
    ~mwin();

private:
    Ui::mwin *ui;
};

#endif // MWIN_H
