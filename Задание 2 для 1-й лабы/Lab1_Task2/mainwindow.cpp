#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);

    // Создаём все фигуры в разных точках
    shapes.append(new Circle(QPointF(200, 200), 50));
    shapes.append(new Rectangle(QPointF(400, 300), 100, 60));
    shapes.append(new Square(QPointF(600, 400), 80));
    shapes.append(new Rhombus(QPointF(500, 200), 120, 80));
    shapes.append(new Triangle(QPointF(300, 500), 70));
    shapes.append(new Hexagon(QPointF(650, 500), 70));
    shapes.append(new Star5(QPointF(200, 600), 60, 30));
    shapes.append(new Star6(QPointF(400, 600), 60, 30));
    shapes.append(new Star8(QPointF(600, 600), 60, 30));
    shapes.append(new Ellipse(QPointF(800, 500), 80, 40));

    // Добавляем все фигуры на сцену
    for (Shape *shape : shapes) {
        scene->addItem(shape);
    }

    currentShape = shapes[0]; // Текущая фигура — первая (круг)
    currentIndex = 0;

    connect(currentShape, &Shape::positionChanged,
            this, &MainWindow::updateInfo); // Создали фигуру -> изменили бар

    // Настройка comboBox
    ui->shapeComboBox->addItem("Круг");
    ui->shapeComboBox->addItem("Прямоугольник");
    ui->shapeComboBox->addItem("Квадрат");
    ui->shapeComboBox->addItem("Ромб");
    ui->shapeComboBox->addItem("Треугольник");
    ui->shapeComboBox->addItem("Шестиугольник");
    ui->shapeComboBox->addItem("Звезда 5");
    ui->shapeComboBox->addItem("Звезда 6");
    ui->shapeComboBox->addItem("Звезда 8");
    ui->shapeComboBox->addItem("Эллипс");
    ui->shapeComboBox->setCurrentIndex(0);

    connect(ui->shapeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onShapeChanged);
    connect(ui->applyPosButton, &QPushButton::clicked,
            this, &MainWindow::onApplyPosition);
    connect(ui->centerButton, &QPushButton::clicked,
            this, &MainWindow::onCenterButton);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setSceneRect(0, 0, 800, 600);

    connect(currentShape, &Shape::positionChanged, this, &MainWindow::updateInfo);

    connect(ui->rotateSlider, &QSlider::valueChanged, this, &MainWindow::onRotateSliderChanged);

    connect(ui->scaleSlider, &QSlider::valueChanged, this, &MainWindow::onScaleSliderChanged);

    connect(ui->paramSlider1, &QSlider::valueChanged, this, &MainWindow::onParamSlider1Changed);
    connect(ui->paramSlider2, &QSlider::valueChanged, this, &MainWindow::onParamSlider2Changed);

    animationTimer = new QTimer(this);
    animationTimer->setInterval(30);  // 30 мс между шагами (~33 кадра/сек)
    connect(animationTimer, &QTimer::timeout, this, &MainWindow::onAnimationStep);
    animationActive = false;

    connect(ui->paramSlider1, &QSlider::valueChanged, this, &MainWindow::onParam1Changed);
    connect(ui->paramSlider2, &QSlider::valueChanged, this, &MainWindow::onParam2Changed);
}

MainWindow::~MainWindow()
{
    // Удаляем все фигуры из списка
    qDeleteAll(shapes);
    shapes.clear();

    delete ui;
}

void MainWindow::onApplyPosition()
{
    if (!currentShape) return;

    bool xOk, yOk;
    qreal x = ui->xCoordEdit->text().toDouble(&xOk);
    qreal y = ui->yCoordEdit->text().toDouble(&yOk);

    if (xOk && yOk) {
        QPointF target(x, y);

        if (ui->animateCheckBox->isChecked()) {
            currentShape->animateMoveTo(target, 500); // за 500 мс
        } else {
            // Мгновенное перемещение
            currentShape->setCenter(target);
        }
    } else {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Пожалуйста, введите числа в поля X и Y");
    }
}

void MainWindow::onAnimationStep()
{
    if (!currentShape || !animationActive) {
        animationTimer->stop();
        return;
    }

    animationStep++;

    if (animationStep >= totalSteps) {
        // Достигли цели
        currentShape->setCenter(targetPos);
        animationTimer->stop();
        animationActive = false;
        return;
    }

    // Линейная интерполяция
    qreal t = (qreal)animationStep / totalSteps;
    QPointF currentPos = startPos + (targetPos - startPos) * t;

    currentShape->setCenter(currentPos);
}

