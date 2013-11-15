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
    ui->imageLabel->setPixmap(QPixmap::fromImage( *mnistReader.trainingImages[curIndex++]));

}

void MainWindow::on_actionRead_Training_Image_triggered()
{
   bool success = mnistReader.readTrainibetterbetterngImage("../ShapeContextDemo/data/MNIST/train-images.idx3-ubyte");
   if(!success)
   {
       qDebug() << "Failed to construct image";
       return;
   }

   // update view
   viewTimer->start(200);
}


