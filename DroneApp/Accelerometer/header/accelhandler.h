///
/// Created by Igorfel 21/04/16
///
#ifndef ACCELHANDLER_H
#define ACCELHANDLER_H

#include <QObject>
#include <QAccelerometer>
#include <SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h>


class AccelHandler : public QObject, QAccelerometerFilter
{
    Q_OBJECT
public:
    explicit AccelHandler(unsigned samplingPeriod = 100);                   //Used when communicating with external device
             AccelHandler(LinAlg::Matrix<double> externalDataX = "0",
                          LinAlg::Matrix<double> externalDataY = "0",
                          LinAlg::Matrix<double> externalDataZ = "0");
             AccelHandler(QObject* parent = 0, QAccelerometer::AccelerationMode AccelMode = QAccelerometer::AccelerationMode::Combined, unsigned dataRate = 10);

    qreal getX();
    qreal getY();
    qreal getZ();

    void                   setSamplingData();
    LinAlg::Matrix<double> getSamplingData();

private:
    unsigned samplingPeriod;

    qreal x,y,z;
    QAccelerometer* m_sensor;
    LinAlg::Matrix<double> AccelX, AccelY, AccelZ;

    void startListeningExternal();
    void startListeningAccelerometer(QAccelerometer::AccelerationMode AccelMode, unsigned dataRate);

    void initAccelDataCapacity();

private slots:
    void Update();
    void startUpdate();

    //Override of QAcclerometerFilter::filter(QAccelerometerReading*)
    bool filter(QAccelerometerReading* reading);

signals:
    void dataUpdated();

};

#endif // ACCELHANDLER_H
