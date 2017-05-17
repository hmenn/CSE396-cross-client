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
    char array[250];
    memset(array, 0, 250);
    sprintf(array, "%s", message.toStdString().c_str());
    int byte = tcpSocket->write(array);
    qDebug() << "Sended : " << message.toStdString().c_str();
    qDebug() << "Byte : " << byte;

    tcpSocket->waitForBytesWritten();
}

void Connection::readRequest(QByteArray *msg) throw (exception){
    //QByteArray msg;
    //while(!tcpSocket->waitForReadyRead(500));
    *msg = tcpSocket->read(10);
    qDebug()<< *msg;
}


