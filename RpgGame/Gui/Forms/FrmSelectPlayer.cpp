#include "FrmSelectPlayer.h"
#include "ui_FrmSelectPlayer.h"

FrmSelectPlayer::FrmSelectPlayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmSelectPlayer)
{
    ui->setupUi(this);
}

FrmSelectPlayer::~FrmSelectPlayer()
{
    delete ui;
}
