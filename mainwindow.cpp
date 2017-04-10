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

    /* initialize connection thread */
    comThread = new CommunicationThread(this);
    comThread->mutex = &mutex;
    comThread->request = &request;
    comThread->message = &message;
    comThread->connection = connection;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete connection;
    delete comThread;
}


void MainWindow::on_btn_conn_clicked(){
    QString ip;
    ui->btn_conn->setEnabled(false);

    try{
        //throw InvalidConnectionException();
        ip = ui->ledit_ip->text();
        connection=new Connection("bogotobogo.com");
        comThread->start();
    }catch(exception &e){
        qDebug()<<e.what();
        ui->tb_messages->append(e.what());
        ui->btn_conn->setEnabled(true);
    }

}
