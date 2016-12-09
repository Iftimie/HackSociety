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

    strcpy(this->outputVector,"1 0 0 0 0 0 0");
    this->indexStart=0;
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
        cv::imshow("reuslt",GetSquareImage(img,100));
        cv::waitKey(30);
    }
}

cv::Mat MainWindow::GetSquareImage( const cv::Mat& img, int target_width)
{
    int width = img.cols,
       height = img.rows;

    //cv::Mat square = cv::Mat::zeros( target_width, target_width, img.type() );
    Mat square(target_width, target_width, CV_8U);
    square = cv::Scalar(255);
    cv::cvtColor(square,square,COLOR_GRAY2BGR);

    int max_dim = ( width >= height ) ? width : height;
    float scale = ( ( float ) target_width ) / max_dim;
    cv::Rect roi;
    if ( width >= height )
    {
        roi.width = target_width;
        roi.x = 0;
        roi.height = height * scale;
        roi.y = ( target_width - roi.height ) / 2;
    }
    else
    {
        roi.y = 0;
        roi.height = target_width;
        roi.width = width * scale;
        roi.x = ( target_width - roi.width ) / 2;
    }

    cv::resize( img, square( roi ), roi.size() );

    return square;
}

void MainWindow::on_radioButton_clicked()
{
    strcpy(this->outputVector,"1 0 0 0 0 0 0");
}

void MainWindow::on_radioButton_2_clicked()
{
    strcpy(this->outputVector,"0 1 0 0 0 0 0");
}

void MainWindow::on_radioButton_3_clicked()
{
    strcpy(this->outputVector,"0 0 1 0 0 0 0");
}

void MainWindow::on_radioButton_4_clicked()
{
    strcpy(this->outputVector,"0 0 0 1 0 0 0");
}

void MainWindow::on_radioButton_5_clicked()
{
    strcpy(this->outputVector,"0 0 0 0 1 0 0");
}

void MainWindow::on_radioButton_6_clicked()
{
    strcpy(this->outputVector,"0 0 0 0 0 1 0");
}

void MainWindow::on_radioButton_7_clicked()
{
    strcpy(this->outputVector,"0 0 0 0 0 0 1");
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    this->indexStart=arg1;
}

void MainWindow::on_saveAndNext_clicked()
{
    Mat copyImage;


    for(double deg = -12;deg<12;deg+=6){
        for(int dx=-15;dx<15;dx+=10){
            for(int dy = -15;dy<15;dy+=10){
                MyLabel::img.copyTo(copyImage);
                copyImage = this->rotate_and_crop(deg,copyImage);
                copyImage = this->translateImg(copyImage,dx,dy);
                char filename[100];
                sprintf(filename,"trainingImages/img%d.jpg",indexStart);
                imwrite(filename,copyImage);

                sprintf(filename,"trainingImages/img%d.jpg %s",indexStart++,this->outputVector);
                appendToFile("trainingImages/def.txt",filename);
            }
        }
    }
    MyLabel::img = Mat(300, 300, CV_8U);
    MyLabel::img = cv::Scalar(255);
    cv::cvtColor(MyLabel::img,MyLabel::img,COLOR_GRAY2BGR);
}

