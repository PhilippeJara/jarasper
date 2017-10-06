#ifndef CUSTOMRECTITEM_H
#define CUSTOMRECTITEM_H

#include <QGraphicsRectItem>
#include "scene.h"
#include "math.h"
#include "qt5/QtGui/QTextDocument"

class CustomRectItem : public QObject , public QGraphicsRectItem
{
   
  
Q_OBJECT
public:
  QGraphicsSimpleTextItem info;
  CustomRectItem(const QRect& rect, QGraphicsItem* parent = 0);
protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value);
};

#endif // CUSTOMRECTITEM_H
