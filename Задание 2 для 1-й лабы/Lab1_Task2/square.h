#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class Square : public Shape
{
public:
    explicit Square(const QPointF &center, qreal side); // без неявных преобразований
    ~Square() override;

    double area() const override;
    double perimeter() const override;

    qreal side() const;
    void setSide(qreal side);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    qreal m_side;  // длина стороны
};

#endif
