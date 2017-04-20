#include "requirements.h"
#include "connection.h"


using namespace std;

Connection::Connection(const QString ip) throw (InvalidConnectionException)
{
    tcpSocket = new QTcpSocket();
    tcpSocket->connectToHost(ip,Constants::PORT);

    if(tcpSocket->waitForConnected(3000)){
        qDebug()<<"Connected";
    }else{
        throw InvalidConnectionException();
    }
}

Connection::~Connection(){
    if(tcpSocket!=NULL){
        tcpSocket->close();
        delete tcpSocket;
        tcpSocket=NULL;
    }
    qDebug()<<"Connection destructed";
}


void Connection::sendRequest(QString message) throw (exception){
    int byte = tcpSocket->write(message.toStdString().c_str());
    qDebug() << "Sended : " << message.toStdString().c_str();
    qDebug() << "Byte : " << byte;
}

void Connection::readRequest() throw (exception){
    QByteArray msg;
    char buffer[50];
    //bzero(buffer,50);

    while(!tcpSocket->waitForReadyRead(500));
    msg = tcpSocket->read(5);
    qDebug()<<msg;
}


