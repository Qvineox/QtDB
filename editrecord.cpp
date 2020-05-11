#include "editrecord.h"
#include "ui_editrecord.h"

#include "mainwindow.h"

editRecord::editRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editRecord)
{
    ui->setupUi(this);
}

editRecord::~editRecord()
{
    delete ui;
}

void editRecord::editSentId(int id) {
    QSqlQuery* query = new QSqlQuery();
    query->prepare("SELECT name, surname FROM characters1 WHERE id=?");
    query->bindValue(0, id);

    if (query->exec()) {
        query->next();
        ui->lineEdit->setText(query->value(0).toString());
        ui->lineEdit_2->setText(query->value(1).toString());
        ui->lineEdit_3->setText(QString::number(id));
    }

}

void editRecord::on_pushButton_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("UPDATE characters1 SET name=?, surname=? WHERE id=?");
    query->bindValue(0, ui->lineEdit->text());
    query->bindValue(1, ui->lineEdit_2->text());
    query->bindValue(2, ui->lineEdit_3->text().toInt());

    if (query->exec()) {
        this->close();
        connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(triggered()));
    }
}
