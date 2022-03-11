#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "QString"
#include<employe.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
ui->tab_employe->setModel(E.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_1_clicked()
{ int id=ui->le_id->text().toInt();
    QString poste=ui->le_poste->text();
    int salaire=ui->le_salaire->text().toInt();
    int heures_de_travail=ui->le_heures_de_travail->text().toInt();
    int absences=ui->le_absences->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString sexe=ui->box_sexe->currentText();
    int age=ui->le_age->text().toInt();

     Employe E(id,poste,salaire,heures_de_travail,absences,nom,prenom,sexe,age);
      //Employe(int,QString,int,int,int,QString,QString,QString,int);
     bool test=E.ajouter();
     if(test)
         {ui->tab_employe->setModel(E.afficher());//refresh
             QMessageBox::information(nullptr,QObject::tr("OK"),
                                      QObject::tr("AJOUT EFFECTUE\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
         }
         else
             QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                   QObject::tr("Ajout non effectue.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_modifier_2_clicked()
{
        int id=ui->le_id->text().toInt();
        QString poste=ui->le_poste->text();
        int salaire=ui->le_salaire->text().toInt();
        int heures_de_travail=ui->le_heures_de_travail->text().toInt();
        int absences=ui->le_absences->text().toInt();
        QString nom=ui->le_nom->text();
        QString prenom=ui->le_prenom->text();
        QString sexe=ui->box_sexe->currentText();
        int age=ui->le_age->text().toInt();

        Employe E(id,poste,salaire,heures_de_travail,absences,nom,prenom,sexe,age);
          bool test=E.modifier(id);
          if(test)
        {


        QMessageBox::information(nullptr,QObject::tr("modifier "),
                          QObject::tr(" modifié.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
           ui->tab_employe->setModel(E.afficher());//refresh
        }
          else
              QMessageBox::critical(nullptr,QObject::tr("modifier"),
                          QObject::tr("Erreur !.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

    }
void MainWindow::on_pushButton_clicked()
{
    Employe E;
    E.setid(ui->le_id->text().toInt());
bool test=E.supprimer(E.getid());

QMessageBox msgBox;

if(test)
{

    msgBox.setText(("Supression avec success."));
    ui->tab_employe->setModel(E.afficher());
}
else

    msgBox.setText("Echec de suppression");
msgBox.exec();
}

