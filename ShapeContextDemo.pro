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
    mnistreader.cpp

HEADERS  += mainwindow.h \
    mnistreader.h

FORMS    += mainwindow.ui

RESOURCES += \
    ShapeContext.qrc
