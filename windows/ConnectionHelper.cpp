//
// Created by hmenn on 06.04.2017.
//


#include "ConnectionHelper.h"
#include "requirements.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;


ConnectionHelper::ConnectionHelper(QString ip,QString port) {

    this->port=port;
    this->ip=ip;


    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        exit(1);
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(ip.toStdString().c_str(), port.toStdString().c_str(), &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        exit(1);
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                               ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            exit(1);
        }

        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        exit(1);
    }

}


void ConnectionHelper::releaseConnection() {
    char buffer[255];
    /* while (read(socketfd, buffer, Constants::MAX_BUFFER_SIZE) > 0) {
    printf("FreeSocket Read:%s\n", buffer);
    bzero(buffer, 250);
  } // free socket*/
    closesocket(ConnectSocket);
    Sleep(1);
    //shutdown(socketfd,SHUT_RDWR);
    fprintf(stdout,"Connection released!\n");

}

char *ConnectionHelper::readSocket(int byte) {

    char *buffer = (char *) calloc(sizeof(char), byte);
    do {
        iResult = recv(ConnectSocket, buffer, byte, 0);
        if ( iResult > 0 )
            printf("Bytes received: %d\n", iResult);
        else if ( iResult == 0 )
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while( iResult > 0 );

    return buffer;
}

int ConnectionHelper::writeSocket(const char *msg) {   
    iResult = send( ConnectSocket, msg, (int)strlen(msg), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    return iResult;
}

void ConnectionHelper::handShake(){
    char msg[10];
    ZeroMemory(msg,10);
    sprintf(msg,"H");
    writeSocket(msg);
    char ch;
    do{
        do {
            iResult = recv(ConnectSocket, &ch, 10, 0);
            if ( iResult > 0 )
                printf("Bytes received: %d\n", iResult);
            else if ( iResult == 0 )
                printf("Connection closed\n");
            else
                printf("recv failed with error: %d\n", WSAGetLastError());

        } while( iResult > 0 );

    }while(ch!='S');

    cout<<"HandShake"<<endl;
}

ConnectionHelper::~ConnectionHelper() {
    char buffer[250];
    ZeroMemory(buffer, 250);


    closesocket(ConnectSocket);
    WSACleanup();
    Sleep(1);
}

int ConnectionHelper::getListenFD() const {
    return ConnectSocket;
}
