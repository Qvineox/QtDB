#include "addrecord.h"
#include "ui_addrecord.h"

addRecord::addRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addRecord)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    QSqlQuery* query = new QSqlQuery();
    query->exec("SELECT post FROM posts");

    while(query->next()) {
        ui->comboBox->addItem(query->value(0).toString());
    }

    postcombo = 0;
}

addRecord::~addRecord()
{
    delete ui;
}

void addRecord::on_pushButton_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("INSERT INTO characters1(name, surname, picPath, dat, mentor) VALUES(:name, :surname, :picPath, :dat, :mentor)");
    query->bindValue(":name", ui->lineEdit->text());
    query->bindValue(":surname", ui->lineEdit_2->text());
    query->bindValue(":picPath", imagePath);
    query->bindValue(":dat", ui->dateEdit->text());
    query->bindValue(":mentor", ui->comboBox->itemText(postcombo));

    QMessageBox* message = new QMessageBox();

    if (!query->exec()) {
        message->setText("Запрос не выполнен!");
    } else {
        message->setText("Запрос выполнен успешно!");
    }

    emit refresh_table();
    message->show();
    this->close();
}

void addRecord::on_toolButton_clicked()
{
    imagePath = QFileDialog::getOpenFileName(0, "Выберите изображение", "./", "*.jpg");
    ui->label_3->setScaledContents(true);
    ui->label_3->setPixmap(QPixmap(imagePath));
}

void addRecord::on_comboBox_currentIndexChanged(int index)
{
    postcombo = index;
}
