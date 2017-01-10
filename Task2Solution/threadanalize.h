#ifndef THREADANALIZE_H
#define THREADANALIZE_H

#include <QtCore>
#include <QtWidgets/QMainWindow>
#include <opencv2/core/core.hpp>
#include <vector>
using namespace std;

using namespace cv;

class ThreadAnalize : public QThread{
    Q_OBJECT
public:
    bool firstRun = true;
    static bool running;
    static int minH;
    static int maxH;
    static int minS;
    static int maxS;
    static int minV;
    static int maxV;
    static int erosin;
    static int blur;
    static bool startRecord;
    static vector<Point2f> shapePoints;
    static char grid[11][11];
    static int currentPositionX;
    static int currentPositionY;

    static int touchPosition;
    bool settingPosition;



public:
    ThreadAnalize(QObject *parent );
    void colorFilter(Mat &frame,Mat &hsv);
    void findBiggestBlob(cv::Mat & matImage,cv::Rect &bounding_rect);
    void nextPosition(int x,int y,int width,int height);
    void touch(int x,int y,int width,int height);


    void run();

signals:
    void analizeBinaryResult();
    void classify();
    void displayShape();
};

#endif // THREADANALIZE_H
