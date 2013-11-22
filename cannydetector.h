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
    bool detect(const QVector<QImage > &images);

    QVector<QImage > cannyImages;

private:
    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);

    int lowThreshold = 0;
    int ratio = 3;
    int kernel_size = 3;
};

#endif // CANNYDETECTOR_H
