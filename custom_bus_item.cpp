#include "custom_bus_item.h"
#include "atoms.h"

custom_bus_item::custom_bus_item(QGraphicsItem* parent):linked_registers(), QObject(), QGraphicsPathItem(parent){
  
  QPainterPath path;
  path.addRect(100, 100, 100, 10);
  this->boundingRect = (QRectF(1000,1000,1000,1000));
  this->setFlags(QGraphicsItem::ItemIsSelectable|
		 QGraphicsItem::ItemIsMovable |
		 QGraphicsItem::ItemSendsGeometryChanges);
  this->setPath(path);
}

void custom_bus_item::update_path(CustomRectItem *obj) {
  auto path = std::make_unique<QPainterPath> ();
  auto cur = [&](){return this->pos();};
  std::cout << "OBJx: "<<obj->x() << "   OBJy: " << obj->y() << std::endl
	    << "CURx: "<< cur().x() << "   CURy: "<< cur().x() << std::endl
	    << "RESx: " << fabs(100 - obj->x())
	    << "   RESy:" << fabs(100 - obj->y())<<std::endl;
    
  if (!this->linked_registers.empty() &&
      this->linked_registers.find(obj) != linked_registers.end()){
    path->addRect(QRectF(100,obj->y(), fabs(100 - obj->x()) , 10));
    path->addRect(QRectF(obj->x(), 100, 10, fabs(100 -obj->y())));
    linked_registers[obj] = std::move(path);
    update();
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
  path = path.simplified();
  
  path.setFillRule(Qt::WindingFill);
  painter->setBrush(Qt::green);
  painter->drawPath(path);
  this->scene()->update();
}

void custom_bus_item::link(CustomRectItem * obj) {
  linked_registers.emplace(obj, std::make_unique<QPainterPath>());
  QObject::connect(obj,SIGNAL(pos_change(CustomRectItem*)),
		   this, SLOT(update_path(CustomRectItem*)));
}

void custom_bus_item::remove_link(CustomRectItem *obj) {
  linked_registers.erase(obj);
}


