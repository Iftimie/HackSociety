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
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QRadioButton *radioButton_4;
    QSlider *horizontalSlider;
    QPushButton *pushButton;
    QSlider *horizontalSlider_2;
    QRadioButton *radioButton_7;
    QLabel *label_2;
    QPushButton *btnLoadParams;
    QSpinBox *spinBox;
    QRadioButton *radioButton;
    QLabel *label_8;
    QLabel *side;
    QLabel *label_9;
    QRadioButton *radioButton_5;
    QSlider *sliMaxH;
    QSlider *sliMinH;
    QRadioButton *radioButton_2;
    QSlider *horizontalSlider_3;
    QPushButton *btnTrain;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *lblUserShape;
    QLabel *label_5;
    QLabel *resultSide;
    QPushButton *startRecord;
    QSlider *sliMaxV;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label;
    QPushButton *btnWhite;
    QPushButton *btnSaveParams;
    MyLabel *lblTrain;
    QSlider *sliMaxS;
    QSlider *sliMinS;
    QPushButton *saveAndNext;
    QPushButton *loadNetwork;
    QLabel *top;
    QRadioButton *radioButton_6;
    QPushButton *btnStartWebAnalyse;
    QRadioButton *radioButton_3;
    QDoubleSpinBox *doubleSpinBox;
    QSlider *sliMinV;
    QLabel *resultTop;
    QWidget *tab_2;
    QLabel *lblFlowChart;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1088, 668);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 1011, 601));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        radioButton_4 = new QRadioButton(tab);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(520, 120, 82, 17));
        horizontalSlider = new QSlider(tab);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 340, 160, 22));
        horizontalSlider->setMaximum(5);
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(640, 370, 91, 23));
        horizontalSlider_2 = new QSlider(tab);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(10, 370, 160, 22));
        horizontalSlider_2->setMinimum(3);
        horizontalSlider_2->setSingleStep(2);
        horizontalSlider_2->setValue(11);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        radioButton_7 = new QRadioButton(tab);
        radioButton_7->setObjectName(QStringLiteral("radioButton_7"));
        radioButton_7->setGeometry(QRect(520, 210, 82, 17));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(180, 190, 41, 16));
        btnLoadParams = new QPushButton(tab);
        btnLoadParams->setObjectName(QStringLiteral("btnLoadParams"));
        btnLoadParams->setGeometry(QRect(230, 200, 75, 23));
        spinBox = new QSpinBox(tab);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(520, 240, 61, 22));
        spinBox->setMaximum(10000);
        radioButton = new QRadioButton(tab);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(520, 30, 82, 17));
        radioButton->setChecked(true);
        label_8 = new QLabel(tab);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(180, 370, 47, 13));
        side = new QLabel(tab);
        side->setObjectName(QStringLiteral("side"));
        side->setGeometry(QRect(270, 10, 231, 141));
        side->setFrameShape(QFrame::Box);
        label_9 = new QLabel(tab);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(180, 400, 47, 13));
        radioButton_5 = new QRadioButton(tab);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(520, 150, 82, 17));
        sliMaxH = new QSlider(tab);
        sliMaxH->setObjectName(QStringLiteral("sliMaxH"));
        sliMaxH->setGeometry(QRect(10, 190, 160, 22));
        sliMaxH->setMaximum(255);
        sliMaxH->setOrientation(Qt::Horizontal);
        sliMinH = new QSlider(tab);
        sliMinH->setObjectName(QStringLiteral("sliMinH"));
        sliMinH->setGeometry(QRect(10, 160, 160, 22));
        sliMinH->setMaximum(255);
        sliMinH->setOrientation(Qt::Horizontal);
        radioButton_2 = new QRadioButton(tab);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(520, 60, 82, 17));
        horizontalSlider_3 = new QSlider(tab);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(10, 400, 160, 22));
        horizontalSlider_3->setMaximum(640);
        horizontalSlider_3->setValue(20);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        btnTrain = new QPushButton(tab);
        btnTrain->setObjectName(QStringLiteral("btnTrain"));
        btnTrain->setGeometry(QRect(640, 400, 91, 23));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(180, 250, 47, 13));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(180, 220, 47, 13));
        lblUserShape = new QLabel(tab);
        lblUserShape->setObjectName(QStringLiteral("lblUserShape"));
        lblUserShape->setGeometry(QRect(340, 370, 161, 101));
        lblUserShape->setFrameShape(QFrame::Box);
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(180, 280, 47, 13));
        resultSide = new QLabel(tab);
        resultSide->setObjectName(QStringLiteral("resultSide"));
        resultSide->setGeometry(QRect(340, 270, 161, 91));
        resultSide->setFrameShape(QFrame::Box);
        startRecord = new QPushButton(tab);
        startRecord->setObjectName(QStringLiteral("startRecord"));
        startRecord->setGeometry(QRect(0, 430, 75, 23));
        sliMaxV = new QSlider(tab);
        sliMaxV->setObjectName(QStringLiteral("sliMaxV"));
        sliMaxV->setGeometry(QRect(10, 310, 160, 22));
        sliMaxV->setMaximum(255);
        sliMaxV->setOrientation(Qt::Horizontal);
        label_7 = new QLabel(tab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(180, 340, 41, 16));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(180, 310, 47, 13));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 160, 51, 21));
        btnWhite = new QPushButton(tab);
        btnWhite->setObjectName(QStringLiteral("btnWhite"));
        btnWhite->setGeometry(QRect(780, 340, 75, 23));
        btnSaveParams = new QPushButton(tab);
        btnSaveParams->setObjectName(QStringLiteral("btnSaveParams"));
        btnSaveParams->setGeometry(QRect(230, 170, 75, 23));
        lblTrain = new MyLabel(tab);
        lblTrain->setObjectName(QStringLiteral("lblTrain"));
        lblTrain->setGeometry(QRect(640, 20, 301, 301));
        lblTrain->setFrameShape(QFrame::Box);
        sliMaxS = new QSlider(tab);
        sliMaxS->setObjectName(QStringLiteral("sliMaxS"));
        sliMaxS->setGeometry(QRect(10, 250, 160, 22));
        sliMaxS->setMaximum(255);
        sliMaxS->setOrientation(Qt::Horizontal);
        sliMinS = new QSlider(tab);
        sliMinS->setObjectName(QStringLiteral("sliMinS"));
        sliMinS->setGeometry(QRect(10, 220, 160, 22));
        sliMinS->setMaximum(255);
        sliMinS->setOrientation(Qt::Horizontal);
        saveAndNext = new QPushButton(tab);
        saveAndNext->setObjectName(QStringLiteral("saveAndNext"));
        saveAndNext->setGeometry(QRect(640, 340, 91, 23));
        loadNetwork = new QPushButton(tab);
        loadNetwork->setObjectName(QStringLiteral("loadNetwork"));
        loadNetwork->setGeometry(QRect(640, 430, 75, 23));
        top = new QLabel(tab);
        top->setObjectName(QStringLiteral("top"));
        top->setGeometry(QRect(10, 10, 221, 141));
        top->setFrameShape(QFrame::Box);
        radioButton_6 = new QRadioButton(tab);
        radioButton_6->setObjectName(QStringLiteral("radioButton_6"));
        radioButton_6->setGeometry(QRect(520, 180, 82, 17));
        btnStartWebAnalyse = new QPushButton(tab);
        btnStartWebAnalyse->setObjectName(QStringLiteral("btnStartWebAnalyse"));
        btnStartWebAnalyse->setGeometry(QRect(110, 440, 75, 23));
        radioButton_3 = new QRadioButton(tab);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(520, 90, 82, 17));
        doubleSpinBox = new QDoubleSpinBox(tab);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(740, 400, 91, 22));
        doubleSpinBox->setDecimals(5);
        doubleSpinBox->setSingleStep(0.01);
        doubleSpinBox->setValue(0.15);
        sliMinV = new QSlider(tab);
        sliMinV->setObjectName(QStringLiteral("sliMinV"));
        sliMinV->setGeometry(QRect(10, 280, 160, 22));
        sliMinV->setMaximum(255);
        sliMinV->setOrientation(Qt::Horizontal);
        resultTop = new QLabel(tab);
        resultTop->setObjectName(QStringLiteral("resultTop"));
        resultTop->setGeometry(QRect(340, 170, 161, 91));
        resultTop->setFrameShape(QFrame::Box);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        lblFlowChart = new QLabel(tab_2);
        lblFlowChart->setObjectName(QStringLiteral("lblFlowChart"));
        lblFlowChart->setGeometry(QRect(10, 10, 550, 550));
        lblFlowChart->setFrameShape(QFrame::Box);
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1088, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        radioButton_4->setText(QApplication::translate("MainWindow", "Right Arrow", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Overwrite def", 0));
        radioButton_7->setText(QApplication::translate("MainWindow", "Diamond", 0));
        label_2->setText(QApplication::translate("MainWindow", "HMax", 0));
        btnLoadParams->setText(QApplication::translate("MainWindow", "Load Params", 0));
        radioButton->setText(QApplication::translate("MainWindow", "Up Arrow", 0));
        label_8->setText(QApplication::translate("MainWindow", "Blur", 0));
        side->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "Touch", 0));
        radioButton_5->setText(QApplication::translate("MainWindow", "Square", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", "Down Arrow", 0));
        btnTrain->setText(QApplication::translate("MainWindow", "Train", 0));
        label_4->setText(QApplication::translate("MainWindow", "SMax", 0));
        label_3->setText(QApplication::translate("MainWindow", "SMin", 0));
        lblUserShape->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "VMin", 0));
        resultSide->setText(QString());
        startRecord->setText(QApplication::translate("MainWindow", "Start Record", 0));
        label_7->setText(QApplication::translate("MainWindow", "Erosin", 0));
        label_6->setText(QApplication::translate("MainWindow", "VMax", 0));
        label->setText(QApplication::translate("MainWindow", "HMin", 0));
        btnWhite->setText(QApplication::translate("MainWindow", "White", 0));
        btnSaveParams->setText(QApplication::translate("MainWindow", "Save Params", 0));
        lblTrain->setText(QString());
        saveAndNext->setText(QApplication::translate("MainWindow", "Save andNext", 0));
        loadNetwork->setText(QApplication::translate("MainWindow", "loadNetwork", 0));
        top->setText(QString());
        radioButton_6->setText(QApplication::translate("MainWindow", "Circle", 0));
        btnStartWebAnalyse->setText(QApplication::translate("MainWindow", "startWebAnalyse", 0));
        radioButton_3->setText(QApplication::translate("MainWindow", "Left Arrow", 0));
        resultTop->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0));
        lblFlowChart->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
