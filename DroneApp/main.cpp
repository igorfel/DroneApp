#include "mainwindow.h"
#include <QApplication>
#include <Communication/client.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
qDebug("Accel started");
//    Client *c = new Client("10.0.0.108",59569);

//    if(c->isConneted())
//        std::cout<<"C Conectado!";
//    else
//        std::cout<<"Erro na conexão C!";

    return a.exec();
}
