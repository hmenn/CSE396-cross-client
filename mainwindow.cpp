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
    disableUI();

    /* Connection part */
    connection=NULL;

    /* initialize connection thread */
    comThread = new CommunicationThread(this);
    comThread->mutex = &mutex;
    comThread->request = &request;
    comThread->message = &message;

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
        comThread->connection = connection;
        connection->sendRequest("Hello Clion");
        connection->readRequest();
       // comThread->start();

        enableUI();
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

    disableUI();
}
