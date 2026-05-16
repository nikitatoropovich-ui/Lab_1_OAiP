#include "hexagon.h"
#include <QPainter>
#include <QtMath>

Hexagon::Hexagon(const QPointF &center, qreal radius)
    : Shape(center)
    , m_radius(radius)
{
}

Hexagon::~Hexagon()
{
}

double Hexagon::area() const
{
    // Площадь правильного шестиугольника: (3√3 / 2) * R²
    return (3 * qSqrt(3) / 2) * m_radius * m_radius;
}

double Hexagon::perimeter() const
{
    // Периметр = 6 * R
    return 6 * m_radius;
}

qreal Hexagon::radius() const
{
    return m_radius;
}

void Hexagon::setRadius(qreal radius)
{
    prepareGeometryChange();
    m_radius = radius;
    update();
}

QRectF Hexagon::boundingRect() const
{
    // Шестиугольник простирается от -R до +R по X и Y
    return QRectF(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
}

void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPolygonF polygon;

    for (int i = 0; i < 6; i++) {
        qreal angle = i * 60 * M_PI / 180;  // 0°, 60°, 120°, 180°, 240°, 300°
        qreal x = m_radius * cos(angle);
        qreal y = m_radius * sin(angle);
        polygon << QPointF(x, y);
    }

    painter->setBrush(Qt::yellow);
    painter->drawPolygon(polygon);
}
