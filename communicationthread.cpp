#include "communicationthread.h"

CommunicationThread::CommunicationThread(QObject* parent):QThread(parent)
{

}

void CommunicationThread::run()
{
    QByteArray msg;

    int delayCounter = 0;

    while(*request != Constants::REQ_CLOSE_CONNECTION){

        //delay as milliseconds
        msleep(300);

        //mutex lock
        mutex->lock();

        switch (*request) {

        case Constants::REQ_OPEN_CONNECTION:
            message->clear();
            message->append(QString::number(*request));
            message->append(Constants::DELIMITER);

            *request = Constants::REQ_ASK_CURRENT_COORDS;
            break;

        case Constants::REQ_CLOSE_CONNECTION:
            message->clear();
            message->append(QString::number(*request));
            message->append(Constants::DELIMITER);
            connection->sendRequest(*message);
            break;

        case Constants::REQ_ASK_CURRENT_COORDS:{

            message->clear();
            message->append(QString::number(*request));
            message->append(Constants::DELIMITER);
            connection->sendRequest(*message);

            connection->readRequest(&msg);
            QString str(msg);
            qDebug() << "Message byte array :" <<str;
            sscanf(str.toStdString().c_str(), "%d%d", xCoordinate, yCoordinate);
            qDebug() << "\nCurrent coordinates: " << str;

            this->updateCoordinates();
            qDebug() << "\nX: " << *xCoordinate << "\nY: "<< *yCoordinate;
            // not necessary
            *request = Constants::REQ_ASK_CURRENT_COORDS;

            break;
        }
        case Constants::REQ_ASK_CURRENT_IMAGE:

            message->clear();
            message->append(QString::number(*request));
            message->append(Constants::DELIMITER);
            connection->sendRequest(*message);

            //image will be saved into memory
            //necessary a loop here to takes the image
            //..

            *request = Constants::REQ_ASK_CURRENT_COORDS;

            break;

        case Constants::REQ_UPDATE_COORDS:

            connection->sendRequest(*message);

            *request = Constants::REQ_ASK_CURRENT_COORDS;

            break;

        case Constants::REQ_CHANGE_MODE:

            connection->sendRequest(*message);

            *request = Constants::REQ_ASK_CURRENT_COORDS;

        default:
            break;
        }

        //mutex unlock
        mutex->unlock();

        //increment delayCounter
        ++delayCounter;

        //every 10 times assign REQ_ASK_CURRENT_IMAGE to request
        if(delayCounter%10 == 0){
            mutex->lock();
            *request = Constants::REQ_ASK_CURRENT_IMAGE;
            qDebug() << "Update request to get image";
            qDebug() << *request;

            mutex->unlock();
        }

    }
    qDebug()<<"Thread quit";
}


/*
void CommunicationThread::updateCoordinates(){

}*/
