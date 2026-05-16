/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *leftPanel;
    QVBoxLayout *verticalLayout;
    QComboBox *shapeComboBox;
    QLabel *PositionLabel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *xCoord;
    QLineEdit *xCoordEdit;
    QLabel *yCoord;
    QLineEdit *yCoordEdit;
    QPushButton *applyPosButton;
    QPushButton *centerButton;
    QFrame *frame;
    QLabel *CharacteristicsLabel;
    QLabel *areaLabel;
    QLabel *perimeterLabel;
    QFrame *frame_2;
    QLabel *TurnLabel;
    QLabel *angleLabel;
    QSlider *rotateSlider;
    QFrame *frame_3;
    QLabel *label;
    QLabel *scaleLabel;
    QSlider *scaleSlider;
    QFrame *frame_4;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *paramName1Label;
    QLabel *paramValue1Label;
    QSlider *paramSlider1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *paramName2Label;
    QLabel *paramValue2Label;
    QSlider *paramSlider2;
    QCheckBox *animateCheckBox;
    QSpacerItem *verticalSpacer;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1021, 1069);
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        leftPanel = new QWidget(centralwidget);
        leftPanel->setObjectName(QString::fromUtf8("leftPanel"));
        leftPanel->setMinimumSize(QSize(270, 0));
        leftPanel->setMaximumSize(QSize(270, 16777215));
        verticalLayout = new QVBoxLayout(leftPanel);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        shapeComboBox = new QComboBox(leftPanel);
        shapeComboBox->setObjectName(QString::fromUtf8("shapeComboBox"));

        verticalLayout->addWidget(shapeComboBox);

        PositionLabel = new QLabel(leftPanel);
        PositionLabel->setObjectName(QString::fromUtf8("PositionLabel"));
        QFont font;
        font.setBold(true);
        PositionLabel->setFont(font);

        verticalLayout->addWidget(PositionLabel);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        xCoord = new QLabel(leftPanel);
        xCoord->setObjectName(QString::fromUtf8("xCoord"));

        horizontalLayout_3->addWidget(xCoord);

        xCoordEdit = new QLineEdit(leftPanel);
        xCoordEdit->setObjectName(QString::fromUtf8("xCoordEdit"));

        horizontalLayout_3->addWidget(xCoordEdit);

        yCoord = new QLabel(leftPanel);
        yCoord->setObjectName(QString::fromUtf8("yCoord"));

        horizontalLayout_3->addWidget(yCoord);

        yCoordEdit = new QLineEdit(leftPanel);
        yCoordEdit->setObjectName(QString::fromUtf8("yCoordEdit"));

        horizontalLayout_3->addWidget(yCoordEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        applyPosButton = new QPushButton(leftPanel);
        applyPosButton->setObjectName(QString::fromUtf8("applyPosButton"));

        verticalLayout->addWidget(applyPosButton);

        centerButton = new QPushButton(leftPanel);
        centerButton->setObjectName(QString::fromUtf8("centerButton"));

        verticalLayout->addWidget(centerButton);

        frame = new QFrame(leftPanel);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(frame);

        CharacteristicsLabel = new QLabel(leftPanel);
        CharacteristicsLabel->setObjectName(QString::fromUtf8("CharacteristicsLabel"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setItalic(true);
        CharacteristicsLabel->setFont(font1);

        verticalLayout->addWidget(CharacteristicsLabel);

        areaLabel = new QLabel(leftPanel);
        areaLabel->setObjectName(QString::fromUtf8("areaLabel"));

        verticalLayout->addWidget(areaLabel);

        perimeterLabel = new QLabel(leftPanel);
        perimeterLabel->setObjectName(QString::fromUtf8("perimeterLabel"));

        verticalLayout->addWidget(perimeterLabel);

        frame_2 = new QFrame(leftPanel);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::HLine);
        frame_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(frame_2);

        TurnLabel = new QLabel(leftPanel);
        TurnLabel->setObjectName(QString::fromUtf8("TurnLabel"));
        TurnLabel->setFont(font);

        verticalLayout->addWidget(TurnLabel);

        angleLabel = new QLabel(leftPanel);
        angleLabel->setObjectName(QString::fromUtf8("angleLabel"));

        verticalLayout->addWidget(angleLabel);

        rotateSlider = new QSlider(leftPanel);
        rotateSlider->setObjectName(QString::fromUtf8("rotateSlider"));
        rotateSlider->setMaximum(360);
        rotateSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(rotateSlider);

        frame_3 = new QFrame(leftPanel);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::HLine);
        frame_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(frame_3);

        label = new QLabel(leftPanel);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        verticalLayout->addWidget(label);

        scaleLabel = new QLabel(leftPanel);
        scaleLabel->setObjectName(QString::fromUtf8("scaleLabel"));

        verticalLayout->addWidget(scaleLabel);

        scaleSlider = new QSlider(leftPanel);
        scaleSlider->setObjectName(QString::fromUtf8("scaleSlider"));
        scaleSlider->setMinimum(10);
        scaleSlider->setMaximum(700);
        scaleSlider->setValue(100);
        scaleSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(scaleSlider);

        frame_4 = new QFrame(leftPanel);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::HLine);
        frame_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(frame_4);

        label_2 = new QLabel(leftPanel);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        paramName1Label = new QLabel(leftPanel);
        paramName1Label->setObjectName(QString::fromUtf8("paramName1Label"));

        horizontalLayout_4->addWidget(paramName1Label);

        paramValue1Label = new QLabel(leftPanel);
        paramValue1Label->setObjectName(QString::fromUtf8("paramValue1Label"));
        paramValue1Label->setAlignment(Qt::AlignRight);

        horizontalLayout_4->addWidget(paramValue1Label);


        verticalLayout->addLayout(horizontalLayout_4);

        paramSlider1 = new QSlider(leftPanel);
        paramSlider1->setObjectName(QString::fromUtf8("paramSlider1"));
        paramSlider1->setMinimum(0);
        paramSlider1->setMaximum(700);
        paramSlider1->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(paramSlider1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        paramName2Label = new QLabel(leftPanel);
        paramName2Label->setObjectName(QString::fromUtf8("paramName2Label"));

        horizontalLayout_5->addWidget(paramName2Label);

        paramValue2Label = new QLabel(leftPanel);
        paramValue2Label->setObjectName(QString::fromUtf8("paramValue2Label"));
        paramValue2Label->setAlignment(Qt::AlignRight);

        horizontalLayout_5->addWidget(paramValue2Label);


        verticalLayout->addLayout(horizontalLayout_5);

        paramSlider2 = new QSlider(leftPanel);
        paramSlider2->setObjectName(QString::fromUtf8("paramSlider2"));
        paramSlider2->setMinimum(0);
        paramSlider2->setMaximum(700);
        paramSlider2->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(paramSlider2);

        animateCheckBox = new QCheckBox(leftPanel);
        animateCheckBox->setObjectName(QString::fromUtf8("animateCheckBox"));

        verticalLayout->addWidget(animateCheckBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(leftPanel);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        horizontalLayout->addWidget(graphicsView);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1021, 44));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Lab1_Task2", nullptr));
        PositionLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\267\320\270\321\206\320\270\321\217:", nullptr));
        xCoord->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        yCoord->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        applyPosButton->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        centerButton->setText(QCoreApplication::translate("MainWindow", "\320\222 \321\206\320\265\320\275\321\202\321\200", nullptr));
        CharacteristicsLabel->setText(QCoreApplication::translate("MainWindow", "\320\245\320\260\321\200\320\260\320\272\321\202\320\265\321\200\320\270\321\201\321\202\320\270\320\272\320\270:", nullptr));
        areaLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\276\321\211\320\260\320\264\321\214: --", nullptr));
        perimeterLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\270\320\274\320\265\321\202\321\200: --", nullptr));
        TurnLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\276\321\200\320\276\321\202", nullptr));
        angleLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\276\321\200\320\276\321\202: 0\302\260", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261", nullptr));
        scaleLabel->setText(QCoreApplication::translate("MainWindow", "100%", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", nullptr));
        paramName1Label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200 1:", nullptr));
        paramValue1Label->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        paramName2Label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200 2:", nullptr));
        paramValue2Label->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        animateCheckBox->setText(QCoreApplication::translate("MainWindow", "\320\220\320\275\320\270\320\274\320\260\321\206\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
