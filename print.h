#ifndef PRINT_H
#define PRINT_H

#include <QWidget>
#include <QAxObject>
#include <QSqlQuery>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class print;
}

class print : public QWidget
{
    Q_OBJECT

public:
    explicit print(QWidget *parent = nullptr);
    ~print();

private slots:
    void on_toolButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::print *ui;
};

#endif // PRINT_H
