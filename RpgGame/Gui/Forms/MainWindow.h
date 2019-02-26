#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Client/Client.h"
#include "../ServerGame/XMLClasses/Players.h"
#include <QMainWindow>

#include <vector>
using namespace std;

namespace Ui {
class MainWindow;
}

class QListWidgetItem;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotConnected();
    void slotSetUserList(Players players);
    void slotAddUser(QString name);
    void slotRemoveUser(QString name);
    void slotAcceptedName();
    void slotNewAlertUser(QString text);
    void slotPlayRequest(QString name);
    void slotNewFightStarted(QString name1, QString name2);
    void slotFightFinalized(QString name1, QString);
    void startNewGame(int index);

    void on_pushButtonQuit_clicked();

    void on_pushButtonSendName_clicked();

    void on_listWidgetPlayer_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    vector<QWidget *> listWidget;

    void initGui();
    void setwidgetVisible(int index);
};

#endif // MAINWINDOW_H
