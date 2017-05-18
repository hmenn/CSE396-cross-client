#include "communicationthread.h"
#include "mainwindow.h"

CommunicationThread::CommunicationThread(QObject* parent):QThread(parent)
{

}

void CommunicationThread::run()
{
    QByteArray msg;
    char array[100000];

    int delayCounter = 0;
    while(*request != Constants::REQ_CLOSE_CONNECTION){
        //delay as milliseconds
        usleep(400000);
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
            int angle;
            QString str = QString::number(*request);
            conH->writeSocket(str.toStdString().c_str());

            char * r = conH->readSocket(Constants::MIN_BUFFER_SIZE);
            sscanf(r, "%d%c%d%c%d%c", xCoordinate,&temp, yCoordinate,&temp,&angle,&temp);

           // sscanf(r, "%d%c%d", xCoordinate,&temp, yCoordinate);

            this->updateCoordinates();
            qDebug() << "\nX: " << *xCoordinate << "\nY: "<< *yCoordinate<<"<\n" << angle;
            foundAngle=angle;
            // not necessary
            *request = Constants::REQ_ASK_CURRENT_COORDS;

            break;
        }
        case Constants::REQ_ASK_CURRENT_IMAGE:{
            bzero(message,Constants::MIN_BUFFER_SIZE);
            char temp;

            QString str = QString::number(*request);

            conH->writeSocket(str.toStdString().c_str());

            char * r = conH->readSocket(Constants::MIN_BUFFER_SIZE);
            cerr<<"Here\n";
            int size;
            sscanf(r,"%d",&size);
            qDebug()<<"Size:"<<size;
            usleep(1000);
            int a = 0;




            for(int i = 0; i<size; ++i){
                r = conH->readSocket(1);
                a+=strlen(r);
                if(r[0] == 0){
                    array[i] = '\0';
                }
                array[i] = r[0];

                //qDebug()<<"BuffSize"<<a;

            }

            if(size > 0){
                image->clear();

               for(int i=0; i<size;++i){
                    image->append(array[i]);
               }
            }



           cerr << "size" << image->size();



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
             image->clear();
            *request = Constants::REQ_ASK_CURRENT_COORDS;

        default:
            break;
        }

        //increment delayCounter
         ++delayCounter;

        //every 10 times assign REQ_ASK_CURRENT_IMAGE to request
        if(delayCounter%5 == 0){
            *request = Constants::REQ_ASK_CURRENT_IMAGE;
            qDebug() << "Update request to get image"<<*request<<endl;
        }
        mutex->unlock();

    }
    qDebug()<<"Thread quit";
}


/*
void CommunicationThread::updateCoordinates(){

}*/
