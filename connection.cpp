#include "requirements.h"
#include "connection.h"


using namespace std;

Connection::Connection(const QString ip) throw (InvalidConnectionException)
{

    tcpSocket = new QTcpSocket();

   /* connect(tcpSocket, SIGNAL(connected()),this, SLOT(connected()));
    connect(tcpSocket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(tcpSocket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(tcpSocket, SIGNAL(readyRead()),this, SLOT(readyRead()));
*/
    tcpSocket->connectToHost(ip,80);

    qDebug()<<"Here";

    if(tcpSocket->waitForConnected(1000)){
        qDebug()<<"Connected";
    }else{
        throw InvalidConnectionException();
    }
}


void Connection::sendRequest(QString message) throw (exception){

}

void Connection::connected()
{
    qDebug() << "connected...";

    // Hey server, tell me about you.
    tcpSocket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
}

void Connection::disconnected()
{
    qDebug() << "disconnected...";
}

void Connection::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void Connection::readyRead()
{
    qDebug() << "reading...";

    // read the data from the socket
    qDebug() << tcpSocket->readAll();
}


