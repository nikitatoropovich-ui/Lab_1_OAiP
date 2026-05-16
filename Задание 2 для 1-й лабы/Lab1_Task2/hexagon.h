#ifndef HEXAGON_H
#define HEXAGON_H

#include "shape.h"
#include <QtMath>

class Hexagon : public Shape
{
public:
    explicit Hexagon(const QPointF &center, qreal radius);
    ~Hexagon() override;

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
