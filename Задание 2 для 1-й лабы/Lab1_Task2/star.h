#ifndef STAR_H
#define STAR_H

#include "shape.h"

class Star : public Shape
{
public:
    explicit Star(const QPointF &center, qreal outerRadius, qreal innerRadius, int points);
    ~Star() override;

    double area() const override = 0;
    double perimeter() const override = 0;

    qreal outerRadius() const;
    qreal innerRadius() const;
    int points() const;

    void setOuterRadius(qreal radius);
    void setInnerRadius(qreal radius);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    qreal m_outerRadius;
    qreal m_innerRadius;
    int m_points;
};

#endif
