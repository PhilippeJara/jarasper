#include "customrectitem.h"

CustomRectItem::CustomRectItem(const QRect& rect, QGraphicsItem* parent):
    QObject(), QGraphicsRectItem(rect, parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges);
}

QVariant CustomRectItem::itemChange(GraphicsItemChange change,
const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
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
