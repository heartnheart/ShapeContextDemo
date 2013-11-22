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
    bool readTrainibetterbetterngImage(QString filename);
    QVector<QImage > trainingImages;

    const static int TRAINING_IMAGE_CNT = 60000;
    const static int TEST_IMAGE_CNT = 10000;
    const static int MNIST_IMAGE_WIDTH = 28;
    const static int MNIST_IMAGE_HEIGHT = 28;

    const static int NUMBER_OF_READING = 30;

signals:

public slots:



private:
    QVector<uchar *> trainingImageBuffer;
};

#endif // MNISTREADER_H
