#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
    explicit Rectangle(const QPointF &center, qreal width, qreal height);
    ~Rectangle() override;

    double area() const override;
    double perimeter() const override;
    qreal width() const;
    qreal height() const;
    void setWidth(qreal width);
    void setHeight(qreal height);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    qreal m_width;
    qreal m_height;
};

#endif
