#include <iostream>
#include <QProgressBar>
#include <QProgressDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btn_disconn->setEnabled(false);

    /* Connection part */
    connection=NULL;

    /* initialize connection thread */
    comThread = new CommunicationThread(this);
    comThread->mutex = &mutex;
    comThread->request = &request;
    comThread->message = &message;

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
    ui->btn_conn->setEnabled(false);
    ui->btn_disconn->setEnabled(true);

    try{
        //throw InvalidConnectionException();
        ip = ui->ledit_ip->text();
        connection=new Connection("127.0.0.1");
        comThread->connection = connection;
        connection->sendRequest("Hello Clion");
       // comThread->start();
    }catch(exception &e){
        qDebug()<<e.what();
        ui->tb_messages->append(e.what());
        ui->btn_conn->setEnabled(true);
    }
}

void MainWindow::on_btn_disconn_clicked(){

    if(connection!=NULL){
        delete connection;
        connection=NULL;
    }
    ui->btn_disconn->setEnabled(false);
    ui->btn_conn->setEnabled(true);
}
