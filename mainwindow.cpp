#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), SLOT(CustomMenu(QPoint)));
    flag = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    logWin = new login();
    logWin->show();
}

void MainWindow::on_pushButton_clicked()
{
    flag = 1;
    model = new QSqlQueryModel();
    model->setQuery("SELECT id, name, surname, mentor, dat, picPath FROM characters1");

    model->setHeaderData(0,Qt::Horizontal,"id");
    model->setHeaderData(1,Qt::Horizontal,"Имя");
    model->setHeaderData(2,Qt::Horizontal,"Фамилия");
    model->setHeaderData(3,Qt::Horizontal,"Ментор");
    model->setHeaderData(4,Qt::Horizontal,"Дата рождения");
    model->setHeaderData(5,Qt::Horizontal,"Картинка");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    ui->tableView->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    newRecord = new addRecord();
    connect(newRecord, SIGNAL(refresh_table()), SLOT(table_refresh_handler()));
    newRecord->show();
}

void MainWindow::table_refresh_handler() {
    on_pushButton_clicked();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int clickedId;
    clickedId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();

    ui->lineEdit_id->setText(QString::number(clickedId));

    QSqlQuery* query = new QSqlQuery();
    query->prepare("SELECT name, surname, mentor, dat, picPath FROM characters1 WHERE id=:id");
    query->bindValue(":id", clickedId);

    if (query->exec()) {
        query->next();
        ui->lineEdit_name->setText(query->value(0).toString());
        ui->lineEdit_surname->setText(query->value(1).toString());
        ui->lineEdit_mentor->setText(query->value(2).toString());
        ui->label_4->setScaledContents(true);
        ui->label_4->setPixmap(QPixmap(query->value(4).toString()));
        ui->dateEdit->setDate(QDate(query->value(3).toDate()));

    }

}

void MainWindow::on_pushButton_4_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("UPDATE characters1 SET name=?, surname=?, mentor=?, dat=? WHERE id=?");
    query->bindValue(0, ui->lineEdit_name->text());
    query->bindValue(1, ui->lineEdit_surname->text());
    query->bindValue(2, ui->lineEdit_mentor->text());
    query->bindValue(3, ui->dateEdit->text());
    query->bindValue(4, ui->lineEdit_id->text());

    if (query->exec()) {
        on_pushButton_clicked();
    }

}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("DELETE FROM characters1 WHERE id=?");
    query->bindValue(0, ui->lineEdit_id->text());

    if (query->exec()) {
        on_pushButton_clicked();
    }
}

void MainWindow::CustomMenu(QPoint pos) {
    if (flag == 1) {
        QModelIndex index = ui->tableView->indexAt(pos);
        globalId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();

        QMenu* menu = new QMenu(this);
        QAction* edit = new QAction("Изменить", this);
        QAction* del = new QAction("Удалить", this);

        connect(del, SIGNAL(triggered()), this, SLOT(delRecord()));
        connect(edit, SIGNAL(triggered()), this, SLOT(reconfRecord()));

        menu->addAction(edit);
        menu->addAction(del);

        menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::delRecord() {
    QSqlQuery* query = new QSqlQuery();
    query->prepare("DELETE FROM characters1 WHERE id=?");
    query->bindValue(0, globalId);

    if (query->exec()) {
        on_pushButton_clicked();
    }
}

void MainWindow::reconfRecord() {
    existingRecord = new editRecord();
    connect(this, SIGNAL(sendId(int)), existingRecord, SLOT(editSentId(int)));
    emit sendId(globalId);

    existingRecord->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    printRecords = new print();
    QSqlQuery* query = new QSqlQuery();
    query->prepare("");

    printRecords->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    QString str;

    str.append("<html><head></head><body><center>" + QString("Пример создания отчета"));
    str.append("<table border=1><tr>");
    str.append("<td>" + QString("Номер ID") + "</td>");
    str.append("<td>" + QString("Имя") + "</td>");
    str.append("<td>" + QString("Фамилия") + "</td></tr>");

    QSqlQuery* query = new QSqlQuery();
    query->exec("SELECT * FROM characters1");

    while (query->next()) {
        str.append("<tr><td>");
        str.append(query->value(0).toString());
        str.append("/td><td>");
        str.append(query->value(1).toString());
        str.append("/td><td>");
        str.append(query->value(2).toString());
        str.append("/td></tr>");
    }

    str.append("</table></center></body></html>");

    QPrinter printer;
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);

    QString path = QFileDialog::getSaveFileName(NULL, "Сохранить PDF как", "Отчет", "PDF (*.pdf)");
    if (path.isEmpty()) return;

    printer.setOutputFileName(path);
    QTextDocument doc;

    doc.setHtml(str);
    doc.print(&printer);
}

void MainWindow::on_action_2_triggered()
{
    printGraph = new printgraph();
    printGraph->show();
}
