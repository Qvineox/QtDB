#ifndef ADDRECORD_H
#define ADDRECORD_H

#include <QWidget>

#include <QMessageBox>
#include <QSqlQuery>

#include <QFileDialog>

namespace Ui {
class addRecord;
}

class addRecord : public QWidget
{
    Q_OBJECT

public:
    explicit addRecord(QWidget *parent = nullptr);
    ~addRecord();

    QString imagePath;
    int postcombo;

private slots:
    void on_pushButton_clicked();

    void on_toolButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

signals:
    void refresh_table();

private:
    Ui::addRecord *ui;
};

#endif // ADDRECORD_H
