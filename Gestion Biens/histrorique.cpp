#include "histrorique.h"

histrorique::histrorique()
{
    date=QDateTime::currentDateTime();

}
histrorique::histrorique(QString etat)
{

    date=QDateTime::currentDateTime();
    this->etat=etat;

}
void histrorique::ajouter_historique()
{
    QString HISTORIQUE="Client Ajouter";
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENTS (HISTORIQUE)"
                  "VALUES(:HISTORIQUE)");
    //query.bindValue(":etat",etat);
    query.bindValue(":HISTORIQUE",HISTORIQUE);

    query.exec();

/*
    query.prepare("INSERT INTO CLIENTS (idc, nom, prenom,sexe, datena, mail, tele, datein) "
                  "VALUES (:idc, :nom, :prenom,:sexe, :datena, :mail, :tele, :datein)");
*/

}


void histrorique::supprimer_historique()
{
    QString Client_supprimer;
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENTS VALUES(ID_HISTORIQUE.nextval,:etat,:DATE_HISTORIQUE ) ");
    query.bindValue(":etat",etat);
    query.bindValue(":DATE_HISTORIQUE",date.toString());

    query.exec();


}

void histrorique::update_historique()
{
    QString Client_update;
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENTS VALUES(ID_HISTORIQUE.nextval,:etat,:DATE_HISTORIQUE ) ");
    query.bindValue(":etat",etat);
    query.bindValue(":DATE_HISTORIQUE",date.toString());

    query.exec();


}

/*
void histrorique::setEtat(QString etat)
{
    this->etat=etat;
}
*/
QSqlQueryModel * histrorique::afficherHistorique()
{
    QSqlQueryModel * model= new QSqlQueryModel();


        model->setQuery("select ETAT,DATE_HISTORIQUE FROM HISTORIQUE order by id_historique DESC ;");



    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ETAT"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date"));


    return model;
}
