#include "steamtrain.h"
#include <cmath>

SteamTrain::SteamTrain(qreal x, qreal y, qreal width, qreal height)
    : QGraphicsItem(),
    m_x(x), m_y(y), m_width(width), m_height(height)
{

    setPos(m_x, m_y);  // устанавливаем позицию на сцене
    wheelAngle = 0;
    isMoving = false;

    // Таймер для анимации дыма
    smokeTimer = new QTimer(this);
    connect(smokeTimer, &QTimer::timeout, this, &SteamTrain::updateSmoke);
    smokeTimer->start(100);

    // Таймер для автоматического дыма
    autoSmokeTimer = new QTimer(this);
    connect(autoSmokeTimer, &QTimer::timeout, this, &SteamTrain::emitSmoke);
    autoSmokeTimer->start(2000);

    emitSmoke();  // одно облако сразу
}

SteamTrain::~SteamTrain() {}

QRectF SteamTrain::boundingRect() const
{
    // Расширяем область вверх для дыма
    qreal topPadding = m_height * 2.0;  // запас вверх на 2 высоты паровоза
    qreal sidePadding = 100;            // запас по бокам

    return QRectF(-sidePadding, -topPadding,
                  m_width + sidePadding * 2,
                  m_height + topPadding + 50);
}

void SteamTrain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Рисуем корпус (прямоугольник)
    painter->setBrush(Qt::blue);
    painter->drawRect(0, 0, m_width, m_height);

    // Колёса
    qreal railY = m_height + 10;  // линия рельсов ниже корпуса на 10 пикселей

    // Большое колесо
    qreal bigWheelSize = m_height * 0.6;  // 60% от высоты корпуса
    qreal bigWheelRadius = bigWheelSize / 2;
    qreal bigWheelX = m_width * 0.2;  // чуть левее центра левой трети

    // Два одинаковых малых колеса
    qreal smallWheelSize = bigWheelSize * 2 / 3;  //примерно 40% от высоты корпуса
    qreal smallWheelRadius = smallWheelSize / 2;

    // Равномерно распределяем по ширине
    qreal smallWheel1X = m_width * 0.5;  // центр первого малого
    qreal smallWheel2X = m_width * 0.8;  // центр второго малого

    // Все колёса касаются рельсов своей нижней точкой
    // Значит центр колеса находится на высоте = railY - радиус
    qreal bigWheelCenterY = railY - bigWheelRadius;
    qreal smallWheelCenterY = railY - smallWheelRadius;

    // Рисуем колёса
    painter->setBrush(Qt::white);
    painter->setPen(QPen(Qt::black, 2));

    // Большое колесо
    painter->drawEllipse(QPointF(bigWheelX, bigWheelCenterY),
                         bigWheelRadius, bigWheelRadius);

    // Два малых колеса
    painter->drawEllipse(QPointF(smallWheel1X, smallWheelCenterY),
                         smallWheelRadius, smallWheelRadius);
    painter->drawEllipse(QPointF(smallWheel2X, smallWheelCenterY),
                         smallWheelRadius, smallWheelRadius);

    // Спицы
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black, 2));

    // Большое колесо — 6 спиц с поворотом
    for (int i = 0; i < 6; i++) {
        qreal angle = (i * 60 + wheelAngle) * 3.14159 / 180;
        qreal dx = bigWheelRadius * cos(angle);
        qreal dy = bigWheelRadius * sin(angle);

        painter->drawLine(QPointF(bigWheelX, bigWheelCenterY),
                          QPointF(bigWheelX + dx, bigWheelCenterY + dy));
    }

    // Первое малое колесо
    for (int i = 0; i < 4; i++) {
        qreal angle = (i * 90 + wheelAngle) * 3.14159 / 180;
        qreal dx = smallWheelRadius * cos(angle);
        qreal dy = smallWheelRadius * sin(angle);

        painter->drawLine(QPointF(smallWheel1X, smallWheelCenterY),
                          QPointF(smallWheel1X + dx, smallWheelCenterY + dy));
    }

    // Второе малое колесо
    for (int i = 0; i < 4; i++) {
        qreal angle = (i * 90 + wheelAngle) * 3.14159 / 180;
        qreal dx = smallWheelRadius * cos(angle);
        qreal dy = smallWheelRadius * sin(angle);

        painter->drawLine(QPointF(smallWheel2X, smallWheelCenterY),
                          QPointF(smallWheel2X + dx, smallWheelCenterY + dy));
    }


    // Рисуем трубу
    painter->setBrush(Qt::gray);
    painter->drawRect(m_width * 0.7, -m_height * 0.3, m_width * 0.15, m_height * 0.4);

    // Рисуем дым
    for (const SmokePuff &puff : smokePuffs) {
        if (!puff.alive) continue;
        painter->setOpacity(puff.opacity);
        painter->setBrush(Qt::white);
        painter->drawEllipse(QPointF(puff.x, puff.y), puff.size, puff.size);
    }
    painter->setOpacity(1.0);
}

void SteamTrain::moveTo(qreal newX, qreal newY)
{
    // Вычисляем смещение движения поезда
    qreal dx = newX - x();
    qreal dy = newY - y();

    // Если смещение есть — мы движемся
    if (dx != 0 || dy != 0) {
        isMoving = true;

        // Вращаем колёса (чем больше смещение, тем сильнее поворот)
        qreal distance = sqrt(dx*dx + dy*dy);  // пройденное расстояние
        wheelAngle += distance * 2;  // коэффициент 2 — чувствительность вращения

        // Не даём углу уйти в бесконечность
        if (wheelAngle >= 360) wheelAngle -= 360;
        if (wheelAngle < 0) wheelAngle += 360;
    }

    // Перемещаем сам объект
    setPos(newX, newY);
    m_x = newX;
    m_y = newY;
    update();
}

void SteamTrain::emitSmoke()
{
    SmokePuff puff;
    puff.x = m_width * 0.7 + m_width * 0.15 / 2;  // центр трубы по X
    puff.y = -m_height * 0.3 - 10;                // над трубой
    puff.size = 15;
    puff.opacity = 1.0;
    puff.alive = true;

    smokePuffs.append(puff);
    update();
}

void SteamTrain::updateSmoke()
{
    for (int i = 0; i < smokePuffs.size(); ++i) {
        SmokePuff &puff = smokePuffs[i];
        puff.y -= 2;
        puff.size += 1;
        puff.opacity -= 0.03;
        if (puff.opacity <= 0 || puff.size > 50) {
            puff.alive = false;
        }
    }

    for (int i = smokePuffs.size() - 1; i >= 0; --i) {
        if (!smokePuffs[i].alive) {
            smokePuffs.removeAt(i);
        }
    }

    isMoving = false;  // если таймер вызван, значит время идёт, но движения уже нет

    update();
}
