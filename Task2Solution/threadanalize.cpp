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
int ThreadAnalize::erosin=0;
int ThreadAnalize::blur=11;
bool ThreadAnalize::startRecord=false;
vector<Point2f> ThreadAnalize::shapePoints;
char ThreadAnalize::grid[11][11];
int ThreadAnalize::nextPos=1;
int ThreadAnalize::touchPosition=320;

ThreadAnalize::ThreadAnalize(QObject *parent):QThread(parent){

}

void ThreadAnalize::run(){

    QThread::msleep(5000);
    while(running){
        Mat *image0 = MainWindow::storeGetImage(nullptr,"EX",0);
        Mat *image1 = MainWindow::storeGetImage(nullptr,"EX",1);
        Mat hsv0;
        Mat hsv1;
        colorFilter(*image0,hsv0);
        colorFilter(*image1,hsv1);

        Rect bounding_rect1;
        findBiggestBlob(hsv1,bounding_rect1);
        int x1 = bounding_rect1.x+bounding_rect1.width/2;
        int y1  =bounding_rect1.y+bounding_rect1.height/2;
        int width = hsv0.cols;
        int height = hsv0.rows;
        this->nextPosition(x1,y1,width,height);
        if(ThreadAnalize::startRecord==true && x1!=0 &&y1 !=0){
            shapePoints.push_back(Point2f(x1,y1));
            emit displayShape();
        }

        Rect bounding_rect0;
        findBiggestBlob(hsv0,bounding_rect0);
        int x0 = bounding_rect0.x+bounding_rect0.width/2;
        int y0  =bounding_rect0.y+bounding_rect0.height/2;
        this->touch(x0,y0,width,height);

        cv::cvtColor(hsv0,hsv0,COLOR_GRAY2BGR);
        cv::cvtColor(hsv1,hsv1,COLOR_GRAY2BGR);

        circle(hsv1, Point2f(x1,y1), 3, cv::Scalar(0, 255, 0), -1, 8);
        circle(hsv0, Point2f(x0,y0), 3, cv::Scalar(0, 255, 0), -1, 8);

        MainWindow::storeGetProcImage(&hsv0,"EN",0);
        MainWindow::storeGetProcImage(&hsv1,"EN",1);
        emit analizeBinaryResult();

        delete image0;
        delete image1;
        QThread::msleep(33);
    }
}

void ThreadAnalize::colorFilter(Mat &frame,Mat &hsv){
    cv::cvtColor(frame, hsv, COLOR_BGR2HSV);
    cv::inRange(hsv, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), hsv);
    Mat element = getStructuringElement(MORPH_ELLIPSE,
           Size(2 * erosin+ 1, 2 * erosin + 1),
           Point(erosin, erosin));
    cv::erode(hsv, hsv, element);
    //dilatation(hsv);
}

void ThreadAnalize::findBiggestBlob(cv::Mat & matImage,cv::Rect &bounding_rect){
    int largest_area = 0;
    int largest_contour_index = 0;

    vector< vector<cv::Point> > contours; // Vector for storing contour
    vector<cv::Vec4i> hierarchy;

    findContours(matImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE); // Find the contours in the image

    for (int i = 0; i< contours.size(); i++) {// iterate through each contour.
        double a = cv::contourArea(contours[i], false);  //  Find the area of contour
        if (a>largest_area){
            largest_area = a;
            largest_contour_index = i;                //Store the index of largest contour
            bounding_rect=cv::boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
        }
    }
                                    //negative index->all indexes are drawn  //negative thicknes(-1<2) CV_FILLED
    //drawContours(matImage, contours, largest_contour_index, cv::Scalar(100), 2, 8, hierarchy); // Draw the largest contour using previously stored index.
    //rectangle(matImage, bounding_rect, cvScalar(225, 225, 225, 0), 1, 8, 0);
    //rectangle(matImage, bounding_rect, cvScalar(0, 225, 0), 1, 8, 0);
    return;
}

void ThreadAnalize::nextPosition(int x,int y,int width,int height){
    if(y<40 && x>40 && x<width-40){
        nextPos = 0;//top
    }else if(y>height-40 && x>40 && x<width-40){
        nextPos =2 ;//down
    }else if(x<40 && y > 40 && y<height-40){
        nextPos =3 ;//left
    }else if(x>width-40 && y > 40 && y<height-40){
        nextPos =2 ;//down
    }
    qDebug()<<nextPos;
}

 void ThreadAnalize::touch(int x,int y,int width,int height){
    if(x<ThreadAnalize::touchPosition){
        ThreadAnalize::startRecord=true;
    }else{
        ThreadAnalize::startRecord=false;
        emit classify();
    }
 }

