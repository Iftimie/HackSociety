#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadwebcam.h"

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
    connect(this->threadAnalize,SIGNAL(analizeBinaryResult()),this,SLOT(on_imageWebcamChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_imageWebcamChanged(){
    Mat *resized0 =MainWindow::storeGetImage(nullptr,"EX",0);
    Mat *resized1 =MainWindow::storeGetImage(nullptr,"EX",1);
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
                                 ThreadAnalize::minV,ThreadAnalize::maxV);
}

void MainWindow::on_btnLoadParams_clicked()
{
    this->loadBinarizationParams(ThreadAnalize::minH,ThreadAnalize::maxH,
                                 ThreadAnalize::minS,ThreadAnalize::maxS,
                                 ThreadAnalize::minV,ThreadAnalize::maxV);
    this->ui->sliMinH->setValue(ThreadAnalize::minH);
    this->ui->sliMaxH->setValue(ThreadAnalize::maxH);
    this->ui->sliMinS->setValue(ThreadAnalize::minS);
    this->ui->sliMaxS->setValue(ThreadAnalize::maxS);
    this->ui->sliMinV->setValue(ThreadAnalize::minV);
    this->ui->sliMaxV->setValue(ThreadAnalize::maxV);
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
