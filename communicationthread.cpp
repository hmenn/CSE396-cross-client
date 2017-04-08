#include "communicationthread.h"

CommunicationThread::CommunicationThread(QObject* parent):QThread(parent)
{

}

void CommunicationThread::run()
{
    while(1){

        switch (*request) {

        case requestType.OPEN_CONN:

            mutex->lock();
            connection->sendRequest(*message);
            //...
            mutex->unlock();

            break;

        case requestType.CLOSE_CONN:

            mutex->lock();
            connection->sendRequest(*message);
            //...
            mutex->unlock();

            break;

        case requestType.GET_COORDS:

            mutex->lock();
            connection->sendRequest(*message);
            //...
            mutex->unlock();

            break;

        case requestType.GET_CURR_IMAGE:

            mutex->lock();
            connection->sendRequest(*message);
            //...
            mutex->unlock();

            break;

        case requestType.UPDATE_COORDS:

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