cv::Rect MainWindow::getLargestRect(double imageWidth, double imageHeight, double rotAngDeg, int type){
    Rect rect;
    double rotateAngleDeg = std::fmod(rotAngDeg, 180);
    if (rotateAngleDeg < 0){
        rotateAngleDeg += 360;
        rotateAngleDeg = std::fmod(rotateAngleDeg, 180);;
    }
    double imgWidth = imageWidth;
    double imgHeight = imageHeight;
    if (rotateAngleDeg == 0 || rotateAngleDeg == 180){
        //Angle is 0, no change needed
        rect = Rect(0, 0, (int)imgHeight, (int)imgWidth);
        return rect;
    }
    if (rotateAngleDeg > 90){
        // Angle > 90 therefore angle = 90 - ("+rotateAngleDeg+" - 90) = "+(90 - (rotateAngleDeg - 90))
        rotateAngleDeg = 90 - (rotateAngleDeg - 90);
    }
    double rotateAngle = (rotateAngleDeg*M_PI) / 180.;
    double sinRotAng = sin(rotateAngle);
    double cosRotAng = cos(rotateAngle);
    double tanRotAng = tan(rotateAngle);
    // Point 1 of rotated rectangle
    double x1 = sinRotAng * imgHeight;
    double y1 = 0;
    // Point 2 of rotated rectangle
    double x2 = cosRotAng * imgWidth + x1;
    double y2 = sinRotAng * imgWidth;
    // Point 3 of rotated rectangle
    double x3 = x2 - x1;
    double y3 = y2 + cosRotAng * imgHeight;
    // Point 4 of rotated rectangle
    double x4 = 0;
    double y4 = y3 - y2;
    // MidPoint of rotated image
    double midx = x2 / 2;
    double midy = y3 / 2;

    // Angle for new rectangle (based on image width and height)
    double imgAngle = atan(imgHeight / imgWidth);
    double imgRotAngle = atan(imgWidth / imgHeight);
    double tanImgAng = tan(imgAngle);
    double tanImgRotAng = tan(imgRotAngle);
    // X Point for new rectangle on bottom line
    double ibx1 = midy / tanImgAng + midx;
    double ibx2 = midy * tanImgAng + midx;

    // First intersecting lines
    // y = ax + b  ,  y = cx + d  ==>  x = (d - b) / (a - c)
    double a = y2 / x3;
    double b = tanRotAng * -x1;
    double c = -imgHeight / imgWidth;
    double d = tanImgAng * ibx1;

    // Intersecting point 1
    double ix1 = (d - b) / (a - c);
    double iy1 = a * ix1 + b;

    // Second intersecting lines
    c = -imgWidth / imgHeight;
    d = tanImgRotAng * ibx2;

    // Intersecting point 2
    double ix2 = (d - b) / (a - c);
    double iy2 = a * ix2 + b;

    // Work out smallest rectangle
    double radx1 = abs(midx - ix1);
    double rady1 = abs(midy - iy1);
    double radx2 = abs(midx - ix2);
    double rady2 = abs(midy - iy2);
    // Work out area of rectangles
    double area1 = radx1 * rady1;
    double area2 = radx2 * rady2;

    Rect rect1 = Rect((int)round(midx - radx1), (int)round(midy - rady1), (int)round(radx1 * 2), (int)round(rady1 * 2));
    Rect rect2 = Rect((int)round(midx - radx2), (int)round(midy - rady2), (int)round(radx2 * 2), (int)round(rady2 * 2));
    switch (type) {
    case 0: rect = (area1 > area2 ? rect1 : rect2); break;
    case 1: rect = (area1 < area2 ? rect1 : rect2); break;
    case 2: rect = (radx1 > radx2 ? rect1 : rect2); break;
    case 3: rect = (rady1 > rady2 ? rect1 : rect2); break;
    }

    return rect;
}

cv::Mat MainWindow::rotate_and_crop(double angle,cv::Mat &mat){
    cv::Point2f center(mat.cols / 2.0, mat.rows / 2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::Rect bbox = cv::RotatedRect(center, mat.size(), angle).boundingRect();
    rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
    rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
    cv::Mat dst;
    cv::warpAffine(mat, dst, rot, bbox.size());
    Rect rect = getLargestRect(mat.rows, mat.cols, angle, 0);
    cv::Mat cropped = dst(rect);
    return cropped;
}

void MainWindow::appendToFile(char* fileName, char* textToAppend){
    FILE *file = fopen(fileName, "a");
    if (file == NULL) {
        perror("Error opening file.");
    }
    else {
        fseek(file, 0, SEEK_END);
        fprintf(file, "%s\n", textToAppend);
        fclose(file);
    }
}

void MainWindow::on_pushButton_clicked()
{
    FILE *file = fopen("trainingImages/def.txt", "w");
        if (file == NULL) {
            perror("Error opening file.");
        }
        else {
            fclose(file);
        }
}

Mat MainWindow::translateImg(Mat &img, int offsetx, int offsety){
    Mat trans_mat = (Mat_<double>(2,3) << 1, 0, offsetx, 0, 1, offsety);
    warpAffine(img,img,trans_mat,img.size());
    return trans_mat;
}
