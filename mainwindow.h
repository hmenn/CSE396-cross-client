#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsLineItem>
#include <QMainWindow>
#include <QMutex>
#include <QKeyEvent>
#include <QSignalMapper>
#include "communicationthread.h"
#include "connection.h"
#include "requirements.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void disableUI();
    void enableUI();
    void setPathPlot(QGraphicsScene *scene, QPoint *posCurrent, QPoint posNext);
    void keyPressEvent(QKeyEvent *event);
    void closeEvent (QCloseEvent *event);


    Ui::MainWindow *ui;
    Connection *connection;

    //QChar data[10];
    QMutex mutex;
    QString message;
    int request;

    CommunicationThread *comThread;

    QString ip;
    QString port;
    int requestType;

    int xCoor;
    int yCoor;

    // path frames
    QGraphicsScene *scene;
    QGraphicsLineItem *pathLine;
    QPoint *curr;
    QPoint *next;

private slots:
    void help();
    void updateCoordinates();
    void on_btn_conn_clicked();
    void on_btn_disconn_clicked();
    void on_xNegative_clicked();
    void on_xPositive_clicked();
    void on_yPositive_clicked();
    void on_yNegative_clicked();
    void on_sendButton_clicked();
    void on_startButton_clicked();
    void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H
