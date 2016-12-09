/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <MyLabel.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *top;
    QLabel *side;
    QSlider *sliMinH;
    QSlider *sliMaxH;
    QSlider *sliMinS;
    QSlider *sliMaxS;
    QSlider *sliMinV;
    QSlider *sliMaxV;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *btnSaveParams;
    QPushButton *btnLoadParams;
    QLabel *resultTop;
    QLabel *resultSide;
    QSlider *horizontalSlider;
    QLabel *label_7;
    QPushButton *startRecord;
    MyLabel *lblTrain;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QSpinBox *spinBox;
    QPushButton *saveAndNext;
    QPushButton *pushButton;
    QPushButton *btnTrain;
    QDoubleSpinBox *doubleSpinBox;
    QSlider *horizontalSlider_2;
    QLabel *label_8;
    QPushButton *btnWhite;
    QSlider *horizontalSlider_3;
    QLabel *label_9;
    QLabel *lblUserShape;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1059, 544);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        top = new QLabel(centralWidget);
        top->setObjectName(QStringLiteral("top"));
        top->setGeometry(QRect(20, 10, 221, 141));
        top->setFrameShape(QFrame::Box);
        side = new QLabel(centralWidget);
        side->setObjectName(QStringLiteral("side"));
        side->setGeometry(QRect(280, 10, 231, 141));
        side->setFrameShape(QFrame::Box);
        sliMinH = new QSlider(centralWidget);
        sliMinH->setObjectName(QStringLiteral("sliMinH"));
        sliMinH->setGeometry(QRect(20, 160, 160, 22));
        sliMinH->setMaximum(255);
        sliMinH->setOrientation(Qt::Horizontal);
        sliMaxH = new QSlider(centralWidget);
        sliMaxH->setObjectName(QStringLiteral("sliMaxH"));
        sliMaxH->setGeometry(QRect(20, 190, 160, 22));
        sliMaxH->setMaximum(255);
        sliMaxH->setOrientation(Qt::Horizontal);
        sliMinS = new QSlider(centralWidget);
        sliMinS->setObjectName(QStringLiteral("sliMinS"));
        sliMinS->setGeometry(QRect(20, 220, 160, 22));
        sliMinS->setMaximum(255);
        sliMinS->setOrientation(Qt::Horizontal);
        sliMaxS = new QSlider(centralWidget);
        sliMaxS->setObjectName(QStringLiteral("sliMaxS"));
        sliMaxS->setGeometry(QRect(20, 250, 160, 22));
        sliMaxS->setMaximum(255);
        sliMaxS->setOrientation(Qt::Horizontal);
        sliMinV = new QSlider(centralWidget);
        sliMinV->setObjectName(QStringLiteral("sliMinV"));
        sliMinV->setGeometry(QRect(20, 280, 160, 22));
        sliMinV->setMaximum(255);
        sliMinV->setOrientation(Qt::Horizontal);
        sliMaxV = new QSlider(centralWidget);
        sliMaxV->setObjectName(QStringLiteral("sliMaxV"));
        sliMaxV->setGeometry(QRect(20, 310, 160, 22));
        sliMaxV->setMaximum(255);
        sliMaxV->setOrientation(Qt::Horizontal);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(190, 160, 51, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(190, 190, 41, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(190, 220, 47, 13));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(190, 250, 47, 13));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(190, 280, 47, 13));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(190, 310, 47, 13));
        btnSaveParams = new QPushButton(centralWidget);
        btnSaveParams->setObjectName(QStringLiteral("btnSaveParams"));
        btnSaveParams->setGeometry(QRect(240, 170, 75, 23));
        btnLoadParams = new QPushButton(centralWidget);
        btnLoadParams->setObjectName(QStringLiteral("btnLoadParams"));
        btnLoadParams->setGeometry(QRect(240, 200, 75, 23));
        resultTop = new QLabel(centralWidget);
        resultTop->setObjectName(QStringLiteral("resultTop"));
        resultTop->setGeometry(QRect(350, 170, 161, 91));
        resultTop->setFrameShape(QFrame::Box);
        resultSide = new QLabel(centralWidget);
        resultSide->setObjectName(QStringLiteral("resultSide"));
        resultSide->setGeometry(QRect(350, 270, 161, 91));
        resultSide->setFrameShape(QFrame::Box);
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(20, 340, 160, 22));
        horizontalSlider->setMaximum(5);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(190, 340, 41, 16));
        startRecord = new QPushButton(centralWidget);
        startRecord->setObjectName(QStringLiteral("startRecord"));
        startRecord->setGeometry(QRect(10, 430, 75, 23));
        lblTrain = new MyLabel(centralWidget);
        lblTrain->setObjectName(QStringLiteral("lblTrain"));
        lblTrain->setGeometry(QRect(650, 20, 301, 301));
        lblTrain->setFrameShape(QFrame::Box);
        radioButton = new QRadioButton(centralWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(530, 30, 82, 17));
        radioButton->setChecked(true);
        radioButton_2 = new QRadioButton(centralWidget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(530, 60, 82, 17));
        radioButton_3 = new QRadioButton(centralWidget);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(530, 90, 82, 17));
        radioButton_4 = new QRadioButton(centralWidget);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(530, 120, 82, 17));
        radioButton_5 = new QRadioButton(centralWidget);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(530, 150, 82, 17));
        radioButton_6 = new QRadioButton(centralWidget);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setGeometry(QRect(530, 180, 82, 17));
        radioButton_7 = new QRadioButton(centralWidget);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));
        radioButton_7->setGeometry(QRect(530, 210, 82, 17));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(530, 240, 61, 22));
        spinBox->setMaximum(10000);
        saveAndNext = new QPushButton(centralWidget);
        saveAndNext->setObjectName(QStringLiteral("saveAndNext"));
        saveAndNext->setGeometry(QRect(650, 340, 91, 23));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(650, 370, 91, 23));
        btnTrain = new QPushButton(centralWidget);
        btnTrain->setObjectName(QStringLiteral("btnTrain"));
        btnTrain->setGeometry(QRect(650, 400, 91, 23));
        doubleSpinBox = new QDoubleSpinBox(centralWidget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(750, 400, 91, 22));
        doubleSpinBox->setDecimals(5);
        doubleSpinBox->setSingleStep(0.01);
        doubleSpinBox->setValue(0.15);
        horizontalSlider_2 = new QSlider(centralWidget);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(20, 370, 160, 22));
        horizontalSlider_2->setMinimum(3);
        horizontalSlider_2->setSingleStep(2);
        horizontalSlider_2->setValue(11);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(190, 370, 47, 13));
        btnWhite = new QPushButton(centralWidget);
        btnWhite->setObjectName(QStringLiteral("btnWhite"));
        btnWhite->setGeometry(QRect(790, 340, 75, 23));
        horizontalSlider_3 = new QSlider(centralWidget);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(20, 400, 160, 22));
        horizontalSlider_3->setMaximum(640);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(190, 400, 47, 13));
        lblUserShape = new QLabel(centralWidget);
        lblUserShape->setObjectName(QStringLiteral("lblUserShape"));
        lblUserShape->setGeometry(QRect(350, 370, 161, 101));
        lblUserShape->setFrameShape(QFrame::Box);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1059, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        top->setText(QString());
        side->setText(QString());
        label->setText(QApplication::translate("MainWindow", "HMin", 0));
        label_2->setText(QApplication::translate("MainWindow", "HMax", 0));
        label_3->setText(QApplication::translate("MainWindow", "SMin", 0));
        label_4->setText(QApplication::translate("MainWindow", "SMax", 0));
        label_5->setText(QApplication::translate("MainWindow", "VMin", 0));
        label_6->setText(QApplication::translate("MainWindow", "VMax", 0));
        btnSaveParams->setText(QApplication::translate("MainWindow", "Save Params", 0));
        btnLoadParams->setText(QApplication::translate("MainWindow", "Load Params", 0));
        resultTop->setText(QString());
        resultSide->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "Erosin", 0));
        startRecord->setText(QApplication::translate("MainWindow", "Start Record", 0));
        lblTrain->setText(QString());
        radioButton->setText(QApplication::translate("MainWindow", "Up Arrow", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", "Down Arrow", 0));
        radioButton_3->setText(QApplication::translate("MainWindow", "Left Arrow", 0));
        radioButton_4->setText(QApplication::translate("MainWindow", "Right Arrow", 0));
        radioButton_5->setText(QApplication::translate("MainWindow", "Square", 0));
        radioButton_6->setText(QApplication::translate("MainWindow", "Circle", 0));
        radioButton_7->setText(QApplication::translate("MainWindow", "Diamond", 0));
        saveAndNext->setText(QApplication::translate("MainWindow", "Save andNext", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Overwrite def", 0));
        btnTrain->setText(QApplication::translate("MainWindow", "Train", 0));
        label_8->setText(QApplication::translate("MainWindow", "Blur", 0));
        btnWhite->setText(QApplication::translate("MainWindow", "White", 0));
        label_9->setText(QApplication::translate("MainWindow", "Touch", 0));
        lblUserShape->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
