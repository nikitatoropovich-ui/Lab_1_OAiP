#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include <QtMath>

class Circle : public Shape
{
public:
    explicit Circle(const QPointF &center, qreal radius);
    ~Circle() override;
    double area() const override;
    double perimeter() const override;
    qreal radius() const;
    void setRadius(qreal radius);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    qreal m_radius;
};

#endif
