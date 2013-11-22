#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QPixmap>
#include <QElapsedTimer>
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

    static int curIndex = 0;
    if(successReading)
        ui->imageLabel->setPixmap(QPixmap::fromImage( mnistReader.trainingImages[curIndex]));
    if(successCanny)
        ui->cannyLabel->setPixmap(QPixmap::fromImage(cannyDetector.cannyImages[curIndex]));

    ++curIndex;
}

void MainWindow::on_actionRead_Training_Image_triggered()
{
   successReading = mnistReader.readTrainibetterbetterngImage("../ShapeContextDemo/data/MNIST/train-images.idx3-ubyte");
   if(!successReading)
   {
       qDebug() << "Failed to construct image";
       return;
   }

  }



void MainWindow::on_actionCanny_Edge_Detect_triggered()
{
   successCanny = cannyDetector.detect(mnistReader.trainingImages);
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
