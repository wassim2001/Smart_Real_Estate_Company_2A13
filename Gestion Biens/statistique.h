#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include <QDialog>
#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include "client.h"
namespace Ui {
class statistique;
}

class statistique : public QDialog
{
    Q_OBJECT

public:
    explicit statistique(QWidget *parent = nullptr);
    ~statistique();

private:
    Ui::statistique *ui;
 Client t;
 int nb0 ,nb1;
};

#endif // STATISTIQUE_H
