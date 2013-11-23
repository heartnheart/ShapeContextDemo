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
    bool readMNISTImages(QString trainingFile, QString testFile);
    const static int TRAINING_IMAGE_CNT = 60000;
    const static int TRAINING_IMAGE_MAGIC_NUMBER = 0x00000803;
    const static int TEST_IMAGE_MAGIC_NUMBER = 0x00000803;
    const static int TEST_IMAGE_CNT = 10000;
    const static int MNIST_IMAGE_WIDTH = 28;
    const static int MNIST_IMAGE_HEIGHT = 28;

    const static int NUMBER_OF_READING = 30;

signals:

public slots:



private:

    bool readTrainingImage(QString filename);
    bool readTestImage(QString filename);

    QVector<uchar *> trainingImageBuffer;
    QVector<uchar *> testImageBuffer;
};

#endif // MNISTREADER_H
