#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "biens.h"
#include "client.h"
#include "employe.h"
#include "smtp.h"
#include "arduino.h"
#include "excel.h"
#include "contrat.h"
#include <QMessageBox>
#include "connection.h"
#include <QIntValidator>
#include <QCheckBox>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
#include <QQuickItem>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QTextBrowser>
#include <QFileDialog>
#include <QSystemTrayIcon>
#include <QComboBox>
#include <QSpinBox>
#include<QValidator>
#include <QTextDocument>
#include <QTextStream>
#include <QFile>
#include <QRectF>
#include <QStaticText>
Contrat Contrats;

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
    ui->tabcl->setModel(CL.affichercl());
    ui->tableViewContrat->setModel(Contrats.affichercontrat());
    ui->tab_employe->setModel(E.afficher());
    ui->tab_employe_2->setModel(E.afficher());
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
            ui->quickWidget->show();
            auto obj = ui->quickWidget->rootObject();
            connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
            connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

            emit setCenter(37.27561, 9.86718);
            emit addMarker(37.27561, 9.86718);

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

void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if(ui->comboBox_2->currentText()=="prix croissant")
            ui->tab_biens->setModel(B.triPrice());
       else if(ui->comboBox_2->currentText()=="prix decroissant")
           ui->tab_biens->setModel(B.triPrice2());
       else if(ui->comboBox_2->currentText()=="city")
           ui->tab_biens->setModel(B.triPrice3());
}






void MainWindow::update_label()
{
    data=A.read_from_arduino();
    qDebug() << data<<endl;

    if(data=="1")

        QMessageBox::information(this, tr("Card is valid!"), "ACCESS GIVEN");

    else if (data=="0")

        QMessageBox::information(this, tr("Card is unvalid"), "ACCESS DENIED");
}




void MainWindow::on_pushButton_2_clicked()
{
    A.write_to_arduino("1");
}





