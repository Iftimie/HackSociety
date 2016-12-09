#include "threadtrainer.h"
#include <QtCore>
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "mainwindow.h"
#include <string.h>
#include <armadillo>
#include <stdio.h>
using namespace cv;

bool ThreadTrainer::running=true;

ThreadTrainer::ThreadTrainer(QObject *parent) : QThread(parent){


}

void ThreadTrainer::run(){
    vector<arma::Mat<double>> training_data;
    MainWindow::loadDetectionData(training_data);
    qDebug("Loaded images");
    MainWindow::net->SGD(training_data,10, 10, 0.03, 5,true,true,false,false);
    MainWindow::saveStandardNeuralNet(*MainWindow::net);
    emit FinishedTrainingNeural();

}


