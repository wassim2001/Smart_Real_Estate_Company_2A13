#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "biens.h"
#include "smtp.h"
#include <QMessageBox>
#include "connection.h"
#include <QIntValidator>
#include <QCheckBox>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
#include <QQuickItem>
#include<QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit->setValidator(new QIntValidator(0, 9999, this));
    ui->lineEdit_2->setValidator(new QIntValidator(0, 9999, this));
    ui->lineEdit_4->setValidator(new QIntValidator(0, 999999999, this));


    /*QRegExp rx("[a-zA-Z]+");
    QValidator *validator = new QRegExpValidator(rx, this->ui->lineEdit_3);
    QLineEdit *edit = new QLineEdit(this->ui->lineEdit_3);
    edit->setValidator(validator);*/

    ui->tab_biens->setModel(B.afficher());
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
            ui->quickWidget->show();
            auto obj = ui->quickWidget->rootObject();
            connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
            connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

            emit setCenter(37.27561, 9.86718);
            emit addMarker(37.27561, 9.86718);


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::title()
{
    setWindowTitle("Smart Immo");
}


void MainWindow::on_valider_clicked()
{

    bool check=true;


    int idp=ui->lineEdit->text().toInt();
    int idc=ui->lineEdit_2->text().toInt();
    QString description=ui->lineEdit_3->text();
    QString governorate=ui->comboBox_3->currentText();
    QString city=ui->comboBox_4->currentText();
    QString type=ui->comboBox->currentText();
    QString liste=ui->comboBox_5->currentText();
    float price=ui->lineEdit_4->text().toFloat();
    float latitude=ui->lineEdit_5->text().toFloat();
    float longititude=ui->lineEdit_6->text().toFloat();


   Biens b(idp,type,governorate,city,liste,description,price,latitude,longititude,idc);

   check = b.checkforchar(description);

    if( idp == NULL || price == NULL || latitude == NULL || longititude == NULL || idc == NULL )
    {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter une propriete"),
              QObject::tr("Veuillez remplir tous les champs !.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    { if(check)
        {

      bool test1=b.ajouter();
      if(test1)
    {

    QMessageBox::information(nullptr, QObject::tr("Ajouter une propriete"),
                      QObject::tr("propriete ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_biens->setModel(b.afficher());


    }
      else
    {
                QMessageBox::critical(nullptr, QObject::tr("Ajouter une propriete"),
                      QObject::tr("Erreur propriete deja existe !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    }


    }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Ajouter une propriete"),
                  QObject::tr("seulement chaines de caracteres dans description !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }

}//end



void MainWindow::on_sup_button_clicked()
{
   Biens bs;
   bs.setIDP(ui->lineEdit_7->text().toInt());
   bool test2=bs.supprimer(bs.getIDP());
   if(test2)
 {

 QMessageBox::information(nullptr, QObject::tr("supprimer une propriete"),
                   QObject::tr("propriete supprime.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

 ui->tab_biens->setModel(bs.afficher());

 }
   else
 {
             QMessageBox::critical(nullptr, QObject::tr("supprimer une propriete"),
                   QObject::tr("Erreur !.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
 }
}

void MainWindow::on_modif_button_clicked()
{


        int idp=ui->lineEdit->text().toInt();
        int idc=ui->lineEdit_2->text().toInt();
        QString description=ui->lineEdit_3->text();
        QString governorate=ui->comboBox_3->currentText();
        QString city=ui->comboBox_4->currentText();
        QString type=ui->comboBox->currentText();
        QString liste=ui->comboBox_5->currentText();
        float price=ui->lineEdit_4->text().toFloat();
        float latitude=ui->lineEdit_5->text().toFloat();
        float longititude=ui->lineEdit_6->text().toFloat();


          Biens b(idp,type,governorate,city,liste,description,price,latitude,longititude,idc);
        bool test=b.modifier(idp);

        if (test)
        {
            QMessageBox::information(nullptr, QObject::tr("Modifier une propriete"),
                                     QObject::tr("  propriete Modifié.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_biens->setModel(b.afficher());//refresh
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Modifier une propriete"),
                                  QObject::tr("Erreur !.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }

}

void MainWindow::on_pushButton_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from biens where price >= 1000");
        float dispo1=model->rowCount();

        model->setQuery("select * from biens where price <1000");
        float dispo=model->rowCount();

        float total=dispo1+dispo;
            QString a=QString("price higher than 1000  . " +QString::number((dispo1*100)/total,'f',2)+"%" );
            QString b=QString("price under 1000 .  "+QString::number((dispo*100)/total,'f',2)+"%" );
            QPieSeries *series = new QPieSeries();
            series->append(a,dispo1);
            series->append(b,dispo);
        if (dispo1!=0)
        {QPieSlice *slice = series->slices().at(0);
            slice->setLabelVisible();
            slice->setPen(QPen());}
        if ( dispo!=0)
        {
            QPieSlice *slice1 = series->slices().at(1);
            slice1->setLabelVisible();
        }

        QChart *chart = new QChart();


        chart->addSeries(series);
        chart->setTitle("Price :Nb biens: "+ QString::number(total));
        chart->legend()->hide();


        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->resize(1000,500);
        chartView->show();


}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tab_biens->setModel(B.recherche(arg1));
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tab_biens->setModel(B.triPrice());
}

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("nay090236@gmail.com", "xzoxyxkgpuspbpve","smtp.gmail.com",465,30000);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail("promotion", ui->lineEdit_10->text() , ui->lineEdit_9->text(),ui->textEdit->toPlainText());
}



void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::on_envoyer_clicked()
{
    connect(ui->envoyer, SIGNAL(clicked()),this, SLOT(sendMail()));
}



void MainWindow::on_locate_clicked()
{
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
            ui->quickWidget->show();
            auto obj = ui->quickWidget->rootObject();
            connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
            connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

        emit setCenter(ui->lineEdit_8->text().toFloat(), ui->lineEdit_11->text().toFloat());
        emit addMarker(ui->lineEdit_8->text().toFloat(), ui->lineEdit_11->text().toFloat());
}

void MainWindow::on_search_textChanged(const QString &arg1)
{
    ui->tab_biens->setModel(B.recherche(arg1));
}
