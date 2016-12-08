#include "threadwebcam.h"
#include "mainwindow.h"
#include <opencv2/highgui/highgui.hpp>

bool ThreadWebCam::running=true;

ThreadWebCam::ThreadWebCam(QObject *parent):QThread(parent){

}

void ThreadWebCam::run(){

    VideoCapture webcam0(0);
    VideoCapture webcam1(1);
    QThread::msleep(1000);
    Mat image0;
    Mat image1;
    while(ThreadWebCam::running){
        webcam0>>image0;
        webcam1>>image1;
        MainWindow::storeGetImage(&image0,"EN",0);
        MainWindow::storeGetImage(&image1,"EN",1);
        emit imageWebCamChanged();
        QThread::msleep(30);
    }
}

