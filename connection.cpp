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


void Connection::sendRequest(const char *message) throw (exception){

    int byte = tcpSocket->write(message);
    qDebug() << "Sended : " << message.toStdString().c_str();
    //qDebug() << "Byte : " << byte;

    tcpSocket->waitForBytesWritten();
}

void Connection::readRequest(QByteArray *msg) throw (exception){
    //QByteArray msg;
    /*while(tcpSocket->bytesAvailable()>0){
        if(!tcpSocket->waitForReadyRead()){
            qDebug() << "waitForReadyRead() timed out";
        }
        *msg = tcpSocket->read(10);
        qDebug()<< *msg;
    }*/

    while(!tcpSocket->bytesAvailable());
    if(!tcpSocket->waitForReadyRead()){
        qDebug() << "waitForReadyRead() timed out";
    }

    *msg = tcpSocket->read(10);
    qDebug()<<"ReadReq" <<*msg;
}


