#ifndef THREADTRAINER_H
#define THREADTRAINER_H

#include <QtCore>
#include <QtWidgets/QMainWindow>
#include <opencv2/core/core.hpp>
#include "Neural_Armadillo.h"

class ThreadTrainer : public QThread{
    Q_OBJECT
public:

    static bool running;

public:
    ThreadTrainer(QObject *parent );
    void run();
    static void saveStandardNeuralNet(Neural &net);


signals:
    void FinishedTrainingNeural();
};


#endif // STANDARDNEURALTRAINER_H
