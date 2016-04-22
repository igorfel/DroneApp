#-------------------------------------------------
#
# Project created by QtCreator 2016-04-20T13:16:40
#
#-------------------------------------------------

QT       += core gui\
            network \
            sensors \
        positioning \
    widgets printsupport \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DroneApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Communication/src/client.cpp \
    Accelerometer/src/accelhandler.cpp

HEADERS  += mainwindow.h \
    SistemasdeControle/headers/graphicLibs/plot.h \
    SistemasdeControle/src/graphicLibs/plot.hpp \
    Communication/header/client.h \
    Test/clienttestsuite.h \
    Accelerometer/header/accelhandler.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

