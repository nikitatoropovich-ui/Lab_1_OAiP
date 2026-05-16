#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , moveDirection(0)  // сначала никуда не двигаем
{
    ui->setupUi(this);

    // Создаём сцену
    scene = new QGraphicsScene(this);

    // Создаём паровоз
    train = new SteamTrain(50, 50, 200, 100);
    scene->addItem(train);

    // Устанавливаем сцену в graphicsView
    ui->graphicsView->setScene(scene);

    // Настраиваем отображение
    ui->graphicsView->setRenderHint(QPainter::Antialiasing); //"испарение"
    ui->graphicsView->setSceneRect(0, 0, 800, 600);

    moveTimer = new QTimer(this);
    moveTimer->setInterval(30);  // каждые 30 миллисекунд
    connect(moveTimer, &QTimer::timeout, this, &MainWindow::moveStep);

    connect(ui->leftButton, &QPushButton::pressed, this, &MainWindow::startMoveLeft);
    connect(ui->leftButton, &QPushButton::released, this, &MainWindow::stopMove);

    connect(ui->rightButton, &QPushButton::pressed, this, &MainWindow::startMoveRight);
    connect(ui->rightButton, &QPushButton::released, this, &MainWindow::stopMove);

    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::startMoveUp);
    connect(ui->upButton, &QPushButton::released, this, &MainWindow::stopMove);

    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::startMoveDown);
    connect(ui->downButton, &QPushButton::released, this, &MainWindow::stopMove);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startMoveLeft()
{
    moveDirection = 1;
    moveTimer->start();
}

void MainWindow::startMoveRight()
{
    moveDirection = 2;
    moveTimer->start();
}

void MainWindow::startMoveUp()
{
    moveDirection = 3;
    moveTimer->start();
}

void MainWindow::startMoveDown()
{
    moveDirection = 4;
    moveTimer->start();
}

void MainWindow::stopMove()
{
    moveTimer->stop();
}

void MainWindow::moveStep()
{
    if (!train) return;

    switch(moveDirection) {
    case 1: // влево
        train->moveTo(train->x() - 10, train->y());
        break;
    case 2: // вправо
        train->moveTo(train->x() + 10, train->y());
        break;
    case 3: // вверх
        train->moveTo(train->x(), train->y() - 10);
        break;
    case 4: // вниз
        train->moveTo(train->x(), train->y() + 10);
        break;
    }
}
