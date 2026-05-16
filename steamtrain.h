#ifndef STEAMTRAIN_H
#define STEAMTRAIN_H

#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <QDebug>

struct SmokePuff {
    qreal x, y;
    qreal size;
    qreal opacity;
    bool alive;
};

class SteamTrain : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit SteamTrain(qreal x, qreal y, qreal width, qreal height);
    ~SteamTrain();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void moveTo(qreal newX, qreal newY);
    void emitSmoke();
    void updateSmoke();

private:
    qreal m_x, m_y;           // позиция
    qreal m_width, m_height;  // размер корпуса

    QVector<SmokePuff> smokePuffs;
    QTimer *smokeTimer;
    QTimer *autoSmokeTimer;

    qreal wheelAngle;      // текущий угол поворота колёс (в градусах)
    bool isMoving;         // движется ли паровоз сейчас
};

#endif
