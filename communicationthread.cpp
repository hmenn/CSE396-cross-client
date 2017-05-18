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
        sleep(1);
        cerr<<"Thread run"<<endl;
        //mutex lock
        mutex->lock();

        switch (*request) {
        case Constants::REQ_OPEN_CONNECTION:
            *request = Constants::REQ_ASK_CURRENT_COORDS;
            break;

        case Constants::REQ_CLOSE_CONNECTION:
            bzero(message,Constants::MIN_BUFFER_SIZE);
            sprintf(message,"%d",*request);
            conH->writeSocket(message);
            break;

        case Constants::REQ_ASK_CURRENT_COORDS:{
            bzero(message,Constants::MIN_BUFFER_SIZE);
            char temp;
            QString str = QString::number(*request);
            conH->writeSocket(str.toStdString().c_str());

            char * r = conH->readSocket(10);
            sscanf(r, "%d%c%d", xCoordinate,&temp, yCoordinate);

            this->updateCoordinates();
            qDebug() << "\nX: " << *xCoordinate << "\nY: "<< *yCoordinate;
            // not necessary
            *request = Constants::REQ_ASK_CURRENT_COORDS;

            break;
        }
        case Constants::REQ_ASK_CURRENT_IMAGE:{
            bzero(message,Constants::MIN_BUFFER_SIZE);
            char temp;

            QString str = QString::number(*request);

            conH->writeSocket(str.toStdString().c_str());

            char * r = conH->readSocket(10);
            cerr<<"Here\n";
            int size;
            sscanf(r,"%d",&size);
            qDebug()<<"Size:"<<size;
            usleep(1000000);
            int a = 0;

            while(a<90){
                r = conH->readSocket(1);
                a+=strlen(r);
                //qDebug()<<"BuffSize"<<strlen(r);
                qDebug()<<"BuffSize"<<a;

            }

            qDebug()<<"BuffSize"<<a;

            //sscanf(r, "%d%c%d", xCoordinate,&temp, yCoordinate);

            //this->updateCoordinates();

            *request = Constants::REQ_ASK_CURRENT_COORDS;

            break;
        }
        case Constants::REQ_UPDATE_COORDS:

            cerr<<"Up"<<message<<endl;
            conH->writeSocket(message);

            *request = Constants::REQ_ASK_CURRENT_COORDS;

            break;

        case Constants::REQ_CHANGE_MODE:

            conH->writeSocket(message);

            *request = Constants::REQ_ASK_CURRENT_COORDS;

        default:
            break;
        }

        //increment delayCounter
         ++delayCounter;

        //every 10 times assign REQ_ASK_CURRENT_IMAGE to request
        /*if(delayCounter%5 == 0){
            *request = Constants::REQ_ASK_CURRENT_IMAGE;
            qDebug() << "Update request to get image"<<*request<<endl;
        }*/
        mutex->unlock();

    }
    qDebug()<<"Thread quit";
}


/*
void CommunicationThread::updateCoordinates(){

}*/
