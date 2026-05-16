#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"
#include <QtMath>

class Triangle : public Shape
{
public:
    explicit Triangle(const QPointF &center, qreal radius);
    ~Triangle() override;

    double area() const override;
    double perimeter() const override;

    qreal radius() const;
    void setRadius(qreal radius);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    qreal m_radius;  // радиус описанной окружности
};

#endif
