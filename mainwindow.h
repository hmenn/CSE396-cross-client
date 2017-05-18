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
#include <QTimer>
#include <QTime>
#include <QPixmap>

extern QByteArray arr;
extern int foundAngle;

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
    void setVPRouteArea();



    void printCoordinates(QGraphicsScene *scene);
    void drawStickMan(QGraphicsScene *scene, qreal X, qreal Y, qreal headRadius, qreal degree);

    bool TimerRunning;
    int hours, minutes, seconds;

    Ui::MainWindow *ui;
    ConnectionHelper *connH;

    QMutex mutex;
    char message [Constants::MIN_BUFFER_SIZE];
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
    QTimer *timer;


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
    void updateTime();
};

#endif // MAINWINDOW_H
