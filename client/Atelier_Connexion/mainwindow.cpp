#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include "connection.h"
#include <QIntValidator>
#include "client.h"
#include "excel.h"
#include <QMessageBox>
#include <QComboBox>
#include <QSpinBox>
#include<QIntValidator>
#include<QValidator>
#include <QSystemTrayIcon>
#include "excel.h"
#include <QFileDialog>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->lineEdit->setValidator(new QIntValidator(0, 999, this));
    ui->tabcl->setModel(CL.afficher());

    //
    int ret=A.connect_arduino(); // lancer la connexion à arduino
                switch(ret){
                case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                    break;
                case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                   break;
                case(-1):qDebug() << "arduino is not available";
                }
                 QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
                 //le slot update_label suite à la reception du signal readyRead (reception des données).
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajoutcl_clicked()
{
    int idc=ui->lineEdit->text().toInt();
    QString nom=ui->lineEdit_2->text();
    QString prenom=ui->lineEdit_3->text();
    QString datena=ui->lineEdit_7->text();
    QString mail=ui->lineEdit_4->text();
    int tele=ui->lineEdit_5->text().toInt();
    QString datein=ui->lineEdit_8->text();
    QString sexe=ui->sexe->currentText();



     Client c1(idc,nom,prenom,sexe,datena,mail,tele,datein);


      bool test1=c1.ajouter();
      if(test1)
    {

    QMessageBox::information(nullptr, QObject::tr("Ajouter un client "),
                      QObject::tr("client ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tabcl->setModel(c1.afficher());


    }
      else
    {
                QMessageBox::critical(nullptr, QObject::tr("Ajouter un client "),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    }




 ui->tabcl->setModel(CL.afficher());

}

void MainWindow::on_supcl_clicked()
{
    Client cl;
    cl.setIDC(ui->lineEdit_6->text().toInt());
    bool test2=cl.supprimer(cl.getIDC());
    if(test2)
  {

  QMessageBox::information(nullptr, QObject::tr("supprimer un client"),
                    QObject::tr("client supprime.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  ui->tabcl->setModel(cl.afficher());

  }
    else
  {
              QMessageBox::critical(nullptr, QObject::tr("supprimer un client"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
  }
     ui->tabcl->setModel(CL.afficher());
    /*
    QString idc=ui->lineEdit_id_supp->text();
   bool test = T.supprimerTerrain(id);

   if(test)  {QMessageBox::information(this,"succes","Delete with succes");

     ui->tableTerrain->setModel(T.afficherTerrain());
   }

    else{
        QMessageBox::warning(nullptr, QObject::tr("vide"),
                    QObject::tr("id n'existe pas .\n"), QMessageBox::Cancel);

}*/
}

void MainWindow::on_modifcl_clicked()
{
    int idc=ui->lineEdit->text().toInt();
    QString nom=ui->lineEdit_2->text();
    QString prenom=ui->lineEdit_3->text();
    QString datena=ui->lineEdit_7->text();
    QString mail=ui->lineEdit_4->text();
    int tele=ui->lineEdit_5->text().toInt();
    QString datein=ui->lineEdit_8->text();
    QString sexe=ui->sexe->currentText();



      Client c1(idc,nom,prenom,sexe,datena,mail,tele,datein);
    bool test=c1.modifier(idc);

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("Modifier un client"),
                                 QObject::tr("  client Modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tabcl->setModel(c1.afficher());//refresh
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier un client"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
     ui->tabcl->setModel(CL.afficher());
}

void MainWindow::on_pushButton_clicked()
{

    QString rech =ui->lineEdit_9->text();
   ui->tabcl->setModel(CL.rechercher(rech));


}

void MainWindow::on_pushButton_2_clicked()
{

    ui->tabcl->setModel(CL.tri());

}

void MainWindow::on_pushButton_3_clicked()
{



        QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                               tr("Excel Files (*.xls)"));
               if (fileName.isEmpty())
                   return;

               ExportExcelObject obj(fileName, "CLIENTS", ui->tabcl);

               //colums to export
               obj.addField(0, "id", "int");
               obj.addField(1, "nom", "char(20)");
               obj.addField(2, "prenom", "char(20)");
               obj.addField(3, "sexe", "char(20)");
               obj.addField(4, "datena", "char(20)");
               obj.addField(5, "mail", "char(20)");
               obj.addField(6, "tele", "int");
               obj.addField(7, "datein", "char(20)");




               int retVal = obj.export2Excel();
               if( retVal > 0)
               {
                   QMessageBox::information(this, tr("Done"),
                                            QString(tr("%1 records exported!")).arg(retVal)
                                            );

                }

}

void MainWindow::on_pushButton_stat_clicked()
{
    stat = new statistique(this);
    stat->show();
}



void MainWindow::update_label()
{

data=A.read_from_arduino();
if(data=="0" || data=="2") //
{
ui->ard->setText("ON");
}
else
{
 ui->ard->setText("OFF");

}

}




void MainWindow::on_pushButton_4_clicked()
{

A.write_to_arduino("1");



}






void MainWindow::on_pushButton_5_clicked()
{

A.write_to_arduino("3");

}
