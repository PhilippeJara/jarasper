#ifndef CUSTOMBUSITEM_H
#define CUSTOMBUSITEM_H
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsRectItem>
#include "scene.h"
#include "math.h"
#include "QtGui/QTextDocument"
#include "QtGui/QPainterPath"
#include "QtWidgets/QStyleOptionGraphicsItem"
#include "QtGui/QPainter"

class custom_bus_item : public QObject , public QGraphicsPathItem
{
     
Q_OBJECT
public:
 custom_bus_item(QGraphicsItem* parent = 0);

 void paint(QPainter *painter,
	    const QStyleOptionGraphicsItem *option,
	    QWidget *widget);
  
 public slots:
 void update_path();
};

#endif // CUSTOBUSITEM_H
