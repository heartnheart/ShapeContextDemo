#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QPixmap>
#include <QElapsedTimer>
#include <opencv/cv.h>
#include <opencv/cvwimage.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    viewTimer = new QTimer(this);
    connect(viewTimer,SIGNAL(timeout()),this,SLOT(updateView()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateView()
{

    static int curTestIndex = 0;
    static int curTrainingIndex = 0;

    if(curTrainingIndex == mnistReader.trainingImages.size())
    {
        curTrainingIndex = 0;
        ++curTestIndex;
    }

    if(curTestIndex == mnistReader.testImages.size())
        return;

    if(successReading)
    {
        ui->lblTestImage->setPixmap(QPixmap::fromImage(mnistReader.testImages[curTestIndex]));
        ui->lblTrainingImage->setPixmap(QPixmap::fromImage(mnistReader.trainingImages[curTrainingIndex]));
    }
    if(successCanny)
    {

        ui->lblCannyTest->setPixmap(QPixmap::fromImage(cannyDetector.cannyTestImages[curTestIndex]));
        ui->lblCannyTraining->setPixmap(QPixmap::fromImage(cannyDetector.cannyTrainingImages[curTrainingIndex]));
    }








    ++curTrainingIndex;

}




void MainWindow::on_actionCanny_Edge_Detect_triggered()
{
   successCanny = cannyDetector.cannyOnMNIST(mnistReader.trainingImages,mnistReader.testImages);
   if(!successCanny)
   {
       qDebug() << "Failed to detecing edges using Canny detector";
       return;
   }
}

void MainWindow::on_actionShow_triggered()
{
    // update view
   viewTimer->start(200);

}

void MainWindow::on_actionRead_Training_and_Test_Images_triggered()
{


    successReading = mnistReader.readMNISTImages("../ShapeContextDemo/data/MNIST/train-images.idx3-ubyte"
                                                 ,"../ShapeContextDemo/data/MNIST/t10k-images.idx3-ubyte");
    if(!successReading)
    {
        qDebug() << "Failed to read Test image";
        return;
    }
}
