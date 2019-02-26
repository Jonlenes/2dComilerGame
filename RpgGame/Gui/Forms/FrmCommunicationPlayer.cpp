#include "FrmCommunicationPlayer.h"
#include "ui_FrmCommunicationPlayer.h"

#include "../../Client/Client.h"

FrmCommunicationPlayer::FrmCommunicationPlayer(QWidget *parent, QString name) :
    QDialog(parent), nameUserRequest(name),
    ui(new Ui::FrmCommunicationPlayer)
{
    ui->setupUi(this);
    setWindowTitle(nameUserRequest);
}

FrmCommunicationPlayer::~FrmCommunicationPlayer()
{
    delete ui;
}

void FrmCommunicationPlayer::on_pushButtonNewGame_clicked()
{
    Cliente::getInstanse()->makeRequestNewGame(nameUserRequest);
    close();
}
