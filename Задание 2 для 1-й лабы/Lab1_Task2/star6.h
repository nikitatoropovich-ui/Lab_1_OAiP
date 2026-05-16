#ifndef STAR6_H
#define STAR6_H

#include "star.h"

class Star6 : public Star
{
public:
    explicit Star6(const QPointF &center, qreal outerRadius, qreal innerRadius);

    double area() const override;
    double perimeter() const override;
};

#endif
