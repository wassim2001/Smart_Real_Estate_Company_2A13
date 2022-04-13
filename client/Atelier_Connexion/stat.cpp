#include "stat.h"
#include "ui_statistique.h"
#include "terrain.h"

statistique::statistique(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::statistique)
{
    nb0=t.nbetat0();
    nb1=t.nbetat1();
    ui->setupUi(this);
    QPieSeries *series = new QPieSeries; //La série circulaire définit un graphique circulaire qui se compose de tranches de tarte qui sont définies comme des objets A Pie Slice
    series->append("Terrains d'etat 0",nb0);
    series->append("Terrains d'etat 1",nb1);

    QChart *chart = new QChart(); //pour afficher

    chart->addSeries(series);
    chart->setTitle("Statistique des terrains selon l'Etat");

    QChartView *chartview = new QChartView(chart);
    chartview->setParent(ui->horizontalFrame);
}

statistique::~statistique()
{
    delete ui;
}
