#include "rhombus.h"
#include <QPainter>
#include <QtMath>

Rhombus::Rhombus(const QPointF &center, qreal diagonal1, qreal diagonal2)
    : Shape(center)
    , m_d1(diagonal1)
    , m_d2(diagonal2)
{
}

Rhombus::~Rhombus()
{
}

double Rhombus::area() const
{
    return (m_d1 * m_d2) / 2.0;
}

double Rhombus::perimeter() const
{
    return 2 * qSqrt(m_d1 * m_d1 + m_d2 * m_d2);
}

qreal Rhombus::diagonal1() const
{
    return m_d1;
}

qreal Rhombus::diagonal2() const
{
    return m_d2;
}

void Rhombus::setDiagonal1(qreal d1)
{
    prepareGeometryChange();
    m_d1 = d1;
    update();
}

void Rhombus::setDiagonal2(qreal d2)
{
    prepareGeometryChange();
    m_d2 = d2;
    update();
}

QRectF Rhombus::boundingRect() const
{
    // Ромб простирается от -d1/2 до +d1/2 по X
    // и от -d2/2 до +d2/2 по Y
    return QRectF(-m_d1/2, -m_d2/2, m_d1, m_d2);
}

void Rhombus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Создаём массив из 4 вершин
    QPolygonF polygon;
    polygon << QPointF(-m_d1/2, 0)    // левая
            << QPointF(0, -m_d2/2)    // верхняя
            << QPointF(m_d1/2, 0)     // правая
            << QPointF(0, m_d2/2);    // нижняя

    painter->setBrush(Qt::magenta);  // яркий цвет, чтобы отличать
    painter->drawPolygon(polygon);
}
