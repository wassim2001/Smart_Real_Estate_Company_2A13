#include "add_proprety.h"
#include "ui_add_proprety.h"
#include <QMessageBox>

Add_proprety::Add_proprety(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_proprety)
{
    ui->setupUi(this);
}

Add_proprety::~Add_proprety()
{
    delete ui;
}
void Add_proprety::title()
{
    setWindowTitle("Smart Immo");
}

void Add_proprety::on_pushButton_3_clicked()
{
    QMessageBox::about(this, "Smart Immo","informations enregistrees");
}


void Add_proprety::on_pushButton_4_clicked()
{
    close();
}
Add_proprety::Add_proprety(int idc,int idp,QString description,QString governorate,QString city,QString type ,QString liste,float price,float latitude,float longititude)
{
    this->idc=idc;
    this->idp=idp;
    this->governorate=governorate;
    this->city=city;
    this->type=type;
    this->liste=liste;
    this->price=price;
    this->latitude=latitude;
    this->longititude=longititude;
}
bool Add_proprety::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(idc);

    query.prepare("insert into biens(idc,type,nature,governoratete,city,liste,description,price,latitude,longititude) ""values(:idc, :type, :nature, :governorate, :city, :liste, :price, :latitude, :longititude)");

    query.bindValue(0, idc);
    query.bindValue(1, idp);
    query.bindValue(2, governorate);
    query.bindValue(3, city);
    query.bindValue(4, type);
    query.bindValue(5, liste);
    query.bindValue(6, price);
    query.bindValue(7, latitude);
    query.bindValue(8, longititude);

    return query.exec();
}
QSqlQueryModel * Add_proprety::afficher()
{

}
bool Add_proprety::supprimer()
{

}
