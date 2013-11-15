#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mnistreader.h"
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
private:
    Ui::MainWindow *ui;

    MNISTReader mnistReader;

    QTimer *viewTimer;
};

#endif // MAINWINDOW_H
