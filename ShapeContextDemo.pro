#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T21:37:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShapeContextDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mnistreader.cpp \
    cannydetector.cpp \
    shapecontextextractor.cpp

HEADERS  += mainwindow.h \
    mnistreader.h \
    cannydetector.h \
    shapecontextextractor.h

FORMS    += mainwindow.ui

RESOURCES += \
    ShapeContext.qrc

INCLUDEPATH += $$(OPENCV_INCLUDE)

LIBS += -L$$(OPENCV_LIB)

LIBS += -lopencv_core300.dll\
        -lopencv_imgproc300.dll\
        -lopencv_shape300.dll
