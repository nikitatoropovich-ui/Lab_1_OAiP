#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
public:
    explicit Ellipse(const QPointF &center, qreal rx, qreal ry);
    ~Ellipse() override;

    double area() const override;
    double perimeter() const override;

    qreal rx() const;
    qreal ry() const;
    void setRx(qreal rx);
    void setRy(qreal ry);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    qreal m_rx;  // радиус по X
    qreal m_ry;  // радиус по Y
};

#endif
