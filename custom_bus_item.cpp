#include "custom_bus_item.h"
#include "atoms.h"

custom_bus_item::custom_bus_item(QGraphicsItem* parent):linked_registers(), QObject(), QGraphicsPathItem(parent), base_bus(0,0,100,5){
  base_bus.setBrush(Qt::red);
  scene_info::scene->addItem(&base_bus);
  base_bus.setZValue(100);
  QPainterPath path;
  path.addRect(0, 0, 100, 5);
  base_bus.setFlags(QGraphicsItem::ItemIsSelectable|
		    QGraphicsItem::ItemIsMovable |
		    QGraphicsItem::ItemSendsGeometryChanges);
  this->setFlags(QGraphicsItem::ItemSendsGeometryChanges);
  this->setPath(path);
  base_bus.update();
}

void custom_bus_item::update_path(CustomRectItem *obj) {
  auto path = std::make_unique<QPainterPath> ();
  auto cur = [&](){return base_bus.pos();};
  // std::cout << "OBJx: "<<obj->x() << "   OBJy: " << obj->y() << std::endl
  // 	    << "CURx: "<< cur().x() << "   CURy: "<< cur().x() << std::endl
  // 	    << "RESx: " << fabs(cur().x() - obj->x())
  // 	    << "   RESy:" << fabs(cur().y() - obj->y())<<std::endl;

  
  if (!this->linked_registers.empty() &&
      this->linked_registers.find(obj) != linked_registers.end()){
    path->addRect(QRectF(cur().x(),cur().y(), (obj->x() - cur().x() ) , 5));
    path->addRect(QRectF(obj->x(), cur().y(), 5, (obj->y() - cur().y() )));
    linked_registers[obj] = std::move(path);
    update();
  }
    
}

  

void custom_bus_item::paint(QPainter* painter,
			    const QStyleOptionGraphicsItem* option,
			    QWidget* widget) {
  auto update_all_paths_if_base_changed = [&](){
					    if (base_bus.ItemPositionHasChanged){
					      for (auto& arg:linked_registers){
						update_path(arg.first);}}};
  update_all_paths_if_base_changed();
  
  QPainterPath path;
  for (auto& arg:linked_registers){
    path = path.united(*(arg.second));
  }
    
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


