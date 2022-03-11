#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "biens.h"
#include <QMessageBox>
#include "connection.h"
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(100, 999, this));
    ui->tab_biens->setModel(B.afficher());
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


      bool test1=b.ajouter();
      if(test1)
    {

    QMessageBox::information(nullptr, QObject::tr("Ajouter une propriete"),
                      QObject::tr("propriete ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);



    }
      else
    {
                QMessageBox::critical(nullptr, QObject::tr("Ajouter une propriete"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
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
