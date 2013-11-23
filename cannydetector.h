#ifndef CANNYDETECTOR_H
#define CANNYDETECTOR_H
#include <QImage>
#include <QVector>
#include <opencv/cv.h>
class CannyDetector
{
public:
    CannyDetector();
    ~CannyDetector();


    QVector<QImage > cannyTrainingImages;
    QVector<QImage > cannyTestImages;
    bool cannyOnMNIST(const QVector<QImage> & trainingImages, const QVector<QImage> & testImages);
private:
    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);
    bool detect(const QVector<QImage > &images, QVector<QImage> & output);
    int lowThreshold = 20;
    int ratio = 3;
    int kernel_size = 3;
};

#endif // CANNYDETECTOR_H
