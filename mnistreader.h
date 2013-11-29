#ifndef MNISTREADER_H
#define MNISTREADER_H

#include <QObject>
#include <QString>
#include <QImage>
#include <QVector>

class MNISTReader : public QObject
{
    Q_OBJECT
public:
    explicit MNISTReader(QObject *parent = 0);
    ~MNISTReader();

    QVector<QImage > trainingImages;
    QVector<QImage > testImages;
    QVector<uchar> trainingLabels;
    QVector<uchar> testLabels;

    bool readMNISTData();

    const static int TRAINING_IMAGE_CNT = 60000;
    const static int TRAINING_IMAGE_MAGIC_NUMBER = 0x00000803;
    const static int TEST_IMAGE_MAGIC_NUMBER = 0x00000803;
    const static int TRAINING_LABEL_MAGIC_NUMBER =  0x00000801;
    const static int TEST_LABEL_MAGIC_NUMBER =  0x00000801;
    const static int TEST_IMAGE_CNT = 10000;
    const static int MNIST_IMAGE_WIDTH = 28;
    const static int MNIST_IMAGE_HEIGHT = 28;

    const static int NUMBER_OF_READING = 60000;

signals:

public slots:



private:
    bool readMNISTImages(QString trainingFile, QString testFile);
    bool readMNISTLabels(QString trainingFile, QString testFile);
    bool readTrainingImage(QString filename);
    bool readTestImage(QString filename);
    bool readTrainingLabels(QString filename);
    bool readTestLabels(QString filename);

    QVector<uchar *> trainingImageBuffer;
    QVector<uchar *> testImageBuffer;
};

#endif // MNISTREADER_H
