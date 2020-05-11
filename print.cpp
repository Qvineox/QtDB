#include "print.h"
#include "ui_print.h"

print::print(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::print)
{
    ui->setupUi(this);
}

print::~print()
{
    delete ui;
}

void print::on_toolButton_clicked()
{
    ui->lineEdit->setText(QFileDialog::getOpenFileName(0, "Выберите файл", "./", "*.html"));
}

void print::on_pushButton_clicked()
{
    QFile* file = new QFile();
    file->setFileName(ui->lineEdit->text());
    file->open(QIODevice::WriteOnly);

    QTextStream inputText(file);

    inputText<<"<html><head></head><body><center>" + QString("Пример создания отчета");
    inputText<<"<table border=1><tr>";
    inputText<<"<td>" + QString("Номер ID") + "</td>";
    inputText<<"<td>" + QString("Имя") + "</td>";
    inputText<<"<td>" + QString("Фамилия") + "</td></tr>";

    QSqlQuery* query = new QSqlQuery();
    query->exec("SELECT * FROM characters1");

    while (query->next()) {
        inputText<<"<tr><td>";
        inputText<<query->value(0).toString();
        inputText<<"/td><td>";
        inputText<<query->value(1).toString();
        inputText<<"/td><td>";
        inputText<<query->value(2).toString();
        inputText<<"/td></tr>";
    }

    inputText<<"</table></center></body></html>";
    file->close();

    QAxObject* word = new QAxObject("Word.Application", this);
    word->setProperty("DisplayAlerts", false);
    word->setProperty("Visible", true);

    QAxObject* doc = word->querySubObject("Documents");
    doc->dynamicCall("Open(QVariant)", ui->lineEdit->text());



}
