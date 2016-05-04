#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->time = 0;
    //ui->tabWidget->setEnabled(false);
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

    //ui->HostInput->setEnabled(false);
    //ui->PortaInput->setEnabled(false);
}

void MainWindow::on_Desconectar_clicked()
{
    this->c->DisconnectFromHost();

    ui->conexaoLabel->setText("Desconectado!");

    ui->tabWidget->setEnabled(false);
    ui->Desconectar->setEnabled(false);

    ui->Conectar->setEnabled(true);
    ui->HostInput->setEnabled(true);
    ui->PortaInput->setEnabled(true);
}

void MainWindow::on_Enviar1_clicked()
{
    this->c->writeData("_b_");
}

void MainWindow::on_Enviar2_clicked()
{
    this->c->writeData("_g_");
}


void MainWindow::on_Enviar3_clicked()
{
    this->c->writeData("_t_");
}

void MainWindow::on_Enviar_clicked()
{
    this->c->writeData(ui->EnviarInput->text());
}

void MainWindow::on_connection_successful()
{
    ui->conexaoLabel->setText("Conectado!");

    ui->tabWidget->setEnabled(true);
    ui->Desconectar->setEnabled(true);

    ui->Conectar->setEnabled(false);
    ui->HostInput->setEnabled(false);
    ui->PortaInput->setEnabled(false);
}

void MainWindow::on_data_received()
{
    ui->MostrarDadosRecebidos->appendPlainText(this->c->dataReceived());
}


void MainWindow::on_Motor1_0_clicked()
{
    this->c->writeData("_0_");
}

void MainWindow::on_Motor1_1_clicked()
{
    this->c->writeData("_1_");
}

void MainWindow::on_Motor2_0_clicked()
{
    this->c->writeData("_2_");
}

void MainWindow::on_Motor2_1_clicked()
{
    this->c->writeData("_3_");
}

void MainWindow::on_Motor3_0_clicked()
{
    this->c->writeData("_4_");
}

void MainWindow::on_Motor3_1_clicked()
{
    this->c->writeData("_5_");
}

void MainWindow::on_Motor4_0_clicked()
{
    this->c->writeData("_6_");
}

void MainWindow::on_Motor4_1_clicked()
{
    this->c->writeData("_7_");
}

void MainWindow::on_Diminuir_Todos_clicked()
{
    if(ui->Motor1_Flag->isChecked())
        this->c->writeData("_0_");
    if(ui->Motor2_Flag->isChecked())
        this->c->writeData("_2_");
    if(ui->Motor3_Flag->isChecked())
        this->c->writeData("_4_");
    if(ui->Motor4_Flag->isChecked())
        this->c->writeData("_6_");
}

void MainWindow::on_Zerar_clicked()
{
    this->c->writeData("_b_");
}

void MainWindow::on_Aumentar_Todos_clicked()
{
    if(ui->Motor1_Flag->isChecked())
        this->c->writeData("_1_");
    if(ui->Motor2_Flag->isChecked())
        this->c->writeData("_3_");
    if(ui->Motor3_Flag->isChecked())
        this->c->writeData("_5_");
    if(ui->Motor4_Flag->isChecked())
        this->c->writeData("_7_");
}
