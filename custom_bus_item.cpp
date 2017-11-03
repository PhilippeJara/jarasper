#include "custom_bus_item.h"
#include "atoms.h"

custom_bus_item::custom_bus_item(QGraphicsItem* parent):linked_registers(), QObject(), QGraphicsPathItem(parent){
  
  QPainterPath path;
  path.addRect(100, 10, 100, 10);
  this->setFlags(QGraphicsItem::ItemIsSelectable|
		 QGraphicsItem::ItemIsMovable |
		 QGraphicsItem::ItemSendsGeometryChanges);
  this->setPath(path);
}

void custom_bus_item::update_path(mov_cnt<CustomRectItem> *obj) {
  auto path = std::make_unique<QPainterPath> ();
  auto cur = this->path().currentPosition();
  
  if (!this->linked_registers.empty() &&
      this->linked_registers.find(obj) != linked_registers.end()){
    path->addRect(QRectF(obj->x(), cur.y(), cur.x() - obj->x() , 10));
    path->addRect(QRectF(cur.x(), obj->y(), 10 , cur.y() - obj->y()));

    linked_registers[obj] = std::move(path);
  }
}

void custom_bus_item::paint(QPainter* painter,
			    const QStyleOptionGraphicsItem* option,
			    QWidget* widget) {
  QPainterPath path;
  path.addPath(this->path());
  for (auto& arg:linked_registers){
    path.addPath(*(arg.second));
  }
  painter->setBrush(Qt::green);
  painter->drawPath(path);
}

void custom_bus_item::link(mov_cnt<CustomRectItem> * obj) {
  linked_registers.emplace(obj, std::make_unique<QPainterPath>());
  QObject::connect(obj,SIGNAL(pos_change(CustomRectItem*)),
		   this, SLOT(update_path(CustomRectItem*)));
}

void custom_bus_item::remove_link(mov_cnt<CustomRectItem> *obj) {
  linked_registers.erase(obj);
}


