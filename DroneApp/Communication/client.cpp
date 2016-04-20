#include "client.h"

//START PUBLIC-----///////
Client::Client(QObject *parent): QObject(parent) {
    registerSlots();
    Init();
}

Client::Client(QString address, quint16 port) {
    registerSlots();
    Init();

    Connect2Host(address, port);
}

Client::~Client() {
    client.disconnectFromHost();
    client.close();
}

void Client::Connect2Host(QString address, quint16 port) {
    QHostAddress addr(address);
    client.connectToHost(addr, port);
}

//QTcpSocket Client::getClient() {
//    return this->client;
//}

bool Client::isConneted() {
    return this->hasConnection;
}

bool Client::writeData(QString str)
{
    client.waitForConnected();
    client.write(str.toStdString().c_str());

    return client.flush();
}
//END PUBLIC------////////

//START PRIVATE-----/////////
void Client::Init() {
    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        this->networkSession = new QNetworkSession(config, this);
        connect(this->networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        this->networkSession->open();
    }
}

void Client::registerSlots() {
    connect(&client, SIGNAL(connected()), this, SLOT(Awake()));
    connect(&client, SIGNAL(readyRead()), this, SLOT(readData()));
}
//END PRIVATE-----///////////

//START SLOTS-----////////
void Client::Awake() {
    this->hasConnection = true;
}

/*!
 * \brief     Client::readData
 *  \details   This function is triggered when the client receives any data.
 */

void Client::readData(){
    char buffer[1024] = {0};
    client.read(buffer, client.bytesAvailable());
    this->bytesReaded = buffer;

    emit this->hasReadData();
}
//END SLOTS-----//////////
