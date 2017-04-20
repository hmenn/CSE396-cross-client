#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>
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


private slots:
    void on_btn_conn_clicked();
    void on_btn_disconn_clicked();
};

#endif // MAINWINDOW_H
