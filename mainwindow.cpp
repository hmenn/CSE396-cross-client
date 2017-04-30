#include <iostream>
#include <QProgressBar>
#include <QProgressDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "communicationthread.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    disableUI();

    xCoor =0;
    yCoor =0;

    /* Connection part */
    connection=NULL;




}
void MainWindow::updateCoordinates(){
    cerr << " geidiiiiii " << xCoor;
    ui->xCoordinate->setText(QString::number(xCoor));
    ui->yCoordinate->setText(QString::number(yCoor));
}

void MainWindow::disableUI(){
    ui->btn_conn->setEnabled(true);
    ui->btn_disconn->setEnabled(false);
    ui->grp_system->setEnabled(false);
    ui->grp_steps->setEnabled(false);
}

void MainWindow::enableUI(){
    ui->btn_conn->setEnabled(false);
    ui->btn_disconn->setEnabled(true);
    ui->grp_system->setEnabled(true);
    ui->grp_steps->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;

    if(connection!=NULL)
        delete connection;
    //delete comThread;
}


void MainWindow::on_btn_conn_clicked(){
    QString ip;
    try{
        //throw InvalidConnectionException();
        ip = ui->ledit_ip->text();
        connection=new Connection(ip);

        // initialization message
        request = Constants::REQ_OPEN_CONNECTION;
        message.append(QString::number(request));
        message.append(Constants::DELIMITER);
        //qDebug() << message.toStdString().c_str();

        /* initialize connection thread */
        comThread = new CommunicationThread(this);
        comThread->mutex = &mutex;
        comThread->request = &request;
        comThread->message = &message;
        comThread->xCoordinate = &this->xCoor;
        comThread->yCoordinate = &this->yCoor;

        connect(comThread,SIGNAL(updateCoordinates()),this,SLOT(updateCoordinates()));

        comThread->connection = connection;

        //connection->sendRequest("Merhaba");
        //connection->readRequest();

        comThread->start();

        ui->message_box->append("Connection is started automatic mode...");


        enableUI();
    }catch(exception &e){
        qDebug()<<e.what();
        ui->message_box->append(e.what());
        ui->btn_conn->setEnabled(true);
    }

}

void MainWindow::on_btn_disconn_clicked(){

    if(connection!=NULL){
        mutex.lock();
        request = Constants::REQ_CLOSE_CONNECTION;
        mutex.unlock();

        //delete connection;
        while(comThread->isRunning());
        delete connection;
        connection=NULL;
    }

    ui->message_box->append("Disconnected from raspberry...");

    disableUI();
}


void MainWindow::on_xPositive_clicked()
{
    mutex.lock();
    request = Constants::REQ_UPDATE_COORDS;
    message.clear();
    message.append(QString::number(request));
    message.append(Constants::DELIMITER);
    message.append("1");
    message.append(Constants::DELIMITER);
    message.append("0");

    mutex.unlock();
}

void MainWindow::on_xNegative_clicked()
{
    mutex.lock();
    request = Constants::REQ_UPDATE_COORDS;
    message.clear();
    message.append(QString::number(request));
    message.append(Constants::DELIMITER);
    message.append("-1");
    message.append(Constants::DELIMITER);
    message.append("0");

    mutex.unlock();
}

void MainWindow::on_yPositive_clicked()
{
    mutex.lock();
    request = Constants::REQ_UPDATE_COORDS;
    message.clear();
    message.append(QString::number(request));
    message.append(Constants::DELIMITER);
    message.append("0");
    message.append(Constants::DELIMITER);
    message.append("1");
    mutex.unlock();
}

void MainWindow::on_yNegative_clicked()
{
    mutex.lock();
    request = Constants::REQ_UPDATE_COORDS;
    message.clear();
    message.append(QString::number(request));
    message.append(Constants::DELIMITER);
    message.append("0");
    message.append(Constants::DELIMITER);
    message.append("-1");
    mutex.unlock();
}

void MainWindow::on_sendButton_clicked()
{
    mutex.lock();
    request = Constants::REQ_UPDATE_COORDS;
    message.clear();
    message.append(QString::number(request));
    message.append(Constants::DELIMITER);
    message.append(ui->ledit_stepX->text());
    message.append(Constants::DELIMITER);
    message.append(ui->ledit_stepY->text());
    mutex.unlock();
}


void MainWindow::on_startButton_clicked()
{
    mutex.lock();
    if(ui->radioManuel->isChecked()){
        request = Constants::REQ_CHANGE_MODE;
        message.clear();
        message.append(QString::number(request));
        message.append(Constants::DELIMITER);
        message.append(QString::number(1));
        ui->message_box->append("Manual mode selected...");
    }else if(ui->radioAutomatic->isChecked()){
        request = Constants::REQ_CHANGE_MODE;
        message.clear();
        message.append(QString::number(request));
        message.append(Constants::DELIMITER);
        message.append(QString::number(0));
        ui->message_box->append("Automatic mode selected...");
    }
    mutex.unlock();
}
