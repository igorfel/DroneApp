#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAccelerometer>
#include <Accelerometer/header/accelhandler.h>
#include <SistemasdeControle/headers/graphicLibs/plot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    double time;
    Ui::MainWindow *ui;
    AccelHandler *ac;

    PlotHandler::plot<double> *P1;

private slots:
    void updatePlot();
};

#endif // MAINWINDOW_H
