#ifndef STAR5_H
#define STAR5_H

#include "star.h"

class Star5 : public Star
{
public:
    explicit Star5(const QPointF &center, qreal outerRadius, qreal innerRadius);

    double area() const override;
    double perimeter() const override;
};

#endif
