//
// Created by hmenn on 06.04.2017.
//

#ifndef CONNECTION_HELPER
#define CONNECTION_HELPER

#include <sys/types.h>
#include <QString>
#include "requirements.h"

class ConnectionHelper {

public:
    ConnectionHelper(QString ip, QString port);
    ~ConnectionHelper();

    char *readSocket(int byte);
    int writeSocket(const char *msg);
    void releaseConnection();
    void startRemoteServer();
    void openArdConnection();
    void handShake();
    bool state=false;
    int getListenFD() const;
private:
    QString ip;
    QString port;
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
            *ptr = NULL,
            hints;
    int iResult;
};


#endif //CSE396_RASP_ALI_RECOGNER_CONNECTIONHELPER_H
