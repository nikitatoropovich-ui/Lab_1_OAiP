#include "circle.h"
#include <QtMath>

Circle::Circle(const QPointF &center, qreal radius)
    : Shape(center)
    , m_radius(radius)
{
}

Circle::~Circle()
{
}

double Circle::area() const // πR²
{
    return M_PI * m_radius * m_radius;
}

double Circle::perimeter() const // 2πR
{
    return 2 * M_PI * m_radius;
}

qreal Circle::radius() const
{
    return m_radius;
}

void Circle::setRadius(qreal radius)
{
    prepareGeometryChange();
    m_radius = radius;
    update();
}

QRectF Circle::boundingRect() const
{
    return QRectF(-m_radius, -m_radius, m_radius * 2, m_radius * 2);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::blue);
    painter->drawEllipse(QPointF(0,0), m_radius, m_radius);
}
