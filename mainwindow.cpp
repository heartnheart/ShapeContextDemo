#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QPixmap>
#include <QElapsedTimer>
#include <opencv/cv.h>

#include <opencv2/shape.hpp>
using namespace cv;
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

static std::vector<Point> simpleContour( const Mat& currentQuery, int n=300 )
{
    std::vector< std::vector<Point> > _contoursQuery;
    std::vector <Point> contoursQuery;
    findContours(currentQuery, _contoursQuery, RETR_LIST, CHAIN_APPROX_NONE);
    for (size_t border=0; border<_contoursQuery.size(); border++)
    {
        for (size_t p=0; p<_contoursQuery[border].size(); p++)
        {
            contoursQuery.push_back( _contoursQuery[border][p] );
        }
    }

    // In case actual number of points is less than n
    for (int add=contoursQuery.size()-1; add<n; add++)
        contoursQuery.push_back(contoursQuery[contoursQuery.size()-add+1]); //adding dummy values

    // Uniformly sampling
    random_shuffle(contoursQuery.begin(), contoursQuery.end());
    std::vector<Point> cont;
    for (int i=0; i<n; i++)
        cont.push_back(contoursQuery[i]);

    return cont;
}

static QImage Mat2QImage(cv::Mat const& src)
{
     cv::Mat temp; // make the same cv::Mat
     cv::cvtColor(src, temp,CV_GRAY2RGB); // Convert back to RGB888 then construct QImage
     QImage dest((uchar*) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     QImage dest2(dest);
     dest2.detach(); // enforce deep copy
     return dest2;
}

static cv::Mat QImage2Mat(QImage const& src)
{


     cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cv::cvtColor(tmp, result,CV_RGB2GRAY); // need to convert from RGB(QImage) to GRAY(for Canny detection)


     return result;
}

void MainWindow::updateView()
{

    static int curTestIndex = 0;
    static int curTrainingIndex = 0;
    std::vector<Point> shapeTest;
    std::vector<Point> shapeTraining;
    static float minDis = FLT_MAX;
    static int minIndex = 0;



    if(curTestIndex == mnistReader.testImages.size())
        return;

    if(successReading)
    {
        ui->lblTestImage->setPixmap(QPixmap::fromImage(mnistReader.testImages[curTestIndex]));
      //  ui->lblTrainingImage->setPixmap(QPixmap::fromImage(mnistReader.trainingImages[curTrainingIndex]));

    }
    if(successCanny)
    {

        ui->lblCannyTest->setPixmap(QPixmap::fromImage(cannyDetector.cannyTestImages[curTestIndex]));
       // ui->lblCannyTraining->setPixmap(QPixmap::fromImage(cannyDetector.cannyTrainingImages[curTrainingIndex]));
        shapeTest = simpleContour (QImage2Mat(cannyDetector.cannyTestImages[curTestIndex]),100);
        shapeTraining = simpleContour(QImage2Mat(cannyDetector.cannyTrainingImages[curTrainingIndex]),100);
    }


    Ptr<ShapeContextDistanceExtractor> mysc = createShapeContextDistanceExtractor();
    mysc->setIterations(1);

    float dist = mysc->computeDistance(shapeTest,shapeTraining);
    if(dist < minDis)
    {
        minDis = dist;
        minIndex = curTrainingIndex;
    }


    ui->tedtOutput->append(QString("Guess %1 dist = %2\n -- ").arg(mnistReader.trainingLabels[curTrainingIndex]).arg(dist));

    ++curTrainingIndex;

    if(curTrainingIndex == mnistReader.trainingImages.size())
    {
        const uchar& trainingLbl = mnistReader.trainingLabels[minIndex];
        const uchar& testLbl = mnistReader.testLabels[curTestIndex];
        QString result = trainingLbl == testLbl ? "Right" : "Wrong";
        ui->tedtOutput->append(QString("Guess %1, GroundTruth %2 --- %3").arg(trainingLbl).arg(testLbl).arg(result));
        ui->lblTrainingImage->setPixmap(QPixmap::fromImage(mnistReader.trainingImages[minIndex]));
        ui->lblCannyTraining->setPixmap(QPixmap::fromImage(cannyDetector.cannyTrainingImages[minIndex]));

        curTrainingIndex = 0;
        ++curTestIndex;
        viewTimer->stop();

    }

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
    ui->tedtOutput->clear();
   viewTimer->start();

}



void MainWindow::on_actionRead_MNIST_Data_triggered()
{
    successReading = mnistReader.readMNISTData();
    if(!successReading)
    {
        qDebug() << "Failed to read MNIST data in ";
        return;
    }
}
