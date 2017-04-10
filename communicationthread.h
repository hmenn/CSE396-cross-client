#ifndef COMMUNICATIONTHREAD_H
#define COMMUNICATIONTHREAD_H

#include <QThread>
#include <QMutex>
#include "connection.h"
#include "requirements.h"


class CommunicationThread : public QThread
{
    Q_OBJECT
public:
    explicit CommunicationThread(QObject* parent=0);
    void run();

    QMutex *mutex;
    QString *message;
    int *request;

    Connection *connection;

private:
    int requestType;
};

#endif // COMMUNICATIONTHREAD_H
