#ifndef EDITRECORD_H
#define EDITRECORD_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class editRecord;
}

class editRecord : public QWidget
{
    Q_OBJECT

public:
    explicit editRecord(QWidget *parent = nullptr);
    ~editRecord();

private slots:
    void editSentId(int);

    void on_pushButton_clicked();

private:
    Ui::editRecord *ui;
};

#endif // EDITRECORD_H
