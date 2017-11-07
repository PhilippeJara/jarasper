#ifndef CUSTOMBUSITEM_H
#define CUSTOMBUSITEM_H
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsRectItem>
#include "scene.h"
#include "customrectitem.h"
#include "math.h"
#include "QtGui/QTextDocument"
#include "QtGui/QPainterPath"
#include "QtWidgets/QStyleOptionGraphicsItem"
#include "QtGui/QPainter"
#include "QtGui/QPainterPathStroker"
#include <unordered_map>
#include <memory>


class custom_bus_item : public QObject , public QGraphicsPathItem
{
     
  Q_OBJECT
public:
  QGraphicsRectItem base_bus;
  custom_bus_item(QGraphicsItem* parent = 0);
  std::unordered_map<CustomRectItem *,
		     std::unique_ptr<QPainterPath>> linked_registers;
   
  void paint(QPainter *painter,
	     const QStyleOptionGraphicsItem *option,
	     QWidget *widget);
  
  void link(CustomRectItem *);
  void remove_link(CustomRectItem *);

public slots:
  void update_path(CustomRectItem*);

};

#endif // CUSTOBUSITEM_H
