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
     cv::cvtColor(src, temp,CV_GRAY2RGB); // Convert back to RGB888 then construct QImage
     QImage dest((uchar*) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     QImage dest2(dest);
     dest2.detach(); // enforce deep copy
     return dest2;
}

cv::Mat CannyDetector::QImage2Mat(QImage const& src)
{


     cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cv::cvtColor(tmp, result,CV_RGB2GRAY); // need to convert from RGB(QImage) to GRAY(for Canny detection)


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
        detected_edges = cv::Scalar::all(0);
        /// Canny detector
        cv::Canny( blured_image, detected_edges, 1, 2, 3 );
        cannyImages.push_back(Mat2QImage(detected_edges));

      //  cannyImages.push_back(Mat2QImage(blured_image));

        static int curI = 0;
        qDebug() << "current is"  << ++curI << " ";
    }
    qDebug() << "return true";
    return true;
}
