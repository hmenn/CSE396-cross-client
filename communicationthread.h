#ifndef COMMUNICATIONTHREAD_H
#define COMMUNICATIONTHREAD_H

#include <QThread>
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
    RequestType requestType;
};

#endif // COMMUNICATIONTHREAD_H
