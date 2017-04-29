#include "communicationthread.h"

CommunicationThread::CommunicationThread(QObject* parent):QThread(parent)
{

}

void CommunicationThread::run()
{
    int delayCounter = 0;



    while(*request != Constants::REQ_CLOSE_CONNECTION){
    qDebug() << "\nI am in \n";
        //delay as milliseconds
        msleep(1000);

        //mutex lock
        mutex->lock();

        switch (*request) {

            case Constants::REQ_OPEN_CONNECTION:

                message->clear();
                message->append(QString::number(*request));
                message->append(Constants::DELIMITER);
                connection->sendRequest(*message);

                *request = Constants::REQ_ASK_CURRENT_COORDS;

                break;

            case Constants::REQ_CLOSE_CONNECTION:

                message->clear();
                message->append(QString::number(*request));
                message->append(Constants::DELIMITER);
                connection->sendRequest(*message);

                //*request = Constants::REQ_ASK_CURRENT_COORDS;
                //wait moduna gececek
                break;

            case Constants::REQ_ASK_CURRENT_COORDS:

                message->clear();
                message->append(QString::number(*request));
                message->append(Constants::DELIMITER);
                connection->sendRequest(*message);

                // not necessary
                *request = Constants::REQ_ASK_CURRENT_COORDS;

                break;

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

              /*  message->clear();
                message->append(QString::number(*request));
                message->append(Constants::DELIMITER);*/
                //append coordinate 1 message->append(QString::number(xCoordiante))
                //message->append(Constants::DELIMITER);
                //append coordinate 2 message->append(QString::number(xCoordiante))
                connection->sendRequest(*message);

                //get coordinates process
                //connection->readRequest()
                //parse and set coordinate values

                *request = Constants::REQ_ASK_CURRENT_COORDS;

                break;

            default:
                break;
        }

      // connection->readRequest();

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
