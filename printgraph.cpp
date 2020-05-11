#include "printgraph.h"
#include "ui_printgraph.h"

printgraph::printgraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::printgraph)
{
    ui->setupUi(this);

    ui->widget->plotLayout()->insertRow(0);
    ui->widget->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget, "График выручки"));

    QVector<double> dx, dy;

    double minX, minY, maxX, maxY;
    minX = 0;
    minY = 0;
    maxX = 0;
    maxY = 0;

    QSqlQuery* query = new QSqlQuery();
    if (query->exec("SELECT * FROM chart")) {
        while (query->next()) {
            if (minX >= query->value(0).toDouble()) minX = query->value(0).toDouble();
            if (minY >= query->value(1).toDouble()) minY = query->value(1).toDouble();
            if (maxX <= query->value(0).toDouble()) maxX = query->value(0).toDouble();
            if (maxY >= query->value(1).toDouble()) maxY = query->value(1).toDouble();

            dx << query->value(0).toDouble();
            dy << query->value(1).toDouble();

            QCPBars* bar = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
            bar->setName("Значение");
            bar->setBrush(QColor(255, 0, 0, 255));
            bar->setData(dx, dy);
            bar->setWidth(0.20);

            ui->widget->xAxis->setLabel("Месяц");
            ui->widget->yAxis->setLabel("Выручка");

            ui->widget->yAxis->setRange(minX, maxX + 0.20);
            ui->widget->yAxis->setRange(minY, maxY + 1);

            ui->widget->xAxis->setAutoTickStep(false);
            ui->widget->yAxis->setAutoTickStep(false);
            ui->widget->xAxis->setTickStep(1);
            ui->widget->yAxis->setTickStep(1);

            ui->widget->replot();
        }
    }

}

printgraph::~printgraph()
{
    delete ui;
}
