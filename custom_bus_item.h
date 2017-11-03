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
#include "container.hpp"

class custom_bus_item : public QObject , public QGraphicsPathItem
{
     
  Q_OBJECT
public:
  

  custom_bus_item(QGraphicsItem* parent = 0);
  std::unordered_map<mov_cnt<CustomRectItem> *,
		     std::unique_ptr<QPainterPath>> linked_registers;
  void paint(QPainter *painter,
	     const QStyleOptionGraphicsItem *option,
	     QWidget *widget);
  void link(mov_cnt<CustomRectItem> *);
  void remove_link(mov_cnt<CustomRectItem> *);

public slots:
  void update_path(mov_cnt<CustomRectItem>*);

};

#endif // CUSTOBUSITEM_H
