#include "star.h"
#include <QPainter>
#include <QtMath>

Star::Star(const QPointF &center, qreal outerRadius, qreal innerRadius, int points)
    : Shape(center)
    , m_outerRadius(outerRadius)
    , m_innerRadius(innerRadius)
    , m_points(points)
{
}

Star::~Star() {}

qreal Star::outerRadius() const { return m_outerRadius; }
qreal Star::innerRadius() const { return m_innerRadius; }
int Star::points() const { return m_points; }

void Star::setOuterRadius(qreal radius)
{
    prepareGeometryChange();
    m_outerRadius = radius;
    update();
}

void Star::setInnerRadius(qreal radius)
{
    prepareGeometryChange();
    m_innerRadius = radius;
    update();
}

QRectF Star::boundingRect() const
{
    return QRectF(-m_outerRadius, -m_outerRadius,
                  2 * m_outerRadius, 2 * m_outerRadius);
}

void Star::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPolygonF polygon;
    qreal angleStep = M_PI / m_points; // = 360° / (2*m_points)

    for (int i = 0; i < 2 * m_points; i++) {
        qreal radius = (i % 2 == 0) ? m_outerRadius : m_innerRadius;
        qreal angle = i * angleStep;
        qreal x = radius * cos(angle);
        qreal y = radius * sin(angle);
        polygon << QPointF(x, y);
    }

    painter->setBrush(Qt::magenta);
    painter->drawPolygon(polygon);
}

double Star::area() const
{
    // Общая формула для правильной звезды
    double angle = M_PI / m_points;
    return (m_points * m_outerRadius * m_innerRadius * sin(angle));
}
