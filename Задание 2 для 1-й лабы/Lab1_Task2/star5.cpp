#include "star5.h"
#include <QtMath>

Star5::Star5(const QPointF &center, qreal outerRadius, qreal innerRadius)
    : Star(center, outerRadius, innerRadius, 5)  // 5 лучей
{
}

double Star5::area() const
{
    double angle = M_PI / 5;  // 36°
    return 5 * m_outerRadius * m_innerRadius * sin(angle);
}

double Star5::perimeter() const
{
    return 0;
}
