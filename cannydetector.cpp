#include "cannydetector.h"
#include <QDebug>
CannyDetector::CannyDetector()
{
}

CannyDetector::~CannyDetector()
{
//    for(QVector<QImage *>::Iterator it = cannyImages.begin(); it != cannyImages.end(); ++it)
//    {
//        delete *it;
//        *it = NULL;
//    }
}

QImage CannyDetector::Mat2QImage(cv::Mat const& src)
{
     cv::Mat temp; // make the same cv::Mat
     cv::cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
     QImage dest((uchar*) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     QImage dest2(dest);
     dest2.detach(); // enforce deep copy
     return dest2;
}

cv::Mat CannyDetector::QImage2Mat(QImage const& src)
{
     cv::Mat tmp(src.height(),src.width(),CV_8U,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cv::cvtColor(tmp, result,CV_RGB2BGR);
     return result;
}

bool CannyDetector::detect(const QVector<QImage > &images)
{


    cv::Mat detected_edges, blured_image;
    for(QVector<QImage>::ConstIterator it = images.begin(); it != images.end(); ++it)
    {
        cv::Mat src = QImage2Mat(*it);
        /// Reduce noise with a kernel 3x3
        cv::blur( src, blured_image, cv::Size(3,3) );

        /// Canny detector
        cv::Canny( blured_image, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
        cannyImages.push_back(Mat2QImage(detected_edges));

        static int curI = 0;
        qDebug() << "current is"  << ++curI << " ";
    }

    return true;
}
