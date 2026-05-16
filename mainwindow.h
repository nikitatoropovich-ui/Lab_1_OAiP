#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "steamtrain.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startMoveLeft();
    void startMoveRight();
    void startMoveUp();
    void startMoveDown();
    void stopMove();
    void moveStep();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    SteamTrain *train;

    QTimer *moveTimer;
    int moveDirection;       // 1-влево, 2-вправо, 3-вверх, 4-вниз
};

#endif
