#include "client.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Client::Client()
{
idc=0;
nom="";
prenom="";
sexe="";
mail="";
tele=0;
datena="";
datein="";
}
//constricteur
Client::Client(int idc,QString nom ,QString prenom,QString sexe,QString datena,QString mail,int tele,QString datein )
{
    this->idc=idc;
    this->nom=nom;
    this->prenom=prenom;
    this->sexe=sexe;
    this->datena=datena;
    this->mail=mail;
    this->tele=tele;
    this->datein=datein;
}

    int Client::getIDC(){return idc;}
    QString Client::getNOM(){return nom;}
    QString Client::getPRENOM(){return prenom;}
    QString Client::getDATENA(){return datena;}
    QString Client::getSEXE(){return sexe;}
    QString Client::getMAIL(){return mail;}
    int Client::getTELE(){return tele;}
    QString Client::getDATEIN(){return datein;}

    void Client::setIDC(int idc){this->idc=idc;}
    void Client::setNOM(QString  nom){this->nom=nom;}
    void Client::setPRENOM(QString prenom){this->prenom=prenom;}
    void Client::setSEXE(QString sexe){this->sexe=sexe;}
    void Client::setDATENA(QString datena){this->datena=datena;}
    void Client::setMAIL(QString mail){this->mail=mail;}
    void Client::setTELE(int  tele){this->tele=tele;}
    void Client::setDATEIN(QString datein){this->datein=datein;}

    bool Client::ajouter()
    {

    QSqlQuery query;
    query.prepare("INSERT INTO CLIENTS (idc, nom, prenom,sexe, datena, mail, tele, datein) "
                  "VALUES (:idc, :nom, :prenom,:sexe, :datena, :mail, :tele, :datein)");
    query.bindValue(":idc", idc);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":sexe", sexe);
    query.bindValue(":datena", datena);
    query.bindValue(":mail", mail);
    query.bindValue(":tele", tele);
    query.bindValue(":datein", datein);

    return    query.exec();
    }

    QSqlQueryModel* Client::afficher()
    {

    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM CLIENTS");

    return model;
    }

    bool Client::supprimer(int)
    {
        QSqlQuery query;
        query.prepare("DELETE FROM CLIENTS WHERE idc=:idc");
        query.bindValue(":idc",idc);
        return query.exec();
    }

    bool Client::modifier(int idc)
    {
     QSqlQuery query;



    query.prepare("update  CLIENTS set nom=:nom, prenom=:prenom,sexe=:sexe,datena=:datena,mail=:mail,tele=:tele,datein=:datein where idc=:idc ");


    query.bindValue(":idc", idc);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":sexe", sexe);
    query.bindValue(":datena", datena);
    query.bindValue(":mail", mail);
    query.bindValue(":tele", tele);
    query.bindValue(":datein", datein);


     return query.exec();
    }


    QSqlQueryModel *Client::rechercher(QString rech)

    {
        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from CLIENTS where nom LIKE '"+rech+"%'");
        return model;
    }


    QSqlQueryModel * Client::tri()
    {
        QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from CLIENTS ORDER BY nom ");


        model->setHeaderData(0, Qt::Horizontal, QObject::tr("idc"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom "));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("sexe "));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("datena "));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail "));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("tele "));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("datein"));

            return model;
    }

    int Client::nbetat0(){

        QSqlQuery qry;
        int nb=0;
        qry.exec("select sexe from CLIENTS where sexe ='Homme'");
        while(qry.next()){
             nb=nb+1;
        }
        return nb;

    }
    int Client::nbetat1(){

        QSqlQuery qry;
        int nb=0;
        qry.exec("select sexe from CLIENTS where sexe = 'Femme'");
        while(qry.next()){
             nb=nb+1;
        }
        return nb;

    }















