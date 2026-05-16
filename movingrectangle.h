#ifndef MOVINGRECTANGLE_H
#define MOVINGRECTANGLE_H
#include <QObject>
#include <QGraphicsRectItem>

class MovingRectangle : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit MovingRectangle(qreal x, qreal y, qreal width, qreal height);
    virtual ~MovingRectangle();

   virtual void moveTo(qreal newX, qreal newY);
};

#endif
