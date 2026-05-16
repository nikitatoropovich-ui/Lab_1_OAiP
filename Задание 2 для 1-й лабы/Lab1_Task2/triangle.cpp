#include "triangle.h"
#include <QPainter>
#include <QtMath>

Triangle::Triangle(const QPointF &center, qreal radius)
    : Shape(center)
    , m_radius(radius)
{
}

Triangle::~Triangle()
{
}

double Triangle::area() const
{
    // Площадь равностороннего треугольника: (3√3 / 4) * R²
    return (3 * qSqrt(3) / 4) * m_radius * m_radius;
}

double Triangle::perimeter() const
{
    // Сторона = R * √3
    qreal side = m_radius * qSqrt(3);
    return 3 * side;
}

qreal Triangle::radius() const
{
    return m_radius;
}

void Triangle::setRadius(qreal radius)
{
    prepareGeometryChange();
    m_radius = radius;
    update();
}

QRectF Triangle::boundingRect() const
{
    // Треугольник простирается от -R до +R по X,
    // и от -R*sin(30) до +R по Y (примерно)
    qreal halfWidth = m_radius * qSqrt(3) / 2;  // половина основания
    qreal topY = -m_radius;                      // верхняя вершина
    qreal bottomY = m_radius * 0.5;              // нижние вершины по Y

    return QRectF(-halfWidth, topY,
                  2 * halfWidth, bottomY - topY);
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Для вычисления вершин
    qreal cos30 = qSqrt(3) / 2;
    qreal sin30 = 0.5;

    QPolygonF polygon;
    polygon << QPointF(0, -m_radius)                         // верх
            << QPointF(m_radius * cos30, m_radius * sin30)   // правая нижняя
            << QPointF(-m_radius * cos30, m_radius * sin30); // левая нижняя

    painter->setBrush(Qt::cyan);  // голубой цвет
    painter->drawPolygon(polygon);
}
