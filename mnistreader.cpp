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

bool MNISTReader::readMNISTImages(QString trainingFile, QString testFile)
{
    bool success = readTrainingImage(trainingFile);
    if(!success)
    {
        qDebug() << "Can't read MNIST training images";
        return false;
    }
    success = readTestImage(testFile);
    if(!success)
    {
        qDebug() << "Cant' open MNIST test file";
        return false;
    }
    qDebug() << "Success Readin" << endl;
    return true;
}

bool MNISTReader::readMNISTData()
{
    bool successReading = readMNISTImages("../ShapeContextDemo/data/MNIST/train-images.idx3-ubyte"
                                          ,"../ShapeContextDemo/data/MNIST/t10k-images.idx3-ubyte");

    if(!successReading)
    {
        qDebug() << "Failed to read MNIST images";
        return false;
    }
    successReading = readMNISTLabels("../ShapeContextDemo/data/MNIST/train-labels.idx1-ubyte",
                                     "../ShapeContextDemo/data/MNIST/t10k-labels.idx1-ubyte");
    if(!successReading)
    {
        qDebug() << "Failed to read MNIST labels";
        return false;
    }
    return true;
}

bool MNISTReader::readMNISTLabels(QString trainingFile, QString testFile)
{
    bool success = readTrainingLabels(trainingFile);
    if(!success)
    {
        qDebug() << "Can't read MNIST training labels";
        return false;
    }
    success = readTestLabels(testFile);
    if(!success)
    {
        qDebug() << "Cant' open MNIST test labels";
        return false;
    }
    qDebug() << "Success Readin labels" << endl;
    return true;
}

bool MNISTReader::readTrainingImage(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open training image file " << file.fileName();
        return false;
    }
    QDataStream in(&file);    // read the data serialized from the file

    // readin magic number
    quint32 magicNumber;
    in >> magicNumber;
    if(magicNumber != TRAINING_IMAGE_MAGIC_NUMBER)
    {
        qDebug() << "This (" << magicNumber << ") is not the correct MNIST TRAINING image file!";
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

bool MNISTReader::readTestImage(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open test image file " << file.fileName();
        return false;
    }
    QDataStream in(&file);    // read the data serialized from the file

    // readin magic number
    quint32 magicNumber;
    in >> magicNumber;
    if(magicNumber != TEST_IMAGE_MAGIC_NUMBER)
    {
        qDebug() << "This is not the correct MNIST TEST image file!";
        return false;
    }
    qDebug("magic number = 0x%08x\n" ,magicNumber);

    // readin number of images
    quint32 numberOfImages;
    in >> numberOfImages;
    qDebug("number of items = %d\n",numberOfImages);
    Q_ASSERT(numberOfImages == TEST_IMAGE_CNT);

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
        testImageBuffer.push_back(pImageBuffer);
        testImages.push_back(pImage->convertToFormat(QImage::Format_RGB888));
        delete pImage;
    }

    return true;
}

bool MNISTReader::readTrainingLabels(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open training LABEL file " << file.fileName();
        return false;
    }
    QDataStream in(&file);    // read the data serialized from the file

    // readin magic number
    quint32 magicNumber;
    in >> magicNumber;
    if(magicNumber != TRAINING_LABEL_MAGIC_NUMBER)
    {
        qDebug() << "This (" << magicNumber << ") is not the correct MNIST TRAINING LABEL file!";
        return false;
    }
    qDebug("magic number = 0x%08x\n" ,magicNumber);

    // readin number of images
    quint32 numberOfImages;
    in >> numberOfImages;
    qDebug("number of items = %d\n",numberOfImages);
    Q_ASSERT(numberOfImages == TRAINING_IMAGE_CNT);


    uchar tlabel;
    for(int i = 0; i < TRAINING_IMAGE_CNT; ++i)
    {
        in >> tlabel;
        trainingLabels.append(tlabel);
    }


    return true;
}

bool MNISTReader::readTestLabels(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open test LABEL file " << file.fileName();
        return false;
    }
    QDataStream in(&file);    // read the data serialized from the file

    // readin magic number
    quint32 magicNumber;
    in >> magicNumber;
    if(magicNumber != TEST_LABEL_MAGIC_NUMBER)
    {
        qDebug() << "This (" << magicNumber << ") is not the correct MNIST TEST LABEL file!";
        return false;
    }
    qDebug("magic number = 0x%08x\n" ,magicNumber);

    // readin number of labels
    quint32 numberOfImages;
    in >> numberOfImages;
    qDebug("number of items = %d\n",numberOfImages);
    Q_ASSERT(numberOfImages == TEST_IMAGE_CNT);


    uchar tlabel;
    for(int i = 0; i < TRAINING_IMAGE_CNT; ++i)
    {
        in >> tlabel;
        testLabels.append(tlabel);
    }


    return true;
}

