#ifndef FRMSELECTPLAYER_H
#define FRMSELECTPLAYER_H

#include <QDialog>

namespace Ui {
class FrmSelectPlayer;
}

class FrmSelectPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit FrmSelectPlayer(QWidget *parent = 0);
    ~FrmSelectPlayer();

private:
    Ui::FrmSelectPlayer *ui;
};

#endif // FRMSELECTPLAYER_H
