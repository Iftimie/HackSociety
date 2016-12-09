#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadwebcam.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

Mat MainWindow::image0;
Mat MainWindow::image1;
Mat MainWindow::procImage0;
Mat MainWindow::procImage1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->threadWebcam = new ThreadWebCam(this);
    connect(this->threadWebcam,SIGNAL(imageWebCamChanged()),this,SLOT(on_imageWebcamChanged()));
    this->threadWebcam->start();

    this->threadAnalize = new ThreadAnalize(this);
    connect(this->threadAnalize,SIGNAL(analizeBinaryResult()),this,SLOT(on_analizeBinaryResult()));
    this->threadAnalize->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_imageWebcamChanged(){
    Mat *resized0 =MainWindow::storeGetImage(nullptr,"EX",0);
    Mat *resized1 =MainWindow::storeGetImage(nullptr,"EX",1);
    cvtColor(*resized0, *resized0, CV_BGR2RGB);
    cvtColor(*resized1, *resized1, CV_BGR2RGB);
    QImage imdisplay0((uchar*)resized0->data, resized0->cols, resized0->rows, resized0->step, QImage::Format_RGB888); //Converts the CV image into Qt standard format
    QImage imdisplay1((uchar*)resized1->data, resized1->cols, resized1->rows, resized1->step, QImage::Format_RGB888);
    int w = this->ui->top->width();
    int h = this->ui->top->height();
    this->ui->top->setPixmap(QPixmap::fromImage(imdisplay0).scaled(w,h,Qt::KeepAspectRatio));
    delete resized0;
    w = this->ui->side->width();
    h = this->ui->side->height();
    this->ui->side->setPixmap(QPixmap::fromImage(imdisplay1).scaled(w,h,Qt::KeepAspectRatio));
    delete resized1;
}

void MainWindow::on_analizeBinaryResult(){
    Mat *resized0 =MainWindow::storeGetProcImage(nullptr,"EX",0);
    Mat *resized1 =MainWindow::storeGetProcImage(nullptr,"EX",1);
    cvtColor(*resized0, *resized0, CV_BGR2RGB);
    cvtColor(*resized1, *resized1, CV_BGR2RGB);
    QImage imdisplay0((uchar*)resized0->data, resized0->cols, resized0->rows, resized0->step, QImage::Format_RGB888); //Converts the CV image into Qt standard format
    QImage imdisplay1((uchar*)resized1->data, resized1->cols, resized1->rows, resized1->step, QImage::Format_RGB888);
    int w = this->ui->resultTop->width();
    int h = this->ui->resultTop->height();
    this->ui->resultTop->setPixmap(QPixmap::fromImage(imdisplay0).scaled(w,h,Qt::KeepAspectRatio));
    delete resized0;
    w = this->ui->resultSide->width();
    h = this->ui->resultSide->height();
    this->ui->resultSide->setPixmap(QPixmap::fromImage(imdisplay1).scaled(w,h,Qt::KeepAspectRatio));
    delete resized1;
}

void MainWindow::saveBinarizationParams(int hmin, int hmax, int smin, int smax, int vmin, int vmax,int erosin)
{
    FILE *f = fopen("bin_params.txt","w");
        if(!f){
            printf("error opening bin_params.txt for writting");
        }else {
           fprintf(f,"%d \n",hmin);fprintf(f,"%d \n",hmax);
           fprintf(f,"%d \n",smin);fprintf(f,"%d \n",smax);
           fprintf(f,"%d \n",vmin);fprintf(f,"%d \n",vmax);
           fprintf(f,"%d \n",erosin);
           fclose(f);
        }
}

void MainWindow::loadBinarizationParams(int& hmin, int& hmax, int& smin, int& smax, int& vmin, int& vmax,int &erosin)
{
    FILE *f = fopen("bin_params.txt", "r");
        if(!f)
        {
            printf("error opening bin_params for reading");
        } else
        {
            fscanf(f,"%d \n",&hmin);fscanf(f,"%d \n",&hmax);
            fscanf(f,"%d \n",&smin);fscanf(f,"%d \n",&smax);
            fscanf(f,"%d \n",&vmin);fscanf(f,"%d \n",&vmax);
            fscanf(f,"%d \n",&erosin);

            // to do UI actualization
            fclose(f);
        }
}

Mat* MainWindow::storeGetImage(Mat *img, char* action,int slot){
    QMutex mutex;
    mutex.lock();
    if(slot==0){
        if (strcmp(action, "EN") == 0){
            img->copyTo(MainWindow::image0);
            mutex.unlock();
        }
        else if (strcmp(action, "EX") == 0){
            Mat* newImg = new cv::Mat();
            MainWindow::image0.copyTo(*newImg);
            mutex.unlock();
            return newImg;
        }
    }
    if(slot==1){
        if (strcmp(action, "EN") == 0){
            img->copyTo(MainWindow::image1);
            mutex.unlock();
        }
        else if (strcmp(action, "EX") == 0){
            Mat* newImg = new cv::Mat();
            MainWindow::image1.copyTo(*newImg);
            mutex.unlock();
            return newImg;
        }
    }

    return 0;
}

