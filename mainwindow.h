#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>

#include <QSqlTableModel>
#include <QSqlQueryModel>

#include "login.h"
#include "ui_login.h"

#include "addrecord.h"
#include "ui_addRecord.h"

#include "editrecord.h"
#include "ui_editrecord.h"

#include "print.h"
#include "ui_print.h"

#include "printgraph.h"
#include "ui_printgraph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    login* logWin;
    addRecord* newRecord;
    editRecord* existingRecord;
    print* printRecords;
    printgraph* printGraph;

    int globalId;
    int flag;


private slots:
    void on_action_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void table_refresh_handler();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void CustomMenu(QPoint);

    void delRecord();

    void reconfRecord();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_action_2_triggered();

signals:

    void sendId(int);

private:
    Ui::MainWindow *ui;
    //QSqlTableModel* model;
    QSqlQueryModel *model;
};
#endif // MAINWINDOW_H
