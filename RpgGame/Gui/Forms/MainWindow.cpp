#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "../ServerGame/XMLClasses/NamePlayer.h"
#include "Gui/Forms/FrmCommunicationPlayer.h"
#include "Gui/Views/GraphicsViewGame.h"
#include "Gui/Forms/FrmSetting.h"

#include <QMessageBox>

enum ListWidget {
    WidConnection,
    WidResumePlayers
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initGui();

    connect(Cliente::getInstanse(), SIGNAL(connected()), this, SLOT(slotConnected()));
    connect(Cliente::getInstanse(), SIGNAL(signalSetUserList(Players)), this, SLOT(slotSetUserList(Players)));
    connect(Cliente::getInstanse(), SIGNAL(signalNewUser(QString)), this, SLOT(slotAddUser(QString)));
    connect(Cliente::getInstanse(), SIGNAL(signalUserDisconnected(QString)), this, SLOT(slotRemoveUser(QString)));
    connect(Cliente::getInstanse(), SIGNAL(signalAcceptedName()), this, SLOT(slotAcceptedName()));
    connect(Cliente::getInstanse(), SIGNAL(signalPlayRequest(QString)), this, SLOT(slotPlayRequest(QString)));
    connect(Cliente::getInstanse(), SIGNAL(signalNewFightStarted(QString,QString)), this, SLOT(slotNewFightStarted(QString,QString)));
    connect(Cliente::getInstanse(), SIGNAL(signalFightFinalized(QString,QString)), this, SLOT(slotFightFinalized(QString,QString)));
    connect(Cliente::getInstanse(), SIGNAL(signalGameAccept(int)), this, SLOT(startNewGame(int)));

    FrmSetting::readSetting();

    try {     
        Cliente::getInstanse()->connectToHost(FrmSetting::serverName, FrmSetting::serverPort, 5000);
    } catch (QString &e) {
        QMessageBox::information(nullptr, "Erro", e);

        FrmSetting frmSetting(nullptr);
        frmSetting.exec();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startNewGame(int index)
{
    GraphicsViewGame *viewGame = new GraphicsViewGame(nullptr, index);
    viewGame->showFullScreen();
}

void MainWindow::slotConnected()
{
    setwidgetVisible(WidResumePlayers);
}

void MainWindow::on_pushButtonQuit_clicked()
{
    close();
}

void MainWindow::initGui()
{
    listWidget.push_back(ui->widgetConnection);
    listWidget.push_back(ui->widgetResumePlayers);

    setwidgetVisible(WidConnection);

    ui->tableWidgetFight->setStyleSheet("QHeaderView::section { background-color:black }");
    ui->tableWidgetFight->horizontalHeader()->setStyleSheet("color:#d60000");
}

void MainWindow::setwidgetVisible(int index)
{
    for (auto i : listWidget)
        i->setVisible(false);

    listWidget[index]->setVisible(true);
}

void MainWindow::slotSetUserList(Players players)
{
    ui->listWidgetPlayer->clear();
    ui->tableWidgetFight->setRowCount(0);

    for (auto i : players.listUsers)
        ui->listWidgetPlayer->addItem(i.name);

    for (auto i : players.listFightsActive)
        slotNewFightStarted(players.listUsers[i.first].name, players.listUsers[i.second].name);
}

void MainWindow::slotAddUser(QString name)
{
    int i = 0;
    for (; i < ui->listWidgetPlayer->count(); ++i)
        if (ui->listWidgetPlayer->item(i)->text() == name)
            break;

    if (i < ui->listWidgetPlayer->count()) {
        QListWidgetItem *item = ui->listWidgetPlayer->item(i);
        //Atualiza o item
    } else {
        ui->listWidgetPlayer->addItem(name);
    }
}

void MainWindow::slotRemoveUser(QString name)
{
    int i = 0;

    for (; i < ui->listWidgetPlayer->count(); ++i)
        if (ui->listWidgetPlayer->item(i)->text() == name)
            break;

    delete (ui->listWidgetPlayer->takeItem(i));
}

void MainWindow::slotAcceptedName()
{
    Cliente::getInstanse()->setName(ui->lineEditName->text());
    ui->widgetInsertName->setVisible(false);
}

void MainWindow::slotNewAlertUser(QString text)
{
    QMessageBox::information(this, "Aviso", text);
}

void MainWindow::slotPlayRequest(QString name)
{
    QMessageBox messageBox(nullptr);

    messageBox.setText(name + " está te chamando para jogar.");
    QPushButton *acceptButton = messageBox.addButton("Aceitar", QMessageBox::AcceptRole);
    messageBox.addButton("Recusar", QMessageBox::RejectRole);

    messageBox.exec();
    if (messageBox.clickedButton() == acceptButton) {
        qDebug() << "Resposta positiva a request";
        Cliente::getInstanse()->responseNewGamePending(true);
        qDebug() << "Enviou o acc para o servidor";
        startNewGame(0);
        qDebug() << "Startou game";
    }
}

void MainWindow::slotNewFightStarted(QString name1, QString name2)
{
    ui->tableWidgetFight->insertRow(ui->tableWidgetFight->rowCount());
    ui->tableWidgetFight->setItem(ui->tableWidgetFight->rowCount() - 1, 0, new QTableWidgetItem(name1));
    ui->tableWidgetFight->setItem(ui->tableWidgetFight->rowCount() - 1, 1, new QTableWidgetItem("X"));
    ui->tableWidgetFight->setItem(ui->tableWidgetFight->rowCount() - 1, 2, new QTableWidgetItem(name2));
}

void MainWindow::slotFightFinalized(QString name1, QString)
{
    int i = 0;

    for (; i < ui->tableWidgetFight->rowCount(); ++i)
        if (ui->tableWidgetFight->item(i, 0)->text() == name1)
            break;

    ui->tableWidgetFight->removeRow(i);
}


void MainWindow::on_pushButtonSendName_clicked()
{
    if (ui->lineEditName->text().isEmpty()) {
        slotNewAlertUser("O nome não pode ser vazio.");
        return;
    }

    ui->lineEditName->setEnabled(false);

    NamePlayer namePlayer(ui->lineEditName->text());
    Cliente::getInstanse()->sendMessege(namePlayer.toXML());
}

void MainWindow::on_listWidgetPlayer_itemClicked(QListWidgetItem *item)
{
    FrmCommunicationPlayer frmCommunicationPlayer(nullptr, item->text());
    frmCommunicationPlayer.show();
    frmCommunicationPlayer.exec();
}

void MainWindow::on_pushButton_clicked()
{
    FrmSetting frmSetting(nullptr);
    frmSetting.exec();
}
