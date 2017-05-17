#include <iostream>
#include <QProgressBar>
#include <QProgressDialog>
#include <QMessageBox>
#include <unistd.h>
#include <stdlib.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "requirements.h"
#include "communicationthread.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedHeight(800);
    this->setFixedWidth(1050);
    setWindowTitle("CSE 396 Project II");

    disableUI();

    xCoor =0;
    yCoor =0;

    /* Connection part */
    connection=NULL;

    QImage logo(":/images/gtuLogo500.png");
    ui->gtuLogo->setPixmap(QPixmap::fromImage(logo.scaled(350,150)));


    ui->xCoordinate->setReadOnly(true);
    ui->yCoordinate->setReadOnly(true);

    curr = new QPoint(0, 0);
    next = new QPoint(0, 0);

    // 0, 0 Upper Left of the w
    scene = new QGraphicsScene(0,0,445,305);
    ui->vp_route->setScene(scene);

    QPen blackPen(QColor(50,50,50));
    blackPen.setWidthF(0.2);

    // Divide the paper into 8 parts
    scene->addLine(0,153,445,153,blackPen);
    scene->addLine(226,0,226,305,blackPen);
    scene->addLine(113,0,113,305,blackPen);
    scene->addLine(339,0,339,305,blackPen);

    printCoordinates(scene);

    //drawStickMan(scene, 80, 80, 20, 0);
    //drawStickMan(scene, 150, 80, 20, 90);
}

void MainWindow::drawStickMan(QGraphicsScene *scene, qreal X, qreal Y, qreal headRadius, qreal degree){
    QPen pen(QColor(0, 0, 0));
    pen.setWidthF(2.0);
    QPen greenPen(QColor(0, 255, 0));
    greenPen.setWidthF(2.0);

    // Find the center coordinates of the head
    qreal circleX = X-headRadius/2;
    qreal circleY = Y-headRadius/2;
    qreal lineLength = (headRadius/10)*15;
    qreal radian = (degree*PI)/180.0;

    // Draw the head with center (X, Y)
    scene->addEllipse(circleX, circleY, headRadius, headRadius, pen);




    // Calculate the body line
    qreal bSxD, bSyD, bFxD, bFyD;

    if(degree == 0 || degree == 90){
        bSxD = (X + headRadius/2) - cos(radian)*headRadius/2;
        bSyD = (Y + headRadius/2) - sin(radian)*headRadius/2;
    }
    else if(degree < 90 && degree >0){
         bSxD = (X + headRadius/1.4) - cos(radian)*headRadius/2;
         bSyD = (Y + headRadius/1.4) - sin(radian)*headRadius/2;
    }
    else if(degree == 180){
        bSxD = (X + headRadius/2) + cos(radian)*headRadius/2;
        bSyD = (Y - headRadius/2) + sin(radian)*headRadius/2;
    }
    else if(degree < 180 && degree >=91){
        bSxD = (X + headRadius/1.4) + cos(radian)*headRadius/2;
        bSyD = (Y - headRadius/1.4) + sin(radian)*headRadius/2;
    }
    else if(degree == 270){
        bSxD = (X - headRadius/2) - cos(radian)*headRadius/2;
        bSyD = (Y - headRadius/2) - sin(radian)*headRadius/2;
    }
    else if(degree < 270 && degree >=181){
        bSxD = (X - headRadius/1.4) - cos(radian)*headRadius/2;
        bSyD = (Y - headRadius/1.4) - sin(radian)*headRadius/2;
    }
    else if(degree < 360 && degree >= 271){
        bSxD = (X - headRadius/1.4) + cos(radian)*headRadius/2;
        bSyD = (Y + headRadius/1.4) + sin(radian)*headRadius/2;
    }

    bFxD = sin(radian)*lineLength + bSxD;
    bFyD = cos(radian)*lineLength + bSyD;

    // Draw the body line
    scene->addLine(bSxD, bSyD, bFxD, bFyD, greenPen);

    // Hands
    qreal handSx = bSxD;
    qreal handSy = bSyD;

    qreal handF1x = sin(radian-45*PI/180)*lineLength/2 + bSxD;
    qreal handF1y = cos(radian-45*PI/180)*lineLength/2 + bSyD;
    qreal handF2x = sin(radian+45*PI/180)*lineLength/2 + bSxD;
    qreal handF2y = cos(radian+45*PI/180)*lineLength/2 + bSyD;

    // Draw the hands
    scene->addLine(handSx, handSy, handF1x, handF1y, greenPen);
    scene->addLine(handSx, handSy, handF2x, handF2y, greenPen);


    // Legs
    qreal legSx = bFxD;
    qreal legSy = bFyD;

    qreal legF1x = sin(radian-45*PI/180)*lineLength/2 + legSx;
    qreal legF1y = cos(radian-45*PI/180)*lineLength/2 + legSy;
    qreal legF2x =  sin(radian+45*PI/180)*lineLength/2 + legSx;
    qreal legF2y = cos(radian+45*PI/180)*lineLength/2 + legSy;

    // Draw the legs
    scene->addLine(legSx, legSy, legF1x, legF1y, greenPen);
    scene->addLine(legSx, legSy, legF2x, legF2y, greenPen);

    /*
    std::cerr << "Kollar:" << std::endl;
    std::cerr << handSx << " -- " << handSy << std::endl;
    std::cerr << handF1x << " == " << handF1y << std::endl;

    std::cerr << handSx << " -- " << handSy << std::endl;
    std::cerr << handF2x << " == " << handF2y << std::endl;

    std::cerr << "Ayaklar:" << std::endl;
    std::cerr << legSx << " -- " << legSy << std::endl;
    std::cerr << legF1x << " == " << legF1y << std::endl;

    std::cerr << legSx << " -- " << legSy << std::endl;
    std::cerr << legF2x << " == " << legF2y << std::endl;
    */

}

