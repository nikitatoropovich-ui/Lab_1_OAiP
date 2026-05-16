#include "star8.h"
#include <QtMath>

Star8::Star8(const QPointF &center, qreal outerRadius, qreal innerRadius)
    : Star(center, outerRadius, innerRadius, 8)  // 5 лучей
{
}

double Star8::area() const
{
    double angle = M_PI / 8;  // 22.5°
    return 8 * m_outerRadius * m_innerRadius * sin(angle);
}

double Star8::perimeter() const
{
    return 0;
}
