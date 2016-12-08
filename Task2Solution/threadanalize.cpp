#include "threadanalize.h"
#include "mainwindow.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

bool ThreadAnalize::running=true;
int ThreadAnalize::minH=0;
int ThreadAnalize::maxH=0;
int ThreadAnalize::minS=0;
int ThreadAnalize::maxS=0;
int ThreadAnalize::minV=0;
int ThreadAnalize::maxV=0;

ThreadAnalize::ThreadAnalize(QObject *parent):QThread(parent){

}

void ThreadAnalize::run(){

    while(running){
        Mat *image0 = MainWindow::storeGetImage(nullptr,"EX",0);
        Mat *image1 = MainWindow::storeGetImage(nullptr,"EX",1);
        Mat hsv0;
        Mat hsv1;
        colorFilter(*image0,hsv0);
        colorFilter(*image1,hsv1);


        emit analizeBinaryResult();

        delete image0;
        delete image1;
        QThread::msleep(33);
    }
}

void ThreadAnalize::colorFilter(Mat &frame,Mat &hsv){
    cv::cvtColor(frame, hsv, COLOR_BGR2HSV);
    cv::inRange(hsv, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), hsv);
    //dilatation(hsv);
}

