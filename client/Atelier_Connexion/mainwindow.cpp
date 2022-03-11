#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include "connection.h"
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->lineEdit->setValidator(new QIntValidator(0, 999, this));
    ui->tabcl->setModel(CL.afficher());
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

   Client c1(idc,nom,prenom,datena,mail,tele,datein);


      bool test1=c1.ajouter();
      if(test1)
    {

    QMessageBox::information(nullptr, QObject::tr("Ajouter une propriete"),
                      QObject::tr("propriete ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tabcl->setModel(c1.afficher());


    }
      else
    {
                QMessageBox::critical(nullptr, QObject::tr("Ajouter une propriete"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    }



}

void MainWindow::on_supcl_clicked()
{
    Client cl;
    cl.setIDC(ui->lineEdit->text().toInt());
    bool test2=cl.supprimer(cl.getIDC());
    if(test2)
  {

  QMessageBox::information(nullptr, QObject::tr("supprimer une propriete"),
                    QObject::tr("propriete supprime.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  ui->tabcl->setModel(cl.afficher());

  }
    else
  {
              QMessageBox::critical(nullptr, QObject::tr("supprimer une propriete"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
  }
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



      Client c1(idc,nom,prenom,datena,mail,tele,datein);
    bool test=c1.modifier(idc);

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("Modifier une propriete"),
                                 QObject::tr("  propriete Modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tabcl->setModel(c1.afficher());//refresh
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier une propriete"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
