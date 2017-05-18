#ifndef COMMUNICATIONTHREAD_H
#define COMMUNICATIONTHREAD_H

#include <QThread>
#include <QMutex>
#include "connection.h"
#include "requirements.h"
#include "ConnectionHelper.h"


class CommunicationThread : public QThread
{
    Q_OBJECT
public:
    explicit CommunicationThread(QObject* parent=0);
    void run();



    QMutex *mutex;
    char *message;
    int *request;

    Connection *connection;
    ConnectionHelper *conH;
    QByteArray *image;

    int* xCoordinate;
    int* yCoordinate;

signals:
    void updateCoordinates();

private:
    int requestType;
};

#endif // COMMUNICATIONTHREAD_H
