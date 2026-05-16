#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QVector>
#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include "square.h"
#include "rhombus.h"
#include "triangle.h"
#include "hexagon.h"
#include "star5.h"
#include "star6.h"
#include "star8.h"
#include "ellipse.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onApplyPosition();
    void onCenterButton();
    void onShapeChanged(int index);
    void updateInfo();
    void onRotateSliderChanged(int value);
    void onScaleSliderChanged(int value);

    void onParam1Changed(int value);
    void onParam2Changed(int value);
    void onParamSlider1Changed(int value);
    void onParamSlider2Changed(int value);

    void onAnimationStep();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QVector<Shape*> shapes;   // список всех фигур
    Shape *currentShape;      // текущая выбранная фигура
    int currentIndex;         // индекс текущей фигуры

    void setupParamSliders();

    QTimer *animationTimer;
    QPointF startPos;
    QPointF targetPos;
    int animationStep;
    int totalSteps;
    bool animationActive;
};

#endif
