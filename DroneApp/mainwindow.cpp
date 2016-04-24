#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->time = 0;

    PlotHandler::plotProperties pp;
    //pp.setPlotFrame(ui->centralWidget);
    pp.setCentralWidget(ui->centralWidget);
    pp.setTitle("Título");
    pp.setxLabel("Legenda eixo X");
    pp.setyLabel("Legenda eixo Y");
    this->P1 = new PlotHandler::plot<double>(1,1, pp);

    ac = new AccelHandler(QAccelerometer::User, 1000);
    connect(ac, SIGNAL(dataUpdated()), this, SLOT(updatePlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePlot()
{
    ui->label->setText(QString::number(ac->getX())+" - "+QString::number(ac->getX())+" - "+QString::number(ac->getX()));

    P1->realTimeDataUpdate(this->time, this->ac->getX());

    time++;
}
