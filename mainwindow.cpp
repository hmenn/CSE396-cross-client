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

    connection = new Connection(ip, port);
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
        ip = ui->ledit_ip->text();
        connection=new Connection(ip);
    }catch(exception &e){

    }





}
