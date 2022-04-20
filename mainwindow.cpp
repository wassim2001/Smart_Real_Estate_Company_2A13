#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include "contrat.h"
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QFile>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextStream>
Contrat Contrats;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->tableViewContrat->setModel(Contrats.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh()
{
  ui->tableViewContrat->setModel(Contrats.afficher());
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

bool ok = C.ajouter();
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
   /* if (ui->lineEdit_idsuppmodifContrat->text().isEmpty())
        QMessageBox::critical(nullptr, QObject::tr("fail"),
                    QObject::tr("veuillez entrer un id.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    else if (Contrats.contratexist(ui->lineEdit_idsuppmodifContrat->text().toInt())==0)
        QMessageBox::critical(nullptr, QObject::tr("fail"),
                    QObject::tr("contrat n'existe pas.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    else {
    int id = ui->lineEdit_idsuppmodifContrat->text().toInt();
    bool ok = Contrats.supprimer(id);
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
    } */

    int id=ui->lineEdit_idsuppmodifContrat->text().toInt();
   bool test = Contrats.supprimer(id);

   if(test)  {QMessageBox::information(this,"succes","Delete with succes");

     ui->tableViewContrat->setModel(Contrats.afficher());
   }

    else{
        QMessageBox::warning(nullptr, QObject::tr("vide"),
                    QObject::tr("id n'existe pas .\n"), QMessageBox::Cancel);

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


bool ok = C.modifier();
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

void MainWindow::on_pushButton_clicked()
{
if (ui->radioButton_type->isChecked())    ui->tableViewContrat->setModel(Contrats.triType());
if (ui->radioButton_date->isChecked())    ui->tableViewContrat->setModel(Contrats.triDate());
if (ui->radioButton_idAgence->isChecked())    ui->tableViewContrat->setModel(Contrats.triProduit());

}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tableViewContrat->setModel(Contrats.recherche(arg1));
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
                                           "<center> <H1>Liste des contrat</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

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