void MainWindow::onCenterButton()
{
    if (!currentShape) return;

    QPointF target(400, 300);

    if (ui->animateCheckBox->isChecked()) {
        currentShape->animateMoveTo(target, 500);
    } else {
        currentShape->setCenter(target);
    }

    ui->xCoordEdit->setText("400");
    ui->yCoordEdit->setText("300");
}

void MainWindow::onShapeChanged(int index)
{
    if (index < 0 || index >= shapes.size()) return;

    // Отключаем сигнал от старой фигуры
    if (currentShape) {
        disconnect(currentShape, &Shape::positionChanged,
                   this, &MainWindow::updateInfo);
    }

    currentShape = shapes[index];
    currentIndex = index;

    // Подключаем сигнал от новой фигуры
    connect(currentShape, &Shape::positionChanged,
            this, &MainWindow::updateInfo);

    // Обновляем поворот
    int angle = currentShape->rotation();
    ui->rotateSlider->setValue(angle);
    ui->angleLabel->setText("Поворот: " + QString::number(angle) + "°");

    // Обновляем масштаб
    qreal scale = currentShape->scale();
    int scalePercent = qRound(scale * 100);
    ui->scaleSlider->setValue(scalePercent);
    ui->scaleLabel->setText(QString::number(scalePercent) + "%");

    // Обновляем координаты
    QPointF center = currentShape->center();
    ui->xCoordEdit->setText(QString::number(center.x()));
    ui->yCoordEdit->setText(QString::number(center.y()));

    if (Circle *circle = dynamic_cast<Circle*>(currentShape)) {
        ui->paramName1Label->setText("Радиус:");
        ui->paramName2Label->setVisible(false);
        ui->paramSlider1->setVisible(true);
        ui->paramSlider2->setVisible(false);
        ui->paramValue1Label->setVisible(true);
        ui->paramValue2Label->setVisible(false);

        ui->paramSlider1->setMinimum(1);
        ui->paramSlider1->setMaximum(500);
        ui->paramSlider1->setValue(circle->radius());
        ui->paramValue1Label->setText(QString::number(circle->radius()));
    }
    else if (Rectangle *rect = dynamic_cast<Rectangle*>(currentShape)) {
        ui->paramName1Label->setText("Ширина:");
        ui->paramName2Label->setText("Высота:");
        ui->paramSlider1->setVisible(true);
        ui->paramSlider2->setVisible(true);
        ui->paramValue1Label->setVisible(true);
        ui->paramValue2Label->setVisible(true);

        ui->paramSlider1->setMinimum(1);
        ui->paramSlider1->setMaximum(500);
        ui->paramSlider2->setMinimum(1);
        ui->paramSlider2->setMaximum(500);

        ui->paramSlider1->setValue(rect->width());
        ui->paramSlider2->setValue(rect->height());
        ui->paramValue1Label->setText(QString::number(rect->width()));
        ui->paramValue2Label->setText(QString::number(rect->height()));
    }
    else if (Square *square = dynamic_cast<Square*>(currentShape)) {
        ui->paramName1Label->setText("Сторона:");
        ui->paramName2Label->setVisible(false);
        ui->paramSlider1->setVisible(true);
        ui->paramSlider2->setVisible(false);
        ui->paramValue1Label->setVisible(true);
        ui->paramValue2Label->setVisible(false);

        ui->paramSlider1->setMinimum(1);
        ui->paramSlider1->setMaximum(500);
        ui->paramSlider1->setValue(square->side());
        ui->paramValue1Label->setText(QString::number(square->side()));
    }
    else if (Rhombus *rhombus = dynamic_cast<Rhombus*>(currentShape)) {
        ui->paramName1Label->setText("Диаг. 1:");
        ui->paramName2Label->setText("Диаг. 2:");
        ui->paramSlider1->setVisible(true);
        ui->paramSlider2->setVisible(true);
        ui->paramValue1Label->setVisible(true);
        ui->paramValue2Label->setVisible(true);

        ui->paramSlider1->setMinimum(1);
        ui->paramSlider1->setMaximum(500);
        ui->paramSlider2->setMinimum(1);
        ui->paramSlider2->setMaximum(500);

        ui->paramSlider1->setValue(rhombus->diagonal1());
        ui->paramSlider2->setValue(rhombus->diagonal2());
        ui->paramValue1Label->setText(QString::number(rhombus->diagonal1()));
        ui->paramValue2Label->setText(QString::number(rhombus->diagonal2()));
    }
    else if (Triangle *triangle = dynamic_cast<Triangle*>(currentShape)) {
        ui->paramName1Label->setText("Радиус:");
        ui->paramName2Label->setVisible(false);
        ui->paramSlider1->setVisible(true);
        ui->paramSlider2->setVisible(false);
        ui->paramValue1Label->setVisible(true);
        ui->paramValue2Label->setVisible(false);

        ui->paramSlider1->setMinimum(1);
        ui->paramSlider1->setMaximum(500);
        ui->paramSlider1->setValue(triangle->radius());
        ui->paramValue1Label->setText(QString::number(triangle->radius()));
    }
    else if (Hexagon *hexagon = dynamic_cast<Hexagon*>(currentShape)) {
        ui->paramName1Label->setText("Радиус:");
        ui->paramName2Label->setVisible(false);
        ui->paramSlider1->setVisible(true);
        ui->paramSlider2->setVisible(false);
        ui->paramValue1Label->setVisible(true);
        ui->paramValue2Label->setVisible(false);

        ui->paramSlider1->setMinimum(1);
        ui->paramSlider1->setMaximum(500);
        ui->paramSlider1->setValue(hexagon->radius());
        ui->paramValue1Label->setText(QString::number(hexagon->radius()));
    }
    else if (dynamic_cast<Star5*>(currentShape) ||
             dynamic_cast<Star6*>(currentShape) ||
             dynamic_cast<Star8*>(currentShape)) {

        Star *star = dynamic_cast<Star*>(currentShape); // Получаем указатель на базовый класс Star
        if (star) {
            ui->paramName1Label->setText("Внеш. R:");
            ui->paramName2Label->setText("Внутр. R:");
            ui->paramSlider1->setVisible(true);
            ui->paramSlider2->setVisible(true);
            ui->paramValue1Label->setVisible(true);
            ui->paramValue2Label->setVisible(true);

            ui->paramSlider1->setMinimum(1);
            ui->paramSlider1->setMaximum(500);
            ui->paramSlider2->setMinimum(1);
            ui->paramSlider2->setMaximum(500);

            ui->paramSlider1->setValue(star->outerRadius());
            ui->paramSlider2->setValue(star->innerRadius());
            ui->paramValue1Label->setText(QString::number(star->outerRadius()));
            ui->paramValue2Label->setText(QString::number(star->innerRadius()));
        }
    }
    else if (Ellipse *ellipse = dynamic_cast<Ellipse*>(currentShape)) {
        ui->paramName1Label->setText("Rx:");
        ui->paramName2Label->setText("Ry:");
        ui->paramSlider1->setVisible(true);
        ui->paramSlider2->setVisible(true);
        ui->paramValue1Label->setVisible(true);
        ui->paramValue2Label->setVisible(true);

        ui->paramSlider1->setMinimum(1);
        ui->paramSlider1->setMaximum(500);
        ui->paramSlider2->setMinimum(1);
        ui->paramSlider2->setMaximum(500);

        ui->paramSlider1->setValue(ellipse->rx());
        ui->paramSlider2->setValue(ellipse->ry());
        ui->paramValue1Label->setText(QString::number(ellipse->rx()));
        ui->paramValue2Label->setText(QString::number(ellipse->ry()));
    }

    updateInfo();
}

