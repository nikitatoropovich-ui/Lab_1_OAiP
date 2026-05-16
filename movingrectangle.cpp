#include "movingrectangle.h"

MovingRectangle::MovingRectangle(qreal x, qreal y, qreal width, qreal height)
    : QGraphicsRectItem(x, y, width, height)
{
}

MovingRectangle::~MovingRectangle()
{
}

void MovingRectangle::moveTo(qreal newX, qreal newY)
{
    setRect(newX, newY, rect().width(), rect().height());
}
