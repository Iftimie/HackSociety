#include "MyLabel.h"
#include <qlabel.h>
#include <QMouseEvent>
#include <QTransform>
#include <QLabel>
#include <QPainter>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "mainwindow.h"
#include <math.h>
#include <opencv2/imgproc/imgproc.hpp>

Mat MyLabel::img;
MyLabel::MyLabel(QWidget *parent) : QLabel(parent) {
	setMouseTracking(true);
    //update();
    this->img = Mat(300, 300, CV_8U);
    this->img = cv::Scalar(255);
    cv::cvtColor(img,img,COLOR_GRAY2BGR);


}

void MyLabel::mouseMoveEvent(QMouseEvent *ev) {
    if(this->startPainting==true){
        QTransform t;
        t.scale(1, -1);
        t.translate(0, -height() + 1);
        QPoint pos = (*ev).pos() * t;
        int y = 300-pos.y();
        circle(img, Point2f(pos.x(),y), 3, cv::Scalar(0, 0, 0), -1, 8);
        QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
        int w = this->width();
        int h = this->height();
        this->setPixmap(QPixmap::fromImage(imdisplay).scaled(w,h,Qt::KeepAspectRatio));
    }

}

void MyLabel::mouseReleaseEvent(QMouseEvent *e){
    this->startPainting=false;

}
void MyLabel::mousePressEvent(QMouseEvent *e)
{
    this->startPainting=true;
}
