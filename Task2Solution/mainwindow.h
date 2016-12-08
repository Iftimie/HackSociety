#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <threadwebcam.h>
#include <opencv2/core/core.hpp>
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
    static cv::Mat* storeGetImage(cv::Mat *img, char* action, int slot);

private slots:
    void on_pushButton_clicked();
    void on_imageWebcamChanged();


private:
    Ui::MainWindow *ui;
    ThreadWebCam *threadWebcam;
};

#endif // MAINWINDOW_H