void MainWindow::on_btnSaveParams_clicked()
{
    this->saveBinarizationParams(ThreadAnalize::minH,ThreadAnalize::maxH,
                                 ThreadAnalize::minS,ThreadAnalize::maxS,
                                 ThreadAnalize::minV,ThreadAnalize::maxV,ThreadAnalize::erosin);
}

void MainWindow::on_btnLoadParams_clicked()
{
    this->loadBinarizationParams(ThreadAnalize::minH,ThreadAnalize::maxH,
                                 ThreadAnalize::minS,ThreadAnalize::maxS,
                                 ThreadAnalize::minV,ThreadAnalize::maxV,ThreadAnalize::erosin);
    this->ui->sliMinH->setValue(ThreadAnalize::minH);
    this->ui->sliMaxH->setValue(ThreadAnalize::maxH);
    this->ui->sliMinS->setValue(ThreadAnalize::minS);
    this->ui->sliMaxS->setValue(ThreadAnalize::maxS);
    this->ui->sliMinV->setValue(ThreadAnalize::minV);
    this->ui->sliMaxV->setValue(ThreadAnalize::maxV);
    this->ui->horizontalSlider->setValue(ThreadAnalize::erosin);
}

Mat* MainWindow::storeGetProcImage(Mat *img, char* action, int slot) {
    QMutex mutex;
    mutex.lock();
    if(slot==0){
        if (strcmp(action, "EN") == 0){
            img->copyTo(MainWindow::procImage0);
            mutex.unlock();
        }
        else if (strcmp(action, "EX") == 0){
            Mat* newImg = new Mat();
            MainWindow::procImage0.copyTo(*newImg);
            mutex.unlock();
            return newImg;
        }
    }
    if(slot==1){
        if (strcmp(action, "EN") == 0){
            img->copyTo(MainWindow::procImage1);
            mutex.unlock();
        }
        else if (strcmp(action, "EX") == 0){
           Mat* newImg = new Mat();
            MainWindow::procImage1.copyTo(*newImg);
            mutex.unlock();
            return newImg;
        }
    }

    return 0;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ThreadAnalize::erosin = value;
}

void MainWindow::on_startRecord_clicked()
{
    if(this->ui->startRecord->text()=="Start Record"){
        ThreadAnalize::shapePoints.clear();
        ThreadAnalize::startRecord=true;
        this->ui->startRecord->setText("Stop Record");
    }else{
        ThreadAnalize::startRecord=false;
        this->ui->startRecord->setText("Start Record");
        int minX=99999;
        int minY=99999;
        int maxX=0;
        int maxY=0;
        for(int i=0;i<ThreadAnalize::shapePoints.size();i++){
            if(ThreadAnalize::shapePoints[i].x<minX){
                minX =ThreadAnalize::shapePoints[i].x;
            }
            if(ThreadAnalize::shapePoints[i].x>maxX){
                maxX = ThreadAnalize::shapePoints[i].x;
            }
            if(ThreadAnalize::shapePoints[i].y<minY){
                minY = ThreadAnalize::shapePoints[i].y;
            }
            if(ThreadAnalize::shapePoints[i].y>maxY){
                maxY = ThreadAnalize::shapePoints[i].y;
            }
        }

        int diffX = maxX-minX;
        int diffY = maxY-minY;
        int width = diffX*1.2;
        int height = diffY*1.2;

        int offsetX = (width-diffX)/2;
        int offsetY = (height-diffY)/2;

        for(int i=0;i<ThreadAnalize::shapePoints.size();i++){
            ThreadAnalize::shapePoints[i].x-=minX;
            ThreadAnalize::shapePoints[i].y-=minY;
            ThreadAnalize::shapePoints[i].x+=offsetX;
            ThreadAnalize::shapePoints[i].y+=offsetY;
        }
        Mat img(height, width, CV_8U);
        img = cv::Scalar(255);
        cv::cvtColor(img,img,COLOR_GRAY2BGR);
        circle(img, Point2f(ThreadAnalize::shapePoints[0].x,ThreadAnalize::shapePoints[0].y), 3, cv::Scalar(0, 255, 0), -1, 8);
        for(int i=1;i<ThreadAnalize::shapePoints.size();i++){
            cv::line(img, ThreadAnalize::shapePoints[i-1], ThreadAnalize::shapePoints[i], cv::Scalar(0, 0, 0), 3, 8,0);
        }
        cv::imshow("reuslt",img);
        cv::waitKey(30);
    }
}