void MainWindow::updateInfo()
{
    if (!currentShape) {
        ui->areaLabel->setText("Площадь: --");
        ui->perimeterLabel->setText("Периметр: --");
        return;
    }

    QString areaText = QString::number(currentShape->area(), 'f', 2); // Значения с двумя знаками после запятой
    QString perimText = QString::number(currentShape->perimeter(), 'f', 2);

    ui->areaLabel->setText("Площадь: " + areaText);
    ui->perimeterLabel->setText("Периметр: " + perimText);
}

void MainWindow::onRotateSliderChanged(int value)
{
    if (!currentShape) return;

    currentShape->setRotation(value);
    ui->angleLabel->setText("Поворот: " + QString::number(value) + "°");
}

void MainWindow::onScaleSliderChanged(int value)
{
    if (!currentShape) return;

    qreal scaleFactor = value / 100.0;  // 100% → 1.0
    currentShape->setScale(scaleFactor);
    ui->scaleLabel->setText(QString::number(value) + "%");
}

void MainWindow::onParamSlider1Changed(int value)
{
    if (!currentShape) return;

    if (dynamic_cast<Circle*>(currentShape)) {
        Circle *circle = dynamic_cast<Circle*>(currentShape);
        circle->setRadius(value);
    }
    else if (dynamic_cast<Rectangle*>(currentShape)) {
        Rectangle *rect = dynamic_cast<Rectangle*>(currentShape);
        rect->setWidth(value);
    }
    else if (dynamic_cast<Square*>(currentShape)) {
        Square *square = dynamic_cast<Square*>(currentShape);
        square->setSide(value);
    }
    else if (dynamic_cast<Rhombus*>(currentShape)) {
        Rhombus *rhombus = dynamic_cast<Rhombus*>(currentShape);
        rhombus->setDiagonal1(value);
    }
    else if (dynamic_cast<Triangle*>(currentShape)) {
        Triangle *triangle = dynamic_cast<Triangle*>(currentShape);
        triangle->setRadius(value);
    }
    else if (dynamic_cast<Hexagon*>(currentShape)) {
        Hexagon *hexagon = dynamic_cast<Hexagon*>(currentShape);
        hexagon->setRadius(value);
    }
    else if (dynamic_cast<Star*>(currentShape)) {
        Star *star = dynamic_cast<Star*>(currentShape);
        star->setOuterRadius(value);
    }
    else if (dynamic_cast<Ellipse*>(currentShape)) {
        Ellipse *ellipse = dynamic_cast<Ellipse*>(currentShape);
        ellipse->setRx(value);
    }

    ui->paramValue1Label->setText(QString::number(value));

    updateInfo(); // Параметры могли измениться
}

