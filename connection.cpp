#include "requirements.h"
#include "connection.h"


using namespace std;

Connection::Connection(const QString ip) throw (InvalidConnectionException)
{
    std::cout<<"Connection opened"<<std::endl;



    tcpSocket = new QTcpSocket();
    tcpSocket->connectToHost("bogotobogo.com",80);

    if(tcpSocket->waitForConnected()){
        qDebug()<<"Connected";
    }else{
        throw new InvalidConnectionException;
    }
}


void Connection::sendRequest(QString message) throw (exception){

}
