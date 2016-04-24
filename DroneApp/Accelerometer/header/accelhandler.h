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
             AccelHandler(QAccelerometer::AccelerationMode AccelMode = QAccelerometer::Combined, unsigned dataRate = 10);

    void                   setSamplingData();
    LinAlg::Matrix<double> getSamplingData();

    qreal getX(){ return x; }
    qreal getY(){ return y; }
    qreal getZ(){ return z; }

    LinAlg::Matrix<double> getAccelX(){ return AccelX; }
    LinAlg::Matrix<double> getAccelY(){ return AccelY; }
    LinAlg::Matrix<double> getAccelZ(){ return AccelZ; }

    double getPhysicalAccelX(){ return physicalX; }
    double getPhysicalAccelY(){ return physicalY; }
    double getPhysicalAccelZ(){ return physicalZ; }

private:
    unsigned samplingPeriod;

    double physicalX,physicalY,physicalZ;

    qreal x,y,z;
    QAccelerometer* m_sensor;
    LinAlg::Matrix<double> AccelX, AccelY, AccelZ, Gravity;

    void Update();
    void lowPassFilter(double alpha);
    void initAccelDataCapacity();
    void startListeningExternal();
    void startListeningAccelerometer(QAccelerometer::AccelerationMode AccelMode, unsigned dataRate);

    //Override of QAcclerometerFilter::filter(QAccelerometerReading*)
    bool filter(QAccelerometerReading* reading);

signals:
    void dataUpdated();

};

#endif // ACCELHANDLER_H
