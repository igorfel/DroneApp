#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <time.h>
#include <QMainWindow>
#include <QAccelerometer>
#include <Communication/header/client.h>
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
    Client *c;
    Ui::MainWindow *ui;
    AccelHandler *ac;

    PlotHandler::plot<double> *P1, *P2, *P3;

private slots:
    void updatePlot();
    void on_connection_successful();
    void on_data_received();
    void on_Conectar_clicked();
    void on_Desconectar_clicked();
    void on_Enviar1_clicked();
    void on_Enviar2_clicked();
    void on_Enviar3_clicked();
    void on_Enviar_clicked();
    void on_Motor1_1_clicked();
    void on_Motor1_0_clicked();
    void on_Motor2_1_clicked();
    void on_Motor2_0_clicked();
    void on_Motor3_0_clicked();
    void on_Motor3_1_clicked();
    void on_Motor4_0_clicked();
    void on_Motor4_1_clicked();
    void on_Diminuir_Todos_clicked();
    void on_Zerar_clicked();
    void on_Aumentar_Todos_clicked();
};

#endif // MAINWINDOW_H
