#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    message = new QMessageBox();

}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server};SERVER=" + ui->lineEdit->text() + ";DATABASE=" + ui->lineEdit_2->text() + ";");
    db.setUserName(ui->lineEdit_3->text());
    db.setPassword(ui->lineEdit_4->text());

    if(db.open()) {
        message->setText("Соединение установлено успешно!");
        message->show();
        this->close();

    } else {
        message->setText("Установить соединение не удалось!");
        message->show();
    }

}

void login::on_pushButton_2_clicked()
{
    ui->lineEdit->setText("DESKTOP-4FC4H9A\\SQLEXPRESS");
    ui->lineEdit_2->setText("QtDataBase");
    ui->lineEdit_3->setText("Yaroslav");
}