void MainWindow::onParamSlider2Changed(int value)
{
    if (!currentShape) return;

    if (dynamic_cast<Rectangle*>(currentShape)) {
        Rectangle *rect = dynamic_cast<Rectangle*>(currentShape);
        rect->setHeight(value);
    }
    else if (dynamic_cast<Rhombus*>(currentShape)) {
        Rhombus *rhombus = dynamic_cast<Rhombus*>(currentShape);
        rhombus->setDiagonal2(value);
    }
    else if (dynamic_cast<Star*>(currentShape)) {
        Star *star = dynamic_cast<Star*>(currentShape);
        star->setInnerRadius(value);
    }
    else if (dynamic_cast<Ellipse*>(currentShape)) {
        Ellipse *ellipse = dynamic_cast<Ellipse*>(currentShape);
        ellipse->setRy(value);
    }

    ui->paramValue2Label->setText(QString::number(value));

    updateInfo(); // Параметры могли измениться
}

void MainWindow::setupParamSliders()
{
    if (!currentShape) return;

    // По умолчанию показываем оба ползунка
    ui->paramName2Label->setVisible(true);
    ui->paramSlider2->setVisible(true);
    ui->paramValue2Label->setVisible(true);

    if (dynamic_cast<Circle*>(currentShape)) {
        ui->paramName1Label->setText("Радиус:");
        ui->paramName2Label->setVisible(false);
        ui->paramSlider2->setVisible(false);
        ui->paramValue2Label->setVisible(false);

        Circle *circle = dynamic_cast<Circle*>(currentShape);
        ui->paramSlider1->setValue(circle->radius());
        ui->paramValue1Label->setText(QString::number(circle->radius()));
    }
    else if (dynamic_cast<Rectangle*>(currentShape)) {
        ui->paramName1Label->setText("Ширина:");
        ui->paramName2Label->setText("Высота:");

        Rectangle *rect = dynamic_cast<Rectangle*>(currentShape);
        ui->paramSlider1->setValue(rect->width());
        ui->paramSlider2->setValue(rect->height());
        ui->paramValue1Label->setText(QString::number(rect->width()));
        ui->paramValue2Label->setText(QString::number(rect->height()));
    }
    else if (dynamic_cast<Square*>(currentShape)) {
        ui->paramName1Label->setText("Сторона:");
        ui->paramName2Label->setVisible(false);
        ui->paramSlider2->setVisible(false);
        ui->paramValue2Label->setVisible(false);

        Square *square = dynamic_cast<Square*>(currentShape);
        ui->paramSlider1->setValue(square->side());
        ui->paramValue1Label->setText(QString::number(square->side()));
    }
    else if (dynamic_cast<Rhombus*>(currentShape)) {
        ui->paramName1Label->setText("Диагональ 1:");
        ui->paramName2Label->setText("Диагональ 2:");

        Rhombus *rhombus = dynamic_cast<Rhombus*>(currentShape);
        ui->paramSlider1->setValue(rhombus->diagonal1());
        ui->paramSlider2->setValue(rhombus->diagonal2());
        ui->paramValue1Label->setText(QString::number(rhombus->diagonal1()));
        ui->paramValue2Label->setText(QString::number(rhombus->diagonal2()));
    }
    else if (dynamic_cast<Triangle*>(currentShape)) {
        ui->paramName1Label->setText("Радиус:");
        ui->paramName2Label->setVisible(false);
        ui->paramSlider2->setVisible(false);
        ui->paramValue2Label->setVisible(false);

        Triangle *triangle = dynamic_cast<Triangle*>(currentShape);
        ui->paramSlider1->setValue(triangle->radius());
        ui->paramValue1Label->setText(QString::number(triangle->radius()));
    }
    else if (dynamic_cast<Hexagon*>(currentShape)) {
        ui->paramName1Label->setText("Радиус:");
        ui->paramName2Label->setVisible(false);
        ui->paramSlider2->setVisible(false);
        ui->paramValue2Label->setVisible(false);

        Hexagon *hexagon = dynamic_cast<Hexagon*>(currentShape);
        ui->paramSlider1->setValue(hexagon->radius());
        ui->paramValue1Label->setText(QString::number(hexagon->radius()));
    }
    else if (dynamic_cast<Star*>(currentShape)) {
        ui->paramName1Label->setText("Внешний R:");
        ui->paramName2Label->setText("Внутренний R:");

        Star *star = dynamic_cast<Star*>(currentShape);
        ui->paramSlider1->setValue(star->outerRadius());
        ui->paramSlider2->setValue(star->innerRadius());
        ui->paramValue1Label->setText(QString::number(star->outerRadius()));
        ui->paramValue2Label->setText(QString::number(star->innerRadius()));
    }
    else if (dynamic_cast<Ellipse*>(currentShape)) {
        ui->paramName1Label->setText("Rx:");
        ui->paramName2Label->setText("Ry:");

        Ellipse *ellipse = dynamic_cast<Ellipse*>(currentShape);
        ui->paramSlider1->setValue(ellipse->rx());
        ui->paramSlider2->setValue(ellipse->ry());
        ui->paramValue1Label->setText(QString::number(ellipse->rx()));
        ui->paramValue2Label->setText(QString::number(ellipse->ry()));
    }
}