void MainWindow::printCoordinates(QGraphicsScene *scene){
    QPen bluePen(QColor(0, 0, 255));
    bluePen.setWidthF(1.0);

    QPen redPen(QColor(255, 0, 0));
    redPen.setWidthF(1.0);

    // Print X coordinates
    int longLine;
    for(int i=0; i<450; i+=5){
       if(i%20 == 0 && i!=0)
           longLine = 20;
       else
           longLine = 5;

       scene->addLine(i, 0, i, longLine, bluePen);
    }

    // Print Y coordinates
    for(int i=0; i<310; i+=5){
        if(i%20 == 0 && i!=0)
          longLine = 20;
        else
          longLine = 5;

        scene->addLine(0, i, longLine, i, redPen);
    }
}


void MainWindow::help(){
    qDebug()<<"Help";
}

void MainWindow::setPathPlot(QGraphicsScene *scene, QPoint *posCurrent, QPoint posNext){

    QPen pen(QColor(200,0,0));
    pen.setWidthF(0.8);
    QBrush redBrush(QColor(200,0,0));

     scene->addLine(posCurrent->x()/2, posCurrent->y()/2, posNext.x()/2, posCurrent->y()/2, pen);
    posCurrent->setX(posNext.x());
    scene->addLine(posCurrent->x()/2, posCurrent->y()/2, posNext.x()/2, posNext.y()/2, pen);
    posCurrent->setY(posNext.y());

    scene->addEllipse(posNext.x()/2, posNext.y()/2, 2, 2, pen, redBrush);
}

void MainWindow::updateCoordinates(){
    ui->xCoordinate->setText(QString::number(xCoor));
    ui->yCoordinate->setText(QString::number(yCoor));
//haritalama
    next->setX(xCoor);
    next->setY(yCoor);
    // Draw a line between the curr and next points
   setPathPlot(scene, curr, *next);
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

    ui->grp_steps->setEnabled(false);
    ui->grp_system->setEnabled(true);

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

        xCoor=0;
        yCoor=0;

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

        connection->sendRequest("H");
        QString *str;
        do{
            sleep(1);
        QByteArray arr;
        connection->readRequest(&arr);
        str = new QString(arr);
        qDebug()<<str;

        }while (strcmp(str->toStdString().c_str(),"S")!=0);
        qDebug()<<"HandShake complete!"<<endl;

        comThread->start();

        ui->radioManuel->setChecked(false);
        ui->radioAutomatic->setChecked(true);
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
    message.append("20");
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
    message.append("-20");
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
    message.append("20");
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
    message.append("-20");
    mutex.unlock();
}

void MainWindow::on_sendButton_clicked()
{
    mutex.lock();
    request = Constants::REQ_UPDATE_COORDS;
    message.clear();
    message.append(QString::number(request));
    // take x coordinate
    message.append(Constants::DELIMITER);
    if(ui->ledit_stepX->text().isEmpty())

        message.append("0");
    else
        message.append(ui->ledit_stepX->text());
    // take y coordinate
    message.append(Constants::DELIMITER);

    if(ui->ledit_stepY->text().isEmpty())
        message.append("0");
    else
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
        ui->grp_steps->setEnabled(true);
    }else if(ui->radioAutomatic->isChecked()){
        request = Constants::REQ_CHANGE_MODE;
        message.clear();
        message.append(QString::number(request));
        message.append(Constants::DELIMITER);
        message.append(QString::number(0));
        ui->message_box->append("Automatic mode selected...");
        ui->grp_steps->setEnabled(false);
    }
    mutex.unlock();
}

void MainWindow::keyPressEvent(QKeyEvent *event){

    if(ui->grp_steps->isEnabled() && ui->keyboardCheckBox->isChecked()){
        if(event->key() == Qt::Key_W){
            on_yPositive_clicked();
        }else if(event->key() == Qt::Key_S){
            on_yNegative_clicked();
        }else if(event->key() == Qt::Key_A){
            on_xNegative_clicked();
        }else if(event->key() == Qt::Key_D){
            on_xPositive_clicked();
        }else if(event->key() == Qt::Key_Backspace){
            mutex.lock();
            request = Constants::REQ_UPDATE_COORDS;
            message.clear();
            message.append(QString::number(request));
            message.append(Constants::DELIMITER);
            message.append("-1000");
            message.append(Constants::DELIMITER);
            message.append("-1000");
            mutex.unlock();
        }
    }
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "CSE396 Client",
                                                                tr("Are you sure?\n"),QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        this->on_btn_disconn_clicked();
        qDebug()<<"Successfully closed!!";
    }
}



void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"Group 5 Members","0.Hasan Men\n1.Ahmet Alperen Bulut\n2.İsa Eş\n3.Recep Sivri\n4.Furkan Erdöl\n5.Onur Sezer\n6.Helin Yıldırım\n7.Mehmed Mustafa");
}
