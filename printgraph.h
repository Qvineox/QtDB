#ifndef PRINTGRAPH_H
#define PRINTGRAPH_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class printgraph;
}

class printgraph : public QWidget
{
    Q_OBJECT

public:
    explicit printgraph(QWidget *parent = nullptr);
    ~printgraph();

private:
    Ui::printgraph *ui;
};

#endif // PRINTGRAPH_H
