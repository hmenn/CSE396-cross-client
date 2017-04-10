#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    Ui::MainWindow *ui;
    Connection *connection;

    QMutex mutex;
    QString message;
    int request;

    CommunicationThread *comThread;
    Connection *connection;

    QString ip;
    QString port;

    RequestType requestType;


private slots:
    void on_btn_conn_clicked();
};

#endif // MAINWINDOW_H
