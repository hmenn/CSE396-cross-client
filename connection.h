#ifndef CONNECTION_H
#define CONNECTION_H

#include "requirements.h"

using namespace std;

class Connection
{
public:
    Connection(QString ip, QString port) throw (InvalidConnectionException);
    void sendRequest(QString message) throw (exception);


private:
    QString ipAddr;
    QString portNum;
};

#endif // CONNECTION_H
