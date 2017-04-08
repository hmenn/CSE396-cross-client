#include <iostream>
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
    std::cout<<"conn";
}
