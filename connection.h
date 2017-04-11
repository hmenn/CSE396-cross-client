#ifndef CONNECTION_H
#define CONNECTION_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <QTcpSocket>
#include "requirements.h"

using namespace std;

class Connection
{
public:
    Connection(QString ip) throw (InvalidConnectionException);
    ~Connection();
    void sendRequest(QString message) throw (exception);

signals:
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QString ipAddr;
    QTcpSocket *tcpSocket;
};

#endif // CONNECTION_H
