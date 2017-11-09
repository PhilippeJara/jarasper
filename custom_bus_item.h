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
  std::unordered_map<CustomRectItem *,
		     std::unique_ptr<QPainterPath>> linked_registers;
  custom_bus_item(QGraphicsItem* parent = 0, size_t wid = 5);   
  void paint(QPainter *painter,
	     const QStyleOptionGraphicsItem *,
	     QWidget *);
  
  void link(CustomRectItem *);
  void remove_link(CustomRectItem *);

public slots:
  void update_path(CustomRectItem*);

private:
  size_t width;
};

#endif // CUSTOBUSITEM_H
