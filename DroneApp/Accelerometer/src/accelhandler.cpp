#include "../header/accelhandler.h"

AccelHandler::AccelHandler(unsigned samplingPeriod)
{
    this->samplingPeriod = samplingPeriod;
    startListeningExternal();
}

AccelHandler::AccelHandler(LinAlg::Matrix<double> externalDataX, LinAlg::Matrix<double> externalDataY, LinAlg::Matrix<double> externalDataZ)/* : QObject(parent)*/
{
    this->AccelX = externalDataX;
    this->AccelY = externalDataY;
    this->AccelZ = externalDataZ;

    this->samplingPeriod = this->AccelX.getNumberOfColumns();
}

AccelHandler::AccelHandler(QObject *parent, QAccelerometer::AccelerationMode AccelMode, unsigned dataRate) : QObject(parent)
{
    startListeningAccelerometer(AccelMode, dataRate);
}

void AccelHandler::startListeningExternal()
{
    initAccelDataCapacity();
}

void AccelHandler::startListeningAccelerometer(QAccelerometer::AccelerationMode AccelMode, unsigned dataRate)
{
    initAccelDataCapacity();

    this->m_sensor = new QAccelerometer(this);
    this->m_sensor->addFilter(this);
    this->m_sensor->connectToBackend();
    this->m_sensor->setAccelerationMode(AccelMode);
    this->m_sensor->setDataRate(dataRate);
    this->m_sensor->start();
}

void AccelHandler::initAccelDataCapacity()
{
    this->AccelX = LinAlg::Zeros<double>(1, 1);
    this->AccelY = LinAlg::Zeros<double>(1, 1);
    this->AccelZ = LinAlg::Zeros<double>(1, 1);
}

void AccelHandler::Update()
{
    if(this->AccelX.getNumberOfColumns() <= this->samplingPeriod)
    {
        this->AccelX = this->AccelX | this->x;
        this->AccelY = this->AccelY | this->y;
        this->AccelZ = this->AccelZ | this->z;
    }
    else
    {
        for(unsigned i = 1; i < this->samplingPeriod; ++i)
        {
            this->AccelX(1,i) = this->AccelX(1,i+1);
            this->AccelY(1,i) = this->AccelY(1,i+1);
            this->AccelZ(1,i) = this->AccelZ(1,i+1);
        }

        this->AccelX = this->AccelX | this->x;
        this->AccelY = this->AccelY | this->y;
        this->AccelZ = this->AccelZ | this->z;
    }

    emit dataUpdated();
}

bool AccelHandler::filter(QAccelerometerReading* reading)
{
    this->x = reading->x();
    this->y = reading->y();
    this->z = reading->z();

    Update();
    qDebug("Current device acceleration: x=%f y=%f z=%f", x, y, z);
    return 1;
}

