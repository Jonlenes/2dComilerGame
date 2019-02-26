#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

    void newUser(QString hostName, int port, QString nome);

    void on_checkBox_clicked(bool checked);

private:
    Ui::MainWindow *ui;

    Server *server;
};

#endif // MAINWINDOW_H
