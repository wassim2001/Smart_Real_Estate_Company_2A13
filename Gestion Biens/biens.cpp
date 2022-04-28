#include "biens.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Biens::Biens()
{
idc=0;
idp=0;
type="";
liste="";
city="";
governorate="";
description="";
}

bool Biens::checkforchar(QString x)
{
bool check=true;
if(x.isEmpty())
{
    check=false;
    return check;
    }
else
{
    for(int i=0;i<x.size();i++)
    {

        if(x[i].isDigit())
        {
         check=false;
         break;
        }
    }
}

return check;

}

Biens::Biens(int idp,QString type ,QString governorate,QString city,QString liste,QString description,float price,float latitude,float longititude,int idc)

{
    this->idc=idc;
    this->idp=idp;
    this->description=description;
    this->governorate=governorate;
    this->city=city;
    this->type=type;
    this->liste=liste;
    this->price=price;
    this->latitude=latitude;
    this->longititude=longititude;
}
    int Biens::getIDC(){return idc;}
    int Biens::getIDP(){return idp;}
    QString Biens::getDescription(){return description;}
    QString Biens::getGov(){return governorate;}
    QString Biens::getCity(){return city;}
    QString Biens::getType(){return type;}
    QString Biens::getListe(){return liste;}
    float Biens::getPrice(){return price;}
    float Biens::getLatitude(){return latitude;}
    float Biens::getLongititude(){return longititude;}


    void Biens::setIDC(int idc){this->idc=idc;}
    void Biens::setIDP(int idp){this->idp=idp;}
    void Biens::setDescription(QString description){this->description=description;}
    void Biens::setGov(QString governorate){this->governorate=governorate;}
    void Biens::setCity(QString city){this->city=city;}
    void Biens::setType(QString type){this->type=type;}
    void Biens::setListe(QString liste){this->liste=liste;}
    void Biens::setPrice(float price){this->price=price;}
    void Biens::setLatitude(float latitude){this->latitude=latitude;}
    void Biens::setLongititude(float longititude){this->longititude=longititude;}


    bool Biens::ajouter()
    {

    QSqlQuery query;
    query.prepare("INSERT INTO BIENS (idp, type, governorate, city, liste, description, price, latitude, longititude, idc) "
                  "VALUES (:idp, :type, :governorate, :city, :liste, :description, :price, :latitude, :longititude, :idc)");
    query.bindValue(":idp", idp);
    query.bindValue(":type", type);
    query.bindValue(":governorate", governorate);
    query.bindValue(":city", city);
    query.bindValue(":liste", liste);
    query.bindValue(":description", description);
    query.bindValue(":price", price);
    query.bindValue(":latitude", latitude);
    query.bindValue(":longititude", longititude);
    query.bindValue(":idc", idc);

    return    query.exec();
    }

    QSqlQueryModel* Biens::afficher()
    {

    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM BIENS");

    return model;
    }

    bool Biens::supprimer(int)
    {
        QSqlQuery query;
        query.prepare("DELETE FROM BIENS WHERE idp=:idp");
        query.bindValue(0, idp);
        return query.exec();
    }

    bool Biens::modifier(int idp)
    {
     QSqlQuery query;



    query.prepare("update  BIENS set type=:type, governorate=:governorate,city=:city,liste=:liste,description=:description,price=:price,latitude=:latitude,longititude=:longititude,idc=:idc where idp=:idp ");


     query.bindValue(":idp", idp);
     query.bindValue(":type", type);
     query.bindValue(":governorate", governorate);
     query.bindValue(":city", city);
     query.bindValue(":liste", liste);
     query.bindValue(":description", description);
     query.bindValue(":price", price);
     query.bindValue(":latitude", latitude);
     query.bindValue(":longititude", longititude);
     query.bindValue(":idc", idc);



     return query.exec();
    }
    QSqlQueryModel * Biens::recherche(QString var)
        {
            QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("SELECT * FROM biens WHERE CITY LIKE '%"+var+"%' or IDP LIKE '%"+var+"%' or TYPE LIKE '%"+var+"%'");
            model->query().bindValue(":idp",idp);
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDP"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("GOVERNORATE"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("CITY"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("LISTE"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("DESCRIPTION"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("PRICE"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("LATITUDE"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("LONGITITUDE"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("IDC"));

            return model;
        }

    QSqlQueryModel* Biens::triPrice()
    {

    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM BIENS ORDER BY PRICE");

    return model;
    }
    QSqlQueryModel* Biens::triPrice2()
    {

    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM BIENS ORDER BY PRICE DESC");

    return model;
        }
    QSqlQueryModel* Biens::triPrice3()
    {

    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM BIENS ORDER BY CITY ASC");

    return model;
    }


