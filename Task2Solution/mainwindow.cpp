#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadwebcam.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QMessageBox>
#include <QtXml>

Mat MainWindow::image0;
Mat MainWindow::image1;
Mat MainWindow::procImage0;
Mat MainWindow::procImage1;
Neural* MainWindow::net = nullptr;
double MainWindow::stopTreshold;

#define numberOfPoints 10

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    strcpy(this->outputVector,"1 0 0 0 0 0 0");
    this->indexStart=0;

    vectorOfShapes[0]= imread("up.jpg", CV_LOAD_IMAGE_COLOR);
    cv::resize(vectorOfShapes[0],vectorOfShapes[0],Size(50,50));
    vectorOfShapes[1]= imread("down.jpg", CV_LOAD_IMAGE_COLOR);
    cv::resize(vectorOfShapes[1],vectorOfShapes[1],Size(50,50));
    vectorOfShapes[2]= imread("left.jpg", CV_LOAD_IMAGE_COLOR);
    cv::resize(vectorOfShapes[2],vectorOfShapes[2],Size(50,50));
    vectorOfShapes[3]= imread("right.jpg", CV_LOAD_IMAGE_COLOR);
    cv::resize(vectorOfShapes[3],vectorOfShapes[3],Size(50,50));
    vectorOfShapes[4]= imread("sqr.jpg", CV_LOAD_IMAGE_COLOR);
    cv::resize(vectorOfShapes[4],vectorOfShapes[4],Size(50,50));
    vectorOfShapes[5]= imread("circ.jpg", CV_LOAD_IMAGE_COLOR);
    cv::resize(vectorOfShapes[5],vectorOfShapes[5],Size(50,50));
    vectorOfShapes[6]= imread("dmd.jpg", CV_LOAD_IMAGE_COLOR);
    cv::resize(vectorOfShapes[6],vectorOfShapes[6],Size(50,50));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_imageWebcamChanged(){
    Mat *resized0 =MainWindow::storeGetImage(nullptr,"EX",0);
    Mat *resized1 =MainWindow::storeGetImage(nullptr,"EX",1);
    //qDebug()<<resized1->cols-40<<" "<<resized1->rows-40;
    cv::rectangle(*resized1,Rect(40,40,resized1->cols-80,resized1->rows-80),Scalar(0,255,0),4,8,0);
    cv::line(*resized0, Point(ThreadAnalize::touchPosition,0), Point(ThreadAnalize::touchPosition,resized0->rows), cv::Scalar(0, 0, 0), 3, 8,0);
    cv::flip(*resized1,*resized1,0);
    cv::flip(*resized1,*resized1,1);
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
    this->ui->labelPosition->setText(QString::asprintf("X = %d, Y = %d", ThreadAnalize::currentPositionX, ThreadAnalize::currentPositionY));

    Mat *resized0 =MainWindow::storeGetProcImage(nullptr,"EX",0);
    Mat *resized1 =MainWindow::storeGetProcImage(nullptr,"EX",1);
    cvtColor(*resized0, *resized0, CV_BGR2RGB);
    cvtColor(*resized1, *resized1, CV_BGR2RGB);
    cv::flip(*resized1,*resized1,0);
    cv::flip(*resized1,*resized1,1);
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
           fprintf(f,"%d \n",erosin);fprintf(f,"%d \n",ThreadAnalize::blur);
           fprintf(f,"%d \n",ThreadAnalize::touchPosition);
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
            fscanf(f,"%d \n",&erosin);fscanf(f,"%d \n",&ThreadAnalize::blur);
            fscanf(f,"%d \n",&ThreadAnalize::touchPosition);

            // to do UI actualization
            this->ui->sliMinH->setValue(hmin);
            this->ui->sliMaxH->setValue(hmax);
            this->ui->sliMinS->setValue(smin);
            this->ui->sliMaxS->setValue(smax);
            this->ui->sliMinV->setValue(vmin);
            this->ui->sliMaxV->setValue(vmax);

            this->ui->horizontalSlider->setValue(erosin);
            this->ui->horizontalSlider_2->setValue(ThreadAnalize::blur);
            this->ui->horizontalSlider_3->setValue(ThreadAnalize::touchPosition);
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
    this->ui->horizontalSlider_2->setValue(ThreadAnalize::blur);
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
        Mat result = fromPointsToMat();
        cv::imshow("reuslt",result);
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


    for(double deg = -12;deg<=12;deg+=6){
        for(int dx=-15;dx<=15;dx+=10){
            for(int dy = -15;dy<=15;dy+=10){
                MyLabel::img.copyTo(copyImage);
                copyImage = this->rotate_and_crop(deg,copyImage);
                copyImage = this->translateImg(copyImage,dx,dy);
                GaussianBlur( copyImage, copyImage, Size( 11, 11 ), 0, 0 );
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
    warpAffine(img,img,trans_mat,img.size(),
               cv::INTER_LINEAR,
               cv::BORDER_CONSTANT,
               cv::Scalar(255, 255, 255));
    return img;
}

void MainWindow::on_btnTrain_clicked()
{
    arma::Mat<int> sizes(1,4);
    sizes(0,0)=900;
    sizes(0,1)=60;
    sizes(0,2)=20;
    sizes(0,3)=7;
    this->net = new Neural(sizes);
    this->threadTrainer = new ThreadTrainer(this);
    connect(this->threadTrainer,SIGNAL(FinishedTrainingNeural()),this,SLOT(on_FinishedTrainingNeural()));
    this->threadTrainer->start();

}

void MainWindow::on_FinishedTrainingNeural(){
    QThread::msleep(1000);
    delete this->threadTrainer;
    this->threadTrainer = nullptr;
    QMessageBox msg;
    msg.setText("Training Complete");
    msg.exec();
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    this->stopTreshold = arg1;
}

void MainWindow::saveStandardNeuralNet(Neural &net){
    for(int i=0;i<net.weights.size();i++){
        char buffer[50];
        sprintf(buffer,"w%d.mat",i);
        net.weights[i].save(buffer);
        sprintf(buffer,"b%d.mat",i);
        net.biases[i].save(buffer);
    }
}

void MainWindow::loadDetectionData(vector<arma::Mat<double>>& training_data){
    FILE* def = fopen("trainingImages/def.txt", "r");
    if (!def){
        qDebug("no def file found!!");
    }
    else{
        int outputSize =7;
        std::vector<double> output;
        int value;

        char path[100];
        fscanf(def,"%s",path);

        for(int j=0;j<outputSize;j++){
            fscanf(def, "%d", &value);
            output.push_back(value);
        }

        int inputSize = 900/*MainWindow::net->sizes(0,0)*/;
        arma::Mat<double> b(inputSize, 1); b.fill(255);
        arma::Mat<double> c(inputSize, 1); c.fill(1);
        while (!feof(def)){
            Mat img;
            img = cv::imread(path);
            cv::resize(img,img,Size(30,30));
            cv::cvtColor(img,img,CV_RGB2GRAY); //when i saved it was CV_GRAY2RGB
            std::vector<double> vec;
            for (int i = 0; i < img.rows; ++i) {
                vec.insert(vec.end(), (uchar*)img.ptr<uchar>(i), (uchar*)img.ptr<uchar>(i)+img.cols);
            }
            arma::Mat<double> image(vec);
            //image = (((image - a) / (b - a)) % (B - A)) + A;
            image = (image+c) / b;
            image.resize(inputSize+outputSize, 1);
            for (int i = 0; i < outputSize; i++){
                image(inputSize + i, 0) = output[i];
            }

            training_data.push_back(image);

            output.clear();

            fscanf(def,"%s",path);
            for(int j=0;j<outputSize;j++){
                fscanf(def, "%d", &value);
                output.push_back(value);
            }
        }
        while(training_data.size()%10 !=0){
            training_data.pop_back();
        }
        fclose(def);
    }
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    if(value%2==0){
        value--;
    }
    ThreadAnalize::blur = value;
}

void MainWindow::on_sliMinH_valueChanged(int value)
{
    ThreadAnalize::minH=value;
}

void MainWindow::on_sliMaxH_valueChanged(int value)
{
    ThreadAnalize::maxH=value;
}

void MainWindow::on_sliMinS_valueChanged(int value)
{
    ThreadAnalize::minS=value;
}

void MainWindow::on_sliMaxS_valueChanged(int value)
{
    ThreadAnalize::maxS=value;
}

void MainWindow::on_sliMinV_valueChanged(int value)
{
    ThreadAnalize::minV=value;
}

void MainWindow::on_sliMaxV_valueChanged(int value)
{
    ThreadAnalize::maxV=value;
}

void MainWindow::on_btnWhite_clicked()
{
    MyLabel::img = Mat(300, 300, CV_8U);
    MyLabel::img = cv::Scalar(255);
    cv::cvtColor(MyLabel::img,MyLabel::img,COLOR_GRAY2BGR);
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    ThreadAnalize::touchPosition = value;
}

void MainWindow::on_classify(){


    if (this->net == nullptr || ThreadAnalize::shapePoints.size() < 2)
        return;
    qDebug()<<"shape size"<<ThreadAnalize::shapePoints.size();
    Mat inputNeural = fromPointsToMat();
    ThreadAnalize::shapePoints.clear();
    qDebug()<<"shape size after clear"<<ThreadAnalize::shapePoints.size();
    int inputSize=900;
    arma::Mat<double> b(inputSize, 1); b.fill(255);
    arma::Mat<double> c(inputSize, 1); c.fill(1);
    cv::resize(inputNeural,inputNeural,Size(30,30));
    cv::cvtColor(inputNeural,inputNeural,CV_RGB2GRAY); //when i saved it was CV_GRAY2RGB
    std::vector<double> vec;
    for (int i = 0; i < inputNeural.rows; ++i) {
        vec.insert(vec.end(), (uchar*)inputNeural.ptr<uchar>(i), (uchar*)inputNeural.ptr<uchar>(i)+inputNeural.cols);
    }
    arma::Mat<double> image(vec);
    image = (image+c) / b;
    arma::Mat<double> output = this->net->feedForward(image);
    int resultClass = output.index_max();
    qDebug()<<"Result class "<<resultClass;
    char result[100];
    findClass(resultClass,result);

    QMessageBox msgBox;
    if(ThreadAnalize::grid[ThreadAnalize::currentPositionX][ThreadAnalize::currentPositionY]==-1){
         msgBox.setText(QString::asprintf("Keep %s?",result));
    }else{
        if(resultClass>=0 &&resultClass<=3){
            msgBox.setText(QString::asprintf("Keep %s?",result));
        }else{
            msgBox.setText(QString::asprintf("Overwrite with %s?",result));
        }
    }
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    int res = msgBox.exec();
    if(res == QMessageBox::Yes){
        if(resultClass==0){
            ThreadAnalize::currentPositionY--;
            if(ThreadAnalize::currentPositionY<0)ThreadAnalize::currentPositionY=0;
            ThreadAnalize::grid[ThreadAnalize::currentPositionX][ThreadAnalize::currentPositionY]=resultClass;
            ThreadAnalize::currentPositionY--;
            if(ThreadAnalize::currentPositionY<0)ThreadAnalize::currentPositionY=0;
        }else if(resultClass ==1){
            ThreadAnalize::currentPositionY++;
            if(ThreadAnalize::currentPositionY > 10)ThreadAnalize::currentPositionY=10;
            ThreadAnalize::grid[ThreadAnalize::currentPositionX][ThreadAnalize::currentPositionY]=resultClass;
            ThreadAnalize::currentPositionY++;
            if(ThreadAnalize::currentPositionY>10)ThreadAnalize::currentPositionY=10;
        }
        else if(resultClass == 2){
                    ThreadAnalize::currentPositionX--;

                    if(ThreadAnalize::currentPositionX<0)
                        ThreadAnalize::currentPositionX=0;
                    ThreadAnalize::grid[ThreadAnalize::currentPositionX][ThreadAnalize::currentPositionY]=resultClass;

                    ThreadAnalize::currentPositionX--;
                    if(ThreadAnalize::currentPositionX<0)
                        ThreadAnalize::currentPositionX=0;
        }
        else if(resultClass == 3){
                    ThreadAnalize::currentPositionX++;
                    if(ThreadAnalize::currentPositionX>10)ThreadAnalize::currentPositionX=10;
                    ThreadAnalize::grid[ThreadAnalize::currentPositionX][ThreadAnalize::currentPositionY]=resultClass;
                    ThreadAnalize::currentPositionX++;
                    if(ThreadAnalize::currentPositionX>10)ThreadAnalize::currentPositionX=10;
        }
        else
            ThreadAnalize::grid[ThreadAnalize::currentPositionX][ThreadAnalize::currentPositionY]=resultClass;

        repaintFlowchart();
    }else{

    }
}

void MainWindow::repaintFlowchart(){
    Mat whiteImage(11*50, 11*50, CV_8U);
    whiteImage= Scalar(255);
    cv::cvtColor(whiteImage,whiteImage,COLOR_GRAY2BGR);

    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            if(ThreadAnalize::grid[i][j]==0){
                this->vectorOfShapes[0].copyTo(whiteImage(Rect(i*50, j*50, 50, 50)));
            }else if(ThreadAnalize::grid[i][j]==1){
                this->vectorOfShapes[1].copyTo(whiteImage(Rect(i*50, j*50, 50, 50)));
            }else if(ThreadAnalize::grid[i][j]==2){
                this->vectorOfShapes[2].copyTo(whiteImage(Rect(i*50, j*50, 50, 50)));
            }else if(ThreadAnalize::grid[i][j]==3){
                this->vectorOfShapes[3].copyTo(whiteImage(Rect(i*50, j*50, 50, 50)));
            }else if(ThreadAnalize::grid[i][j]==4){
                this->vectorOfShapes[4].copyTo(whiteImage(Rect(i*50, j*50, 50, 50)));
            }else if(ThreadAnalize::grid[i][j]==5){
                this->vectorOfShapes[5].copyTo(whiteImage(Rect(i*50, j*50, 50, 50)));
            }else if(ThreadAnalize::grid[i][j]==6){
                this->vectorOfShapes[6].copyTo(whiteImage(Rect(i*50, j*50, 50, 50)));
            }
        }
    }
    cvtColor(whiteImage, whiteImage, CV_BGR2RGB);
    QImage imdisplay0((uchar*)whiteImage.data, whiteImage.cols, whiteImage.rows, whiteImage.step, QImage::Format_RGB888); //Converts the CV image into Qt standard format
    int w = this->ui->lblFlowChart->width();
    int h = this->ui->lblFlowChart->height();
    this->ui->lblFlowChart->setPixmap(QPixmap::fromImage(imdisplay0).scaled(w,h,Qt::KeepAspectRatio));
}

void MainWindow::findClass(int resultClass,char * result){
    if(resultClass==0){
        strcpy(result,"Up arrow");
    }else if(resultClass==1){
        strcpy(result,"Down arrow");
    }else if(resultClass==2){
        strcpy(result,"Left arrow");
    }else if(resultClass==3){
        strcpy(result,"Right arrow");
    }else if(resultClass==4){
        strcpy(result,"Square");
    }else if(resultClass==5){
        strcpy(result,"Circle");
    }else if(resultClass==6){
        strcpy(result,"Diamond");
    }
}

void MainWindow::on_displayShape(){

    if (ThreadAnalize::shapePoints.size() <3)
        return;
    //qDebug("debug");

    Mat image = fromPointsToMat();
    cvtColor(image, image, CV_BGR2RGB);
    QImage imageDisplay((uchar*)image.data, image.cols, image.rows, image.step, QImage::Format_RGB888); //Converts the CV image into Qt standard format
    int w = this->ui->lblUserShape->width();
    int h = this->ui->lblUserShape->height();
    this->ui->lblUserShape->setPixmap(QPixmap::fromImage(imageDisplay).scaled(w,h,Qt::KeepAspectRatio));
}

cv::Mat MainWindow::fromPointsToMat(){
    int minX=99999;
    int minY=99999;
    int maxX=0;
    int maxY=0;

    vector<Point2f> copyVector(ThreadAnalize::shapePoints);

    int shapePointsSize = copyVector.size();
    for(int i=0;i<shapePointsSize;i++){
        if(copyVector[i].x<minX){
            minX =copyVector[i].x;
        }
        if(copyVector[i].x>maxX){
            maxX = copyVector[i].x;
        }
        if(copyVector[i].y<minY){
            minY = copyVector[i].y;
        }
        if(copyVector[i].y>maxY){
            maxY =copyVector[i].y;
        }
    }

    int diffX = maxX-minX;
    int diffY = maxY-minY;
    int width = diffX*1.2;
    int height = diffY*1.2;

    int offsetX = (width-diffX)/2;
    int offsetY = (height-diffY)/2;

    for(int i=0;i<copyVector.size();i++){
        copyVector[i].x-=minX;
        copyVector[i].y-=minY;
        copyVector[i].x+=offsetX;
        copyVector[i].y+=offsetY;
    }
    Mat img(height, width, CV_8U);
    if(height == 0 || width == 0) {
        qDebug()<<"[SEVERE ERROR] h:" << height << " w:" << width;
        Mat imgReturnWhite(100, 100, CV_8U);
        imgReturnWhite = cv::Scalar(255);
        cv::cvtColor(imgReturnWhite,imgReturnWhite,COLOR_GRAY2BGR);
        return imgReturnWhite;
    }
    img = cv::Scalar(255);
    cv::cvtColor(img,img,COLOR_GRAY2BGR);
    circle(img, Point2f(copyVector[0].x,copyVector[0].y), 3, cv::Scalar(0, 0, 0), -1, 8);
    //qDebug()<<"x="<<ThreadAnalize::shapePoints[0].x<<",y="<<ThreadAnalize::shapePoints[0].y;
    for(int i=1/*numberOfPoints*/;i<copyVector.size();i++){
        //qDebug()<<"x="<<ThreadAnalize::shapePoints[i].x<<",y="<<ThreadAnalize::shapePoints[i].y;
        cv::line(img, copyVector[i-1], copyVector[i], cv::Scalar(0, 0, 0), 3, 8,0);
    }
    // QThread::sleep(10);
    GaussianBlur( img, img, Size( ThreadAnalize::blur, ThreadAnalize::blur ), 0, 0 );
    Mat result = GetSquareImage(img,100);
    cv::flip(result,result,1);
    cv::flip(result,result,0);
    return result;
}

void MainWindow::on_btnStartWebAnalyse_clicked()
{
    this->threadWebcam = new ThreadWebCam(this);
    connect(this->threadWebcam,SIGNAL(imageWebCamChanged()),this,SLOT(on_imageWebcamChanged()));
    this->threadWebcam->start();

    this->threadAnalize = new ThreadAnalize(this);
    connect(this->threadAnalize,SIGNAL(analizeBinaryResult()),this,SLOT(on_analizeBinaryResult()));
    connect(this->threadAnalize,SIGNAL(classify()),this,SLOT(on_classify()));
    connect(this->threadAnalize,SIGNAL(displayShape()),this,SLOT(on_displayShape()));
    this->threadAnalize->start();
}

void MainWindow::on_loadNetwork_clicked()
{
    if(this->net!=nullptr)
        delete this->net;
    arma::Mat<int> sizes(1,4);
    sizes(0,0)=900;
    sizes(0,1)=60;
    sizes(0,2)=20;
    sizes(0,3)=7;
    this->net = new Neural(sizes);
    for(int i=0;i<net->weights.size();i++){
        char buffer[50];
        sprintf(buffer,"w%d.mat",i);
        net->weights[i].load(buffer);
        sprintf(buffer,"b%d.mat",i);
        net->biases[i].load(buffer);
    }
}

void MainWindow::on_btn_xml_clicked()
{
    this->holder.clear();

    QFile xmlFile("schema.xgml");
    if(!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug("Error on schema.xgml IO");
        return;
    }

    QDomDocument doc;

//    QDomElement xml = doc.createElement("xml");
//    xml.setAttribute("encoding", "Cp1252");
//    xml.setAttribute("version", "1.0");
//    doc.appendChild(xml);

    QDomElement sections = doc.createElement("section");
    sections.setAttribute("name", "xgml");

        QDomElement creator = doc.createElement("attribute");
        creator.setAttribute("key","Creator");
        creator.setAttribute("type","String");
        creator.appendChild(doc.createTextNode("yFiles"));
        sections.appendChild(creator);

        QDomElement version = doc.createElement("attribute");
        version.setAttribute("key","Version");
        version.setAttribute("type","String");
        version.appendChild(doc.createTextNode("2.14"));
        sections.appendChild(version);

        QDomElement graph = doc.createElement("section");
        graph.setAttribute("name","graph");

            QDomElement hierarchic = doc.createElement("attribute");
            hierarchic.setAttribute("key","hierarchic");
            hierarchic.setAttribute("type","int");
            hierarchic.appendChild(doc.createTextNode("1"));
            graph.appendChild(hierarchic);

            QDomElement label = doc.createElement("attribute");
            label.setAttribute("key","label");
            label.setAttribute("type","String");
            label.appendChild(doc.createTextNode(""));
            graph.appendChild(label);

            QDomElement type = doc.createElement("attribute");
            type.setAttribute("key","directed");
            type.setAttribute("type","int");
            type.appendChild(doc.createTextNode("1"));
            graph.appendChild(type);

            int id = 0;

            for(int i=0; i < 11; i++){
                for(int j=0; j < 11; j++)
                {
                    if(ThreadAnalize::grid[i][j] == 4)
                    {
                        QDomElement square = getShape(i,j,id,"rectangle",doc);
                        graph.appendChild(square);

                        this->holder.push_back(ShapeHolder(i,j,id));
                        id++;
                    }

                    if(ThreadAnalize::grid[i][j] == 5)
                    {
                        QDomElement square = getShape(i,j,id,"ellipse",doc);
                        graph.appendChild(square);

                         this->holder.push_back(ShapeHolder(i,j,id));
                        id++;
                    }

                    if(ThreadAnalize::grid[i][j] == 6)
                    {
                        QDomElement square = getShape(i,j,id,"diamond",doc);
                        graph.appendChild(square);

                        this->holder.push_back(ShapeHolder(i,j,id));
                        id++;
                    }

                }
            }

            for (int i=0;i<11;i++){
                for(int j=0;j<11;j++){
                    printf("%d ",ThreadAnalize::grid[i][j]);
                }
                printf("\n");
            }

            for(int i=0; i < 11; i++){
                for(int j=0; j < 11; j++)
                {

                    if(ThreadAnalize::grid[i][j] == 0)
                    {
                         int sourceId = getIdGivenXY(i,j+1);
                         int targetId = getIdGivenXY(i,j-1);

                        QDomElement line = getLine(sourceId,targetId, doc) ;
                          graph.appendChild(line);
                    }
                    if(ThreadAnalize::grid[i][j] == 1)
                    {
                         int sourceId = getIdGivenXY(i,j-1);
                         int targetId = getIdGivenXY(i,j+1);

                        QDomElement line = getLine(sourceId,targetId, doc) ;
                          graph.appendChild(line);
                    }
                    if(ThreadAnalize::grid[i][j] == 2)
                    {
                         int sourceId = getIdGivenXY(i+1,j);
                         int targetId = getIdGivenXY(i-1,j);

                        QDomElement line = getLine(sourceId,targetId, doc) ;
                          graph.appendChild(line);
                    }
                    if(ThreadAnalize::grid[i][j] == 3)
                    {
                         int sourceId = getIdGivenXY(i-1,j);
                         int targetId = getIdGivenXY(i+1,j);

                        QDomElement line = getLine(sourceId,targetId, doc) ;
                          graph.appendChild(line);
                    }
                }
            }


        sections.appendChild(graph);

    doc.appendChild(sections);


    QTextStream out(&xmlFile);
    out << doc.toString();
}

QDomElement MainWindow::getLine(int sourceId, int targetId, QDomDocument doc) {
    QDomElement line = doc.createElement("section");
    line.setAttribute("name", "edge");

        QDomElement source = doc.createElement("attribute");
        source.setAttribute("key","source");
        source.setAttribute("type","int");
        source.appendChild(doc.createTextNode(QString::asprintf("%d",sourceId)));
        line.appendChild(source);

        QDomElement target = doc.createElement("attribute");
        target.setAttribute("key","target");
        target.setAttribute("type","int");
        target.appendChild(doc.createTextNode(QString::asprintf("%d",targetId)));
        line.appendChild(target);

        QDomElement targetShow = doc.createElement("section");
        targetShow.setAttribute("name", "graphics");
            QDomElement filling = doc.createElement("attribute");
            filling.setAttribute("key","fill");
            filling.setAttribute("type","String");
            filling.appendChild(doc.createTextNode("#000000"));
            targetShow.appendChild(filling);

            QDomElement targetArrow = doc.createElement("attribute");
            targetArrow.setAttribute("key","targetArrow");
            targetArrow.setAttribute("type","String");
            targetArrow.appendChild(doc.createTextNode("standard"));
            targetShow.appendChild(targetArrow);
        line.appendChild(targetShow);

        return line;
}

QDomElement MainWindow::getShape(int i, int j, int id, QString shapeType, QDomDocument doc)
{
    QDomElement square =  doc.createElement("section");
    square.setAttribute("name","node");

    QDomElement info = doc.createElement("attribute");
    info.setAttribute("key","id");
    info.setAttribute("type","int");
    info.appendChild(doc.createTextNode(QString::asprintf("%d", id)));
    square.appendChild(info);

    QDomElement info2 = doc.createElement("attribute");
    info2.setAttribute("key","label");
    info2.setAttribute("label","String");
    info2.appendChild(doc.createTextNode(""));
    square.appendChild(info2);

    QDomElement graphics = doc.createElement("section");
    graphics.setAttribute("name","graphics");

        QDomElement x = doc.createElement("attribute");
        x.setAttribute("key","x");
        x.setAttribute("type","double");
        x.appendChild(doc.createTextNode(QString::asprintf("%d",i * 50)));
        graphics.appendChild(x);

        QDomElement y = doc.createElement("attribute");
        y.setAttribute("key","y");
        y.setAttribute("type","double");
        y.appendChild(doc.createTextNode(QString::asprintf("%d",j * 50)));
        graphics.appendChild(y);

        QDomElement w = doc.createElement("attribute");
        w.setAttribute("key","w");
        w.setAttribute("type","double");
        w.appendChild(doc.createTextNode(QString::asprintf("%d", 50)));
        graphics.appendChild(w);

        QDomElement h = doc.createElement("attribute");
        h.setAttribute("key","h");
        h.setAttribute("type","double");
        h.appendChild(doc.createTextNode(QString::asprintf("%d", 50)));
        graphics.appendChild(h);

        QDomElement formType = doc.createElement("attribute");
        formType.setAttribute("key","type");
        formType.setAttribute("type","String");
        formType.appendChild(doc.createTextNode(shapeType));
        graphics.appendChild(formType);

        QDomElement raisedBorder = doc.createElement("attribute");
        raisedBorder.setAttribute("key","raisedBorder");
        raisedBorder.setAttribute("type","boolean");
        raisedBorder.appendChild(doc.createTextNode("false"));
        graphics.appendChild(raisedBorder);

        QDomElement fill = doc.createElement("attribute");
        fill.setAttribute("key","fill");
        fill.setAttribute("type","String");
        fill.appendChild(doc.createTextNode("#FFCC00"));
        graphics.appendChild(fill);

        QDomElement outline = doc.createElement("attribute");
        outline.setAttribute("key","outline");
        outline.setAttribute("type","String");
        outline.appendChild(doc.createTextNode("#000000"));
        graphics.appendChild(outline);

    square.appendChild(graphics);


    QDomElement LabelGraphics = doc.createElement("section");
    LabelGraphics.setAttribute("name","LabelGraphics");
    square.appendChild(LabelGraphics);

    return square;
}

void MainWindow::on_btn_dummyGrid_clicked()
{
    for(int i=0; i < 11; i++)
        for(int j=0; j < 11; j++)
            ThreadAnalize::grid[i][j] = -1;

    ThreadAnalize::grid[5][5] = 4;
    ThreadAnalize::grid[6][5] = 3;
    ThreadAnalize::grid[7][5] = 6;
    ThreadAnalize::grid[7][6] = 1;
    ThreadAnalize::grid[7][7] = 5;
}

int MainWindow::getIdGivenXY(int x,int y){
    for(int i=0;i<this->holder.size();i++){
        if(holder[i].x == x && holder[i].y==y)
            return holder[i].id;
    }
    return -1;
}
