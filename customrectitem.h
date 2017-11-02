#ifndef CUSTOMRECTITEM_H
#define CUSTOMRECTITEM_H
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsRectItem>
#include "scene.h"
#include "math.h"
#include "QtGui/QTextDocument"

class CustomRectItem : public QObject , public QGraphicsRectItem
{
     
Q_OBJECT
public:
  QGraphicsSimpleTextItem info;
  CustomRectItem(QGraphicsItem* parent = 0);
  CustomRectItem(const QRect& rect, QGraphicsItem* parent = 0);
  void setText(QString);

signals:
  void pos_change(QPointF);
  
protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value);
};

#endif // CUSTOMRECTITEM_H