/*---------------------------------------dom--------------------------*/
void MainWindow::on_ajoutcl_clicked()
{
    int idc=ui->lineEdit_dom->text().toInt();
    QString nom=ui->lineEdit_dom2->text();
    QString prenom=ui->lineEdit_dom3->text();
    QString datena=ui->lineEdit_dom7->text();
    QString mail=ui->lineEdit_dom4->text();
    int tele=ui->lineEdit_dom5->text().toInt();
    QString datein=ui->lineEdit_dom8->text();
    QString sexe=ui->sexedom->currentText();



     Client c1(idc,nom,prenom,sexe,datena,mail,tele,datein);


      bool test1=c1.ajoutercl();
      if(test1)
    {


    QMessageBox::information(nullptr, QObject::tr("Ajouter un client "),
                      QObject::tr("client ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tabcl->setModel(c1.affichercl());


    }
      else
    {
                QMessageBox::critical(nullptr, QObject::tr("Ajouter un client "),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
    }




 ui->tabcl->setModel(CL.affichercl());

}

void MainWindow::on_supcl_clicked()
{
    Client cl;
    cl.setIDCC(ui->lineEdit_dom6->text().toInt());
    bool test2=cl.supprimercl(cl.getIDCC());
    if(test2)
  {

  QMessageBox::information(nullptr, QObject::tr("supprimer un client"),
                    QObject::tr("client supprime.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  ui->tabcl->setModel(cl.affichercl());

  }
    else
  {
              QMessageBox::critical(nullptr, QObject::tr("supprimer un client"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
  }
     ui->tabcl->setModel(CL.affichercl());
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
    int idc=ui->lineEdit_dom->text().toInt();
    QString nom=ui->lineEdit_dom2->text();
    QString prenom=ui->lineEdit_dom3->text();
    QString datena=ui->lineEdit_dom7->text();
    QString mail=ui->lineEdit_dom4->text();
    int tele=ui->lineEdit_dom5->text().toInt();
    QString datein=ui->lineEdit_dom8->text();
    QString sexe=ui->sexedom->currentText();



      Client c1(idc,nom,prenom,sexe,datena,mail,tele,datein);
    bool test=c1.modifiercl(idc);

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("Modifier un client"),
                                 QObject::tr("  client Modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tabcl->setModel(c1.affichercl());//refresh
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier un client"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
     ui->tabcl->setModel(CL.affichercl());
}


void MainWindow::on_pushButton_2dom_clicked()
{

    ui->tabcl->setModel(CL.tri());

}

void MainWindow::on_pushButton_6dom_clicked()
{
    Client CL;
    CL.exporterpdf(ui->textBrowser);
}
void MainWindow::on_pushButton_statdom_clicked()
{
    stat = new statistique(this);
    stat->show();
}
void MainWindow::on_pushButton_3dom_clicked()
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




void MainWindow::on_pushButtondom_clicked()
{
    QString rech =ui->lineEdit_dom9->text();
   ui->tabcl->setModel(CL.rechercher(rech));
}

void MainWindow::on_pushButton_4dom_clicked()
{
    A.write_to_arduino("1");
}

void MainWindow::update_label1()
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



/*------------------------------------damergi---------------------*/


void MainWindow::refresh()
{
  ui->tableViewContrat->setModel(Contrats.affichercontrat());

}


void MainWindow::on_pushButton_ajouterContrat_clicked()
{
    if (ui->lineEdit_typeContrat->text().contains(QRegExp("^[A-Za-z]+$"))){
    int id_agence = ui->lineEdit_idAgence_Contrat->text().toInt();
    QString cin = ui->lineEdit_cin_Contrat->text();
    int id_produit = ui->lineEdit_idProduit_Contrat->text().toInt();
    QString type = ui->lineEdit_typeContrat->text();
    QDate date_contrat = ui->dateEdit_Contrat->date();
    Contrat C(0,id_agence,cin,id_produit,date_contrat,type);

bool ok = C.ajoutercontrat();
if(ok)
{
    refresh();
    QMessageBox::information(nullptr, QObject::tr("succes"),
                QObject::tr("contrat ajouté.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("fail"),
                QObject::tr("contrat non ajouté.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    } else     QMessageBox::critical(nullptr, QObject::tr("fail"),
                                     QObject::tr("veuillez verifier le type.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_supprimerContrat_clicked()
{
    if (ui->lineEdit_idsuppmodifContrat->text().isEmpty())
        QMessageBox::critical(nullptr, QObject::tr("fail"),
                    QObject::tr("veuillez entrer un id.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    else if (Contrats.contratexist(ui->lineEdit_idsuppmodifContrat->text().toInt())==0)
        QMessageBox::critical(nullptr, QObject::tr("fail"),
                    QObject::tr("contrat n'existe pas.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    else {
    int id = ui->lineEdit_idsuppmodifContrat->text().toInt();
    bool ok = Contrats.supprimercontrat(id);
    if(ok)
    {
        refresh();
        QMessageBox::information(nullptr, QObject::tr("succes"),
                    QObject::tr("contrat supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("fail"),
                    QObject::tr("contrat non supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_modifierContrats_clicked()
{
    if (ui->lineEdit_idsuppmodifContrat->text().isEmpty())
        QMessageBox::critical(nullptr, QObject::tr("fail"),
                    QObject::tr("veuillez entrer un id.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    else if (Contrats.contratexist(ui->lineEdit_idsuppmodifContrat->text().toInt())==0)
        QMessageBox::critical(nullptr, QObject::tr("fail"),
                    QObject::tr("contrat n'existe pas.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    else {
    int id_agence = ui->lineEdit_idAgence_Contrat->text().toInt();
    QString cin = ui->lineEdit_cin_Contrat->text();
    int id_produit = ui->lineEdit_idProduit_Contrat->text().toInt();
    QString type = ui->lineEdit_typeContrat->text();
    QDate date_contrat = ui->dateEdit_Contrat->date();
    int id = ui->lineEdit_idsuppmodifContrat->text().toInt();

    Contrat C(id,id_agence,cin,id_produit,date_contrat,type);


bool ok = C.modifiercontrat();
if(ok)
{
    refresh();
    QMessageBox::information(nullptr, QObject::tr("succes"),
                QObject::tr("contrat modifié.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("fail"),
                QObject::tr("contrat non modifié.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::clear(){
    ui->lineEdit_idAgence_Contrat->clear();
    ui->lineEdit_cin_Contrat->clear();
    ui->lineEdit_idProduit_Contrat->clear();
    ui->lineEdit_typeContrat->clear();
}

void MainWindow::on_lineEdit_idsuppmodifContrat_textChanged(const QString &arg1)
{
    if (Contrats.contratexist(arg1.toInt())){
        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from CONTRAT WHERE ID_CONTRAT="+arg1);
        ui->lineEdit_idAgence_Contrat->setText(model->data(model->index(0,1)).toString());
        ui->lineEdit_cin_Contrat->setText(model->data(model->index(0,2)).toString());
        ui->lineEdit_idProduit_Contrat->setText(model->data(model->index(0,3)).toString());
        ui->lineEdit_typeContrat->setText(model->data(model->index(0,5)).toString());


    } else clear();
}



void MainWindow::on_pushButton_pdf_clicked()
{
    QString strStream;
                          QTextStream out(&strStream);

                           const int rowCount = ui->tableViewContrat->model()->rowCount();
                           const int columnCount = ui->tableViewContrat->model()->columnCount();
                          out <<  "<html>\n"
                          "<head>\n"
                                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                           <<  QString("<title>%1</title>\n").arg("strTitle")
                                           <<  "</head>\n"
                                           "<body bgcolor=#ffffff link=#5000A0>\n"

                                          //     "<align='right'> " << datefich << "</align>"
                                           "<center> <H1>Liste des Guichets</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                       // headers
                                       out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                       out<<"<cellspacing=10 cellpadding=3>";
                                       for (int column = 0; column < columnCount; column++)
                                           if (!ui->tableViewContrat->isColumnHidden(column))
                                               out << QString("<th>%1</th>").arg(ui->tableViewContrat->model()->headerData(column, Qt::Horizontal).toString());
                                       out << "</tr></thead>\n";

                                       // data table
                                       for (int row = 0; row < rowCount; row++) {
                                           out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                           for (int column = 0; column < columnCount; column++) {
                                               if (!ui->tableViewContrat->isColumnHidden(column)) {
                                                   QString data = ui->tableViewContrat->model()->data(ui->tableViewContrat->model()->index(row, column)).toString().simplified();
                                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                               }
                                           }
                                           out << "</tr>\n";
                                       }
                                       out <<  "</table> </center>\n"
                                           "</body>\n"
                                           "</html>\n";

                                 QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                   if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                                  QPrinter printer (QPrinter::PrinterResolution);
                                   printer.setOutputFormat(QPrinter::PdfFormat);
                                  printer.setPaperSize(QPrinter::A4);
                                 printer.setOutputFileName(fileName);

                                  QTextDocument doc;
                                   doc.setHtml(strStream);
                                   doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                   doc.print(&printer);
}



void MainWindow::on_pushButton_Da_clicked()
{
    if (ui->radioButton_type->isChecked())    ui->tableViewContrat->setModel(Contrats.triType());
    if (ui->radioButton_date->isChecked())    ui->tableViewContrat->setModel(Contrats.triDate());
    if (ui->radioButton_idAgence->isChecked())    ui->tableViewContrat->setModel(Contrats.triProduit());

}

void MainWindow::on_lineEdit_12_textChanged(const QString &arg1)
{
     ui->tableViewContrat->setModel(Contrats.recherche(arg1));
}





/*----------------------------skan---------------------------------*/
void MainWindow::on_pb_ajouter_1_clicked()
{
    bool check=true;
    bool check1=true;
    bool check2=true;
    bool check3=true;
    bool check4=true;
    bool check5=true;
    bool check6=true;
    bool check7=true;
    bool check8=true;



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
      //Employe(int,QString,int,int,int,QString,QString,QString,int);

     QString idcheck= ui->le_id->text();
     QString salairecheck= ui->le_salaire->text();
     QString heuresdetravailheck= ui->le_heures_de_travail->text();
     QString absencescheck= ui->le_absences->text();
     QString agecheck= ui->le_age->text();

     QString postecheck= ui->le_poste->text();
     QString nomcheck= ui->le_nom->text();
     QString prenomcheck= ui->le_prenom->text();
     QString sexecheck= ui->box_sexe->currentText();

check = E.checkforchar(idcheck);
check1 = E.checkforchar(salairecheck);
check2 = E.checkforchar(heuresdetravailheck);
check3 = E.checkforchar(absencescheck);
check4 = E.checkforchar(agecheck);
check5 = E.checkforint(postecheck);
check6 = E.checkforint(nomcheck);
check7 = E.checkforint(prenomcheck);
check8 = E.checkforint(sexecheck);

     if (check && check1 && check2 && check3 && check4 && check5 && check6 && check7 && check8 )
{
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
}




/*void MainWindow::stats(QString table,QString critere,int valeur1,int valeur2,QString unite)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString valeur1QString=QString::number(valeur1);
    QString valeur2QString=QString::number(valeur2);

                model->setQuery("select * from "+table+" where "+critere+"<"+valeur1QString);

                float countFirst=model->rowCount();
                model->setQuery("select * from "+table+" where " +critere+" between " +valeur1QString+ " and "+valeur2QString);
                float countSecond=model->rowCount();
                model->setQuery("select * from "+table+" where " +critere+">"+valeur2QString);
                float countThird=model->rowCount();
                float total=countFirst+countSecond+countThird;
                QString a=QString("moins de "+valeur1QString+" "+unite+" "+QString::number((countFirst*100)/total,'f',2)+"%" );

                QString b=QString("entre "+valeur1QString+ " et " +valeur2QString+" "+unite+" "+QString::number((countSecond*100)/total,'f',2)+"%" );
                QString c=QString("Plus que "+valeur2QString +" "+unite+" "+QString::number((countThird*100)/total,'f',2)+"%" );

                QPieSeries *series = new QPieSeries();
                series->append(a,countFirst);
                series->append(b,countSecond);
                series->append(c,countThird);
        if (countFirst!=0)
        {QPieSlice *slice = series->slices().at(0);
         slice->setLabelVisible();
         slice->setPen(QPen());}
        if ( countSecond!=0)
        {
                 // Add label, explode and define brush for 2nd slice
                 QPieSlice *slice1 = series->slices().at(1);
                 //slice1->setExploded();
                 slice1->setLabelVisible();
        }
       if(countThird!=0)
        {
                 // Add labels to rest of slices
                 QPieSlice *slice2 = series->slices().at(2);
                 //slice1->setExploded();
                 slice2->setLabelVisible();
        }
                // Create the chart widget
                QChart *chart = new QChart();
                // Add data to chart with title and hide legend
                chart->addSeries(series);
                if(critere=="CAPACITE_STADE")
                    critere="Capacite";
                chart->setTitle("Pourcentage Par " +critere+":Nombre Des " +table+" :" +QString::number(total));
                chart->legend()->hide();
                // Used to display the chart
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->resize(1000,500);
                chartView->show();

}

*/

void MainWindow::on_pb_modifier_2Em_clicked()
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

void MainWindow::on_pushButton_suppEm_clicked()
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

void MainWindow::on_pb_trier_sexe_clicked()
{

    Employe E;
ui->tab_employe_2->setModel(E.afficher_triesexe());
}

void MainWindow::on_pb_trier_salaire_clicked()
{
    Employe E;
ui->tab_employe_2->setModel(E.afficher_triesalaire());
}

void MainWindow::on_pb_trirer_poste_clicked()
{
    Employe E;
ui->tab_employe_2->setModel(E.afficher_trieage());
}

void MainWindow::on_chercher_clicked()
{

    //ui->tab_employe_2->setModel(E.recherchef(ui->le_id_r->text() , ui->le_nom_r->text() , ui->le_poste_r->text()));
      ui->tab_employe_2->setModel(E.recherchef2(ui->le_id_r->text() ));
}

/*void MainWindow::on_pb_age_stat_clicked()
{
    stats("employe","age",20,50,"Age");
}
*/

void MainWindow::on_pushButton_imagesk_clicked()
{
    QString image;
        QString file_name= QFileDialog::getOpenFileName(this,"open a file","C:\\");
        ui->aaaaask->insert(file_name);
        QPixmap pix(file_name);
ui->kkkkk->setPixmap(pix.scaled(150,150,Qt::KeepAspectRatio));
}
