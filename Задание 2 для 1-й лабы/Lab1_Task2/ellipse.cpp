#include "ellipse.h"
#include <QPainter>
#include <QtMath>

Ellipse::Ellipse(const QPointF &center, qreal rx, qreal ry)
    : Shape(center)
    , m_rx(rx)
    , m_ry(ry)
{
}

Ellipse::~Ellipse() {}

double Ellipse::area() const // Площадь эллипса = π * a * b
{
    return M_PI * m_rx * m_ry;
}

double Ellipse::perimeter() const // Приближённая формула Рамануджана
{
    qreal a = m_rx;
    qreal b = m_ry;
    return M_PI * (3 * (a + b) - qSqrt((3*a + b) * (a + 3*b))); // π * [3(a+b) - √((3a+b)(a+3b))]
}

qreal Ellipse::rx() const { return m_rx; }
qreal Ellipse::ry() const { return m_ry; }

void Ellipse::setRx(qreal rx)
{
    prepareGeometryChange();
    m_rx = rx;
    update();
}

void Ellipse::setRy(qreal ry)
{
    prepareGeometryChange();
    m_ry = ry;
    update();
}

QRectF Ellipse::boundingRect() const
{
    return QRectF(-m_rx, -m_ry, 2 * m_rx, 2 * m_ry);
}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::cyan);  // бирюзовый
    painter->drawEllipse(QPointF(0, 0), m_rx, m_ry);
}
