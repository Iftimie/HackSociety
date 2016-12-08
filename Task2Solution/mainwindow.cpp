#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadwebcam.h"

Mat MainWindow::image0;
Mat MainWindow::image1;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->threadWebcam = new ThreadWebCam(this);
    connect(this->threadWebcam,SIGNAL(imageWebCamChanged()),this,SLOT(on_imageWebcamChanged()));
    this->threadWebcam->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_imageWebcamChanged(){
    cv::Mat *resized0 =MainWindow::storeGetImage(nullptr,"EX",0);
    cv::Mat *resized1 =MainWindow::storeGetImage(nullptr,"EX",1);
    QImage imdisplay0((uchar*)resized0->data, resized0->cols, resized0->rows, resized0->step, QImage::Format_RGB888); //Converts the CV image into Qt standard format
    QImage imdisplay1((uchar*)resized1->data, resized1->cols, resized1->rows, resized1->step, QImage::Format_RGB888);
    int w = this->ui->top->width();
    int h = this->ui->top->height();
    this->ui->top->setPixmap(QPixmap::fromImage(imdisplay0).scaled(w,h,Qt::KeepAspectRatio));
    delete resized0;
    w = this->ui->top->width();
    h = this->ui->top->height();
    this->ui->side->setPixmap(QPixmap::fromImage(imdisplay1).scaled(w,h,Qt::KeepAspectRatio));
    delete resized1;
}

void MainWindow::saveBinarizationParams(int hmin, int hmax, int smin, int smax, int vmin, int vmax)
{
    FILE *f = fopen("bin_params.txt","s");
        if(!f){
            printf("error opening bin_params.txt for writting");
        }else {
           fprintf(f,"%d \n",hmin);fprintf(f,"%d \n",hmax);
           fprintf(f,"%d \n",smin);fprintf(f,"%d \n",smax);
           fprintf(f,"%d \n",vmin);fprintf(f,"%d \n",vmax);
           fclose(f);
        }
}

void MainWindow::loadBinarizationParams(int& hmin, int& hmax, int& smin, int& smax, int& vmin, int& vmax)
{
    FILE *f = fopen("bin_params.txt", "r");
        if(!f)
        {
            printf("error opening bin_params for reading");
        } else
        {
            fscanf(f,"%d \n",hmin);fscanf(f,"%d \n",hmax);
            fscanf(f,"%d \n",smin);fscanf(f,"%d \n",smax);
            fscanf(f,"%d \n",vmin);fscanf(f,"%d \n",vmax);

            // to do UI actualization
            fclose(f);
        }
}

cv::Mat* MainWindow::storeGetImage(cv::Mat *img, char* action,int slot){
    QMutex mutex;
    mutex.lock();
    if(slot==0){
        if (strcmp(action, "EN") == 0){
            img->copyTo(MainWindow::image0);
            mutex.unlock();
        }
        else if (strcmp(action, "EX") == 0){
            cv::Mat* newImg = new cv::Mat();
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
            cv::Mat* newImg = new cv::Mat();
            MainWindow::image1.copyTo(*newImg);
            mutex.unlock();
            return newImg;
        }
    }

    return 0;
}
