#include "customrectitem.h"

CustomRectItem::CustomRectItem(const QRect& rect, QGraphicsItem* parent):
  QObject(), QGraphicsRectItem(rect, parent), info(this)
{
  setFlags(QGraphicsItem::ItemIsSelectable |
	   QGraphicsItem::ItemIsMovable |
	   QGraphicsItem::ItemSendsGeometryChanges);
}
CustomRectItem::CustomRectItem(QGraphicsItem* parent):
  QObject(), QGraphicsRectItem(parent), info(this)
{
  setFlags(QGraphicsItem::ItemIsSelectable |
	   QGraphicsItem::ItemIsMovable |
	   QGraphicsItem::ItemSendsGeometryChanges);
}
void CustomRectItem::setText(const QString string){
  this->info.setText(string);
}
QVariant CustomRectItem::itemChange(GraphicsItemChange change,
				    const QVariant &value)
{
  if (change == ItemPositionChange && scene()) {
    emit pos_change(this);
    QPointF newPos = value.toPointF();
    if(QApplication::mouseButtons() == Qt::LeftButton &&
       qobject_cast<Scene*> (scene())){
      Scene* customScene = qobject_cast<Scene*> (scene());
      int gridSize = customScene->getGridSize();
      qreal xV = round(newPos.x()/gridSize)*gridSize;
      qreal yV = round(newPos.y()/gridSize)*gridSize;
      return QPointF(xV, yV);
    }
    else
      return newPos;
  }
  else
    return QGraphicsItem::itemChange(change, value);
  }


