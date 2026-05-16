#include "star6.h"
#include <QtMath>

Star6::Star6(const QPointF &center, qreal outerRadius, qreal innerRadius)
    : Star(center, outerRadius, innerRadius, 6)  // 5 лучей
{
}

double Star6::area() const
{
    double angle = M_PI / 6;  // 30°
    return 6 * m_outerRadius * m_innerRadius * sin(angle);
}

double Star6::perimeter() const
{
    return 0;
}
