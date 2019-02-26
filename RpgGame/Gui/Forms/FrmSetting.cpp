#include "FrmSetting.h"
#include "ui_FrmSetting.h"
#include "Client/Client.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>

bool FrmSetting::useCompiler = false;
QString FrmSetting::serverName = "";
int FrmSetting::serverPort = 0;

FrmSetting::FrmSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmSetting)
{
    ui->setupUi(this);

    ui->checkBoxUseCompiler->setChecked(useCompiler);
    ui->lineEditPath->setText(serverName);
    ui->lineEditPort->setText(QString::number(serverPort));

}

FrmSetting::~FrmSetting()
{
    delete ui;
}

void FrmSetting::on_pushButtonOk_clicked()
{
    serverName = ui->lineEditPath->text();
    serverPort = ui->lineEditPort->text().toInt();
    useCompiler = ui->checkBoxUseCompiler->isChecked();

    writeSetting();
    readSetting();
    close();
}

void FrmSetting::readSetting()
{
    QFile file("setting.xml");

    if (file.open(QFile::ReadOnly)) {
        QXmlStreamReader xmlReader(file.readAll());

        xmlReader.readNextStartElement();

        xmlReader.readNextStartElement();
        useCompiler = xmlReader.readElementText().toInt();

        xmlReader.readNextStartElement();
        serverName = xmlReader.readElementText();

        xmlReader.readNextStartElement();
        serverPort = xmlReader.readElementText().toInt();
    }
}

void FrmSetting::writeSetting()
{

    QString xml;
    QXmlStreamWriter xmlWriter(&xml);

    xmlWriter.writeStartElement("Setting");
    xmlWriter.writeTextElement("useCompiler", QString::number(useCompiler));
    xmlWriter.writeTextElement("serverName", serverName);
    xmlWriter.writeTextElement("serverPort", QString::number(serverPort));
    xmlWriter.writeEndElement();

    QFile file("setting.xml");
    file.open(QFile::WriteOnly);

    QTextStream stream(&file);
    stream << xml;
    file.close();
}

void FrmSetting::on_pushButtonConnect_clicked()
{
    try {
        Cliente::getInstanse()->connectToHost(ui->lineEditPath->text(), ui->lineEditPort->text().toInt(), 5000);
        on_pushButtonOk_clicked();
    }  catch (QString &e) {
        //"192.168.25.240", 10,
        QMessageBox::information(this, "Erro", e);
    }
}
