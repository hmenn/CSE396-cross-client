//
// Created by hmenn on 06.04.2017.
//


#include "ConnectionHelper.h"
#include "requirements.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

using namespace std;


ConnectionHelper::ConnectionHelper(QString ip,QString port) {

    this->port=port;
    this->ip=ip;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        throw  SocketCreationException(CREATE_ERROR);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(port.toStdString().c_str()));
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    inet_pton(AF_INET,ip.toStdString().c_str(),&serv_addr.sin_addr);

    if( connect(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        throw SocketCreationException(LISTEN_ERROR);
    }
    fprintf(stdout, "ConnectionHelper constucted. Port:%d now available.\n", 3965);
}


void ConnectionHelper::releaseConnection() {
    char buffer[255];
    /* while (read(socketfd, buffer, Constants::MAX_BUFFER_SIZE) > 0) {
    printf("FreeSocket Read:%s\n", buffer);
    bzero(buffer, 250);
  } // free socket*/
    close(listenfd);
    sleep(1);
    //shutdown(socketfd,SHUT_RDWR);
    fprintf(stdout,"Connection released!\n");

}

char *ConnectionHelper::readSocket(int byte) {

    char *buffer = (char *) calloc(sizeof(char), byte);
    int size = read(listenfd, buffer, byte);
    if (size > 0) {
        return buffer;
    }

    return NULL;
}

int ConnectionHelper::writeSocket(const char *msg) {
    int size;
    if ((size = write(listenfd, msg, strlen(msg))) < 0) {
        perror("write socket");
        exit(1);
    }
    return size;
}

void ConnectionHelper::handShake(){
    char msg[10];
    bzero(msg,10);
    sprintf(msg,"H");
    write(listenfd, msg,strlen(msg));
    char ch;
    do{

        read(listenfd,&ch,10);

    }while(ch!='S');
    cout<<"HandShake"<<endl;
}

ConnectionHelper::~ConnectionHelper() {
    char buffer[250];
    bzero(buffer, 250);

    //shutdown(socketfd,SHUT_RDWR);
    //shutdown(serverfd,SHUT_RDWR);
    //close(socketfd);
    close(listenfd);
    printf("Socket-Port:%d closed.", 3965);
    sleep(1);
}

int ConnectionHelper::getListenFD() const {
    return listenfd;
}
