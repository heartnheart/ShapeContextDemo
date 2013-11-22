#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mnistreader.h"
#include "cannydetector.h"
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionRead_Training_Image_triggered();

    void updateView();
    void on_actionCanny_Edge_Detect_triggered();

    void on_actionShow_triggered();

private:
    Ui::MainWindow *ui;

    MNISTReader mnistReader;
    CannyDetector cannyDetector;

    QTimer *viewTimer;

    bool successReading = false;
    bool successCanny = false;
};

#endif // MAINWINDOW_H
