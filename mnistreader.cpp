#include "mnistreader.h"
#include <QFile>
#include <QDataStream>
#include <QtDebug>
#include <QDir>
#include <QImage>
MNISTReader::MNISTReader(QObject *parent) :
    QObject(parent)
{

}
MNISTReader::~MNISTReader()
{

    // clean the buffer QImage used
    for(QVector<uchar*>::Iterator it = trainingImageBuffer.begin(); it != trainingImageBuffer.end(); ++it)
    {
        delete *it;
        *it = NULL;
    }

}

bool MNISTReader::readTrainibetterbetterngImage(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open file " << file.fileName();
        return false;
    }
    QDataStream in(&file);    // read the data serialized from the file

    // readin magic number
    quint32 magicNumber;
    in >> magicNumber;
    if(magicNumber != 0x803)
    {
        qDebug() << "This is not the correct MNIST training image file!";
        return false;
    }
    qDebug("magic number = 0x%08x\n" ,magicNumber);

    // readin number of images
    quint32 numberOfImages;
    in >> numberOfImages;
    qDebug("number of items = %d\n",numberOfImages);
    Q_ASSERT(numberOfImages == TRAINING_IMAGE_CNT);

    // read in number of rows and cols
    quint32 rowCnt, colCnt;
    in >> rowCnt >> colCnt;
    Q_ASSERT(rowCnt ==  MNIST_IMAGE_HEIGHT);
    Q_ASSERT(colCnt ==  MNIST_IMAGE_WIDTH);

    // read in images
    uchar* pImageBuffer = NULL;
    QImage* pImage = NULL;
    QVector<QRgb> grayscaleTable;
    for(int i = 0; i < 256; i++)
        grayscaleTable.push_back(qRgb(i,i,i));
    //for(int i = 0; i < TRAINING_IMAGE_CNT; i++)
    for(int i = 0; i < NUMBER_OF_READING; ++i)
    {
        // read in raw data of one image
        pImageBuffer = new uchar[rowCnt * colCnt];
        for(uint j = 0; j < rowCnt * colCnt; ++j)
            in >> pImageBuffer[j];

        pImage = new QImage(pImageBuffer,colCnt,rowCnt,QImage::Format_Indexed8);
        pImage->setColorTable(grayscaleTable);
        trainingImageBuffer.push_back(pImageBuffer);
        trainingImages.push_back(pImage->convertToFormat(QImage::Format_RGB888));
        delete pImage;
    }

    return true;
}
