#include "shape.h"
#include <QPropertyAnimation>
#include <QAbstractAnimation>

Shape::Shape(QPointF center)
    : m_center(center)
{
    setPos(m_center);
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

Shape::~Shape() {}

QPointF Shape::center() const { return m_center; }

void Shape::setCenter(const QPointF &newCenter)
{
    m_center = newCenter;
    setPos(m_center);
    emit positionChanged();
    update();
}

void Shape::move(const QPointF &delta)
{
    setCenter(m_center + delta);
}

void Shape::rotate(qreal angle)
{
    setRotation(angle);  // встроенный метод QGraphicsItem
}

qreal Shape::getScale() const
{
    return QGraphicsItem::scale();
}

void Shape::animateMoveTo(const QPointF &target, int duration)
{
    // Создаём анимацию для свойства "pos"
    QPropertyAnimation *anim = new QPropertyAnimation(this, "pos");
    anim->setDuration(duration);
    anim->setStartValue(pos());
    anim->setEndValue(target);

    // При каждом изменении позиции обновляем m_center
    connect(anim, &QPropertyAnimation::valueChanged, this, [this](const QVariant &value) {
        m_center = value.toPointF();
        emit positionChanged();
    });

    // По окончании обновляем ещё раз для надёжности
    connect(anim, &QPropertyAnimation::finished, this, [this]() {
        m_center = pos();
        emit positionChanged();
    });

    // Автоматически удалить анимацию после завершения
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}