void MainWindow::onParam1Changed(int value)
{
    if (!currentShape) return;

    ui->paramValue1Label->setText(QString::number(value));

    if (Circle *circle = dynamic_cast<Circle*>(currentShape)) {
        circle->setRadius(value);
    }
    else if (Rectangle *rect = dynamic_cast<Rectangle*>(currentShape)) {
        rect->setWidth(value);
    }
    else if (Square *square = dynamic_cast<Square*>(currentShape)) {
        square->setSide(value);
    }
    else if (Rhombus *rhombus = dynamic_cast<Rhombus*>(currentShape)) {
        rhombus->setDiagonal1(value);
    }
    else if (Triangle *triangle = dynamic_cast<Triangle*>(currentShape)) {
        triangle->setRadius(value);
    }
    else if (Hexagon *hexagon = dynamic_cast<Hexagon*>(currentShape)) {
        hexagon->setRadius(value);
    }
    else if (Star5 *star5 = dynamic_cast<Star5*>(currentShape)) {
        star5->setOuterRadius(value);
    }
    else if (Star6 *star6 = dynamic_cast<Star6*>(currentShape)) {
        star6->setOuterRadius(value);
    }
    else if (Star8 *star8 = dynamic_cast<Star8*>(currentShape)) {
        star8->setOuterRadius(value);
    }
    else if (Ellipse *ellipse = dynamic_cast<Ellipse*>(currentShape)) {
        ellipse->setRx(value);
    }
}

void MainWindow::onParam2Changed(int value)
{
    if (!currentShape) return;

    ui->paramValue2Label->setText(QString::number(value));

    if (Rectangle *rect = dynamic_cast<Rectangle*>(currentShape)) {
        rect->setHeight(value);
    }
    else if (Rhombus *rhombus = dynamic_cast<Rhombus*>(currentShape)) {
        rhombus->setDiagonal2(value);
    }
    else if (Star5 *star5 = dynamic_cast<Star5*>(currentShape)) {
        star5->setInnerRadius(value);
    }
    else if (Star6 *star6 = dynamic_cast<Star6*>(currentShape)) {
        star6->setInnerRadius(value);
    }
    else if (Star8 *star8 = dynamic_cast<Star8*>(currentShape)) {
        star8->setInnerRadius(value);
    }
    else if (Ellipse *ellipse = dynamic_cast<Ellipse*>(currentShape)) {
        ellipse->setRy(value);
    }
    // Для фигур с одним параметром — второй слайдер скрыт
    else {
        ui->paramValue2Label->setVisible(false);
    }
}
