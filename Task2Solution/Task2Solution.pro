#-------------------------------------------------
#
# Project created by QtCreator 2016-12-08T22:37:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Task2Solution
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    threadwebcam.cpp

INCLUDEPATH +=C:/OpenCV2410/opencv/build/include
LIBS +=-LC:/OpenCV2410/opencv/build/x64/vc12/lib \
opencv_calib3d2410d.lib \
opencv_contrib2410d.lib \
opencv_core2410d.lib \
opencv_features2d2410d.lib \
opencv_flann2410d.lib \
opencv_gpu2410d.lib \
opencv_highgui2410d.lib \
opencv_imgproc2410d.lib \
opencv_legacy2410d.lib \
opencv_ml2410d.lib \
opencv_nonfree2410d.lib \
opencv_objdetect2410d.lib \
opencv_ocl2410d.lib \
opencv_photo2410d.lib \
opencv_stitching2410d.lib \
opencv_superres2410d.lib \
opencv_ts2410d.lib \
opencv_video2410d.lib \
opencv_videostab2410d.lib

INCLUDEPATH +=C:/Armadillo/include
LIBS +=-LC:/Armadillo/examples/lib_win64 \
blas_win64_MT.lib \
lapack_win64_MT.lib

HEADERS  += mainwindow.h \
    threadwebcam.h

FORMS    += mainwindow.ui
