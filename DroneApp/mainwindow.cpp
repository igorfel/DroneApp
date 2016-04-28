#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->time = 0;
    ui->ComandosWidget->setEnabled(false);
    ui->Desconectar->setEnabled(false);

//    PlotHandler::plotProperties ppX;
//    ppX.setPlotFrame(ui->widgetX);
//    //ppX.setCentralWidget(ui->widgetX);
//    ppX.setTitle("Valor bruto");
//    ppX.setxLabel("Tempo");
//    ppX.setyLabel("Aceleração");
//    ppX.setyAxisRange(-0.5,0.5);
//    this->P1 = new PlotHandler::plot<double>(1,1,ppX);

//    PlotHandler::plotProperties ppY;
//    ppY.setPlotFrame(ui->widgetY);
//    //ppY.setCentralWidget(ui->widgetY);
//    ppY.setTitle("Filtro 1");
//    ppY.setxLabel("Tempo");
//    ppY.setyLabel("Aceleração");
//    ppY.setyAxisRange(-0.5,0.5);
//    this->P2 = new PlotHandler::plot<double>(1,1, ppY);

//    PlotHandler::plotProperties ppZ;
//    ppZ.setPlotFrame(ui->widgetZ);
//    //ppZ.setCentralWidget(ui->widgetZ);
//    ppZ.setTitle("Filtro 2");
//    ppZ.setxLabel("Tempo");
//    ppZ.setyLabel("Aceleração");
//    ppZ.setyAxisRange(-0.5,0.5);
//    this->P3 = new PlotHandler::plot<double>(1,1, ppZ);

    ac = new AccelHandler(QAccelerometer::Combined, 200);
    connect(ac, SIGNAL(dataUpdated()), this, SLOT(updatePlot()));

//    QTimer *timer = new QTimer(this);
//    timer->setInterval(1000);
//    connect(timer, SIGNAL(timeout()), this, SLOT(updatePlot()));
//    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->c;
}

void MainWindow::updatePlot()
{
    //ui->label->setText(QString::number(ac->getX())+" - "+QString::number(ac->getX())+" - "+QString::number(ac->getX()));

    //P1->realTimeDataUpdate(this->time, this->ac->getX());//->getPhysicalAccelX());
    //P2->realTimeDataUpdate(this->time, this->ac/*->getY());*/->getPhysicalAccelX());
    //P3->realTimeDataUpdate(this->time, this->ac/*->getZ());//->getPhysicalAccelZ());*/->getPhysicalAccelX2());

    time++;
}


void MainWindow::on_Conectar_clicked()
{
    this->c = new Client(ui->HostInput->currentText(), ui->PortaInput->text().toInt());

    connect(c, SIGNAL(connectionSuccessful()), this, SLOT(on_connection_successful()));
    connect(c, SIGNAL(hasReadData()), this, SLOT(on_data_received()));

    ui->HostInput->setEnabled(false);
    ui->PortaInput->setEnabled(false);
}

void MainWindow::on_Desconectar_clicked()
{
    this->c->DisconnectFromHost();

    ui->conexaoLabel->setText("Desconectado!");

    ui->ComandosWidget->setEnabled(false);
    ui->Desconectar->setEnabled(false);

    ui->Conectar->setEnabled(true);
    ui->HostInput->setEnabled(true);
    ui->PortaInput->setEnabled(true);
}

void MainWindow::on_EnviarA_clicked()
{
    this->c->writeData("_A_");
}

void MainWindow::on_EnviarZ_clicked()
{
    this->c->writeData("_Z_");
}

void MainWindow::on_Enviar_clicked()
{
    this->c->writeData(ui->EnviarInput->text());
}

void MainWindow::on_connection_successful()
{
    ui->conexaoLabel->setText("Conectado!");

    ui->ComandosWidget->setEnabled(true);
    ui->Desconectar->setEnabled(true);

    ui->Conectar->setEnabled(false);
    ui->HostInput->setEnabled(false);
    ui->PortaInput->setEnabled(false);
}

void MainWindow::on_data_received()
{
    ui->MostrarDadosRecebidos->appendPlainText(this->c->dataReceived());
}
