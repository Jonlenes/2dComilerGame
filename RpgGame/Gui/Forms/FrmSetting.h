#ifndef FRMSETTING_H
#define FRMSETTING_H

#include <QDialog>

namespace Ui {
class FrmSetting;
}

class FrmSetting : public QDialog
{
    Q_OBJECT

public:
    explicit FrmSetting(QWidget *parent = 0);
    ~FrmSetting();

    static bool useCompiler;
    static QString serverName;
    static int serverPort;

    static void readSetting();
    static void writeSetting();

private slots:
    void on_pushButtonOk_clicked();

    void on_pushButtonConnect_clicked();

private:
    Ui::FrmSetting *ui;

};

#endif // FRMSETTING_H
