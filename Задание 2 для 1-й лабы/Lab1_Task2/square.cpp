#include "square.h"
#include <QPainter>

Square::Square(const QPointF &center, qreal side)
    : Shape(center)
    , m_side(side)
{
}

Square::~Square() {}

double Square::area() const
{
    return m_side * m_side; // S = a²
}

double Square::perimeter() const
{
    return 4 * m_side; // Р = 4×а
}

qreal Square::side() const
{
    return m_side;
}

void Square::setSide(qreal side)
{
    prepareGeometryChange(); // Сообщаем сцене, что и старая, и новая область требуют перерисовки
    m_side = side;
    update();
}

QRectF Square::boundingRect() const
{
    // Квадрат с центром в (0,0) простирается от -side/2 до +side/2
    qreal half = m_side / 2;
    return QRectF(-half, -half, m_side, m_side);
}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::green);
    qreal half = m_side / 2;
    painter->drawRect(QRectF(-half, -half, m_side, m_side));
}
