#ifndef SHAPE_H
#define SHAPE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>
#include <QObject>

class Shape : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    explicit Shape(QPointF center = QPointF(0,0));
    virtual ~Shape();
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual QPointF center() const;
    virtual void setCenter(const QPointF &newCenter);
    virtual void move(const QPointF &delta);
    virtual void rotate(qreal angle);
    virtual qreal getScale() const;
    virtual QRectF boundingRect() const override = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override = 0;
    void animateMoveTo(const QPointF &target, int duration = 500);

protected:
    QPointF m_center;

signals:
    void positionChanged();
};

#endif
