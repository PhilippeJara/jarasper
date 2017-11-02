#include "custom_bus_item.h"
#include "atoms.h"

custom_bus_item::custom_bus_item(QGraphicsItem* parent):QObject(), QGraphicsPathItem(parent){
  QPainterPath path;
  path.addRect(100, 20, 100, 20);
  this->setFlags(QGraphicsItem::ItemIsSelectable|
		 QGraphicsItem::ItemIsMovable);
  this->setPath(path);
}


// setPath(QPainterPath(QPointF(120, 130)));
//   setBrush(Qt::darkGreen);
//   drawPath(path);


void custom_bus_item::update_path() {
  regist *snd =  dynamic_cast<regist*>(sender());
  snd->display->pos();
}

void custom_bus_item::paint(QPainter* painter,
			    const QStyleOptionGraphicsItem* option,
			    QWidget* widget) {
  painter->setBrush(Qt::green);
  painter->fillPath(this->path(), Qt::green);
  painter->drawPath(this->path());

}
