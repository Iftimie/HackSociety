#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <threadwebcam.h>
#include <opencv2/core/core.hpp>
#include "threadanalize.h"
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static Mat image0;
    static Mat image1;
    static Mat* storeGetImage(Mat *img, char* action, int slot);
    static Mat procImage0;
    static Mat procImage1;
    static Mat* storeGetProcImage(Mat *img, char* action, int slot);

private slots:
    void on_imageWebcamChanged();
    void on_analizeBinaryResult();


    void on_btnSaveParams_clicked();

    void on_btnLoadParams_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_startRecord_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_saveAndNext_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    ThreadWebCam *threadWebcam;
    ThreadAnalize *threadAnalize;

    char outputVector[100];
    int indexStart;

    void saveBinarizationParams(int hmin, int hmax, int smin, int smax, int vmin, int vmax,int erosin);
    void loadBinarizationParams(int& hmin, int& hmax, int& smin, int& smax, int& vmin, int& vmax,int &erosin);
    cv::Mat GetSquareImage( const cv::Mat& img, int target_width );
    void appendToFile(char* fileName, char* textToAppend);
    Mat translateImg(Mat &img, int offsetx, int offsety);
    cv::Mat rotate_and_crop(double angle,cv::Mat &mat);
    cv::Rect getLargestRect(double imageWidth, double imageHeight, double rotAngDeg, int type);
};

#endif // MAINWINDOW_H
