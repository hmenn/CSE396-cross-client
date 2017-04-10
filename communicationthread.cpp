#include "communicationthread.h"

CommunicationThread::CommunicationThread(QObject* parent):QThread(parent)
{

}

void CommunicationThread::run()
{
    while(1){

        switch (*request) {

        case Constants::REQ_OPEN_CONNECTION:

            mutex->lock();
            connection->sendRequest(*message);
            //...
            mutex->unlock();

            break;

        case Constants::REQ_CLOSE_CONNECTION:

            mutex->lock();
            connection->sendRequest(*message);
            //...
            mutex->unlock();

            break;

        case Constants::REQ_ASK_CURRENT_COORDS:

            mutex->lock();
            connection->sendRequest(*message);
            //...
            mutex->unlock();

            break;

        case Constants::REQ_ASK_CURRENT_IMAGE:

            mutex->lock();
            connection->sendRequest(*message);
            //...
            mutex->unlock();

            break;

        case Constants::REQ_UPDATE_COORDS:

            mutex->lock();
            connection->sendRequest(*message);
            //...
            mutex->unlock();

            break;

        default:
            break;
        }
    }
}
