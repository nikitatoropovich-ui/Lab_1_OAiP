#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "shape.h"
#include <QtMath>

class Rhombus : public Shape
{
public:
    explicit Rhombus(const QPointF &center, qreal diagonal1, qreal diagonal2);
    ~Rhombus() override;

    double area() const override;
    double perimeter() const override;

    qreal diagonal1() const;
    qreal diagonal2() const;
    void setDiagonal1(qreal d1);
    void setDiagonal2(qreal d2);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    qreal m_d1;  // горизонтальная диагональ
    qreal m_d2;  // вертикальная диагональ
};

#endif
