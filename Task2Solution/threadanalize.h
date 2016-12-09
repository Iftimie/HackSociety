#ifndef THREADANALIZE_H
#define THREADANALIZE_H

#include <QtCore>
#include <QtWidgets/QMainWindow>
#include <opencv2/core/core.hpp>

using namespace cv;

class ThreadAnalize : public QThread{
    Q_OBJECT
public:
    static bool running;
    static int minH;
    static int maxH;
    static int minS;
    static int maxS;
    static int minV;
    static int maxV;
    static int erosin;

public:
    ThreadAnalize(QObject *parent );
    void colorFilter(Mat &frame,Mat &hsv);
    void findBiggestBlob(cv::Mat & matImage,cv::Rect &bounding_rect);

    void run();

signals:
    void analizeBinaryResult();
};

#endif // THREADANALIZE_H
