#include "rectangle.h"

Rectangle::Rectangle(const QPointF &center, qreal width, qreal height)
    : Shape(center)
    , m_width(width)
    , m_height(height)
{
}

Rectangle::~Rectangle()
{
}

double Rectangle::area() const // S = ab
{
    return m_width * m_height;
}

double Rectangle::perimeter() const // P = 2(a+b)
{
    return 2 * (m_width + m_height);
}

qreal Rectangle::width() const
{
    return m_width;
}

qreal Rectangle::height() const
{
    return m_height;
}

void Rectangle::setWidth(qreal width)
{
    prepareGeometryChange();
    m_width = width;
    update();
}

void Rectangle::setHeight(qreal height)
{
    prepareGeometryChange();
    m_height = height;
    update();
}

QRectF Rectangle::boundingRect() const
{
    // Прямоугольник с центром в (0,0) простирается от -width/2 до +width/2
    // и от -height/2 до +height/2
    return QRectF(-m_width/2, -m_height/2, m_width, m_height);
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::red);
    painter->drawRect(QRectF(-m_width/2, -m_height/2, m_width, m_height));
}
