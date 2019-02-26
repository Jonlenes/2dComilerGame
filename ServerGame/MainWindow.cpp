#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QXmlStreamReader>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(width(), height());
    ui->lineEditAddress->setEnabled(false);
    ui->pushButtonStop->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonStart_clicked()
{
    QString strAddress = ui->lineEditAddress->text();
    int port = ui->lineEditPort->text().isEmpty()? 10 :  ui->lineEditPort->text().toInt();
    QHostAddress hostAddress;

    if (strAddress.isEmpty())
        hostAddress = QHostAddress::LocalHost;
    else
        hostAddress = QHostAddress(strAddress);

    server = new Server(hostAddress, port);

    ui->lineEditAddress->setEnabled(false);
    ui->lineEditPort->setEnabled(false);

    ui->lineEditAddress->setText(server->serverAddress().toString());
    ui->lineEditPort->setText(QString::number(server->serverPort()));

    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonStop->setEnabled(true);
    ui->lineEditPort->setEnabled(false);

    ui->tableWidget->setRowCount(0);
    connect(server, SIGNAL(newUser(QString,int,QString)), this, SLOT(newUser(QString,int,QString)));
}

void MainWindow::on_pushButtonStop_clicked()
{
    delete server;

    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);
    ui->lineEditPort->setEnabled(true);
}

void MainWindow::newUser(QString hostName, int port, QString nome)
{
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        if (ui->tableWidget->item(i, 0)->text() == hostName &&
                ui->tableWidget->item(i, 1)->text().toInt() == port) {
            ui->tableWidget->item(i, 2)->setText(nome);
            return;
        }
    }

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(hostName));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::number(port)));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(nome));
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    setFixedHeight((checked? 370 : 100));
}
