#ifndef STAR8_H
#define STAR8_H

#include "star.h"

class Star8 : public Star
{
public:
    explicit Star8(const QPointF &center, qreal outerRadius, qreal innerRadius);

    double area() const override;
    double perimeter() const override;
};

#endif
