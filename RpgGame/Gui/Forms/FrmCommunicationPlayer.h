#ifndef FRMCOMMUNICATIONPLAYER_H
#define FRMCOMMUNICATIONPLAYER_H

#include <QDialog>

namespace Ui {
class FrmCommunicationPlayer;
}

class FrmCommunicationPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit FrmCommunicationPlayer(QWidget *parent, QString name);
    ~FrmCommunicationPlayer();

private slots:
    void on_pushButtonNewGame_clicked();

private:
    Ui::FrmCommunicationPlayer *ui;
    QString nameUserRequest;
};

#endif // FRMCOMMUNICATIONPLAYER_H
