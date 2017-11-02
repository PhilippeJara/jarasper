#include "custom_bus_item.h"
#include "atoms.h"

custom_bus_item::custom_bus_item(QGraphicsItem* parent):QObject(), QGraphicsPathItem(parent){
  QPainterPath path;
  path.addRect(100, 10, 100, 10);
  this->setFlags(QGraphicsItem::ItemIsSelectable|
		 QGraphicsItem::ItemIsMovable |
		 QGraphicsItem::ItemSendsGeometryChanges);
  this->setPath(path);
}

void custom_bus_item::update_path(QPointF pos) {
  QPainterPath path;
  path.addPath(this->path());
  //path.lineTo(pos);
  auto cur = path.currentPosition();
  path.addRect(QRectF(pos.x(), cur.y(), cur.x() - pos.x() , 10));
  path.addRect(QRectF(cur.x(), pos.y(), 10 , cur.y() - pos.y()));
  // pos.x();
    this->setPath(path);
}

void custom_bus_item::paint(QPainter* painter,
			    const QStyleOptionGraphicsItem* option,
			    QWidget* widget) {
  painter->setBrush(Qt::green);
  painter->drawPath(this->path());

}


