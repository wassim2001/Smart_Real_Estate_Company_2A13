#include "contrat.h"

Contrat::Contrat()
{
    id_contrat=0;
id_agence=0;cin="";id_produit=0;
type="";
}

Contrat::Contrat(int id_Contrat,int id_Agence,QString Cin,int id_Produit,QDate Date_contrat,QString Type)
{
    id_contrat=id_Contrat;
    id_agence=id_Agence;cin=Cin;id_produit=id_Produit;
    type=Type;
    date_contrat.setDate(Date_contrat.year(),Date_contrat.month(),Date_contrat.day());
}

bool Contrat::ajouter(){
    QSqlQuery query;
    query.prepare("INSERT INTO CONTRAT (ID_AGENCE,CIN,ID_PRODUIT,DATE_CONTRAT,TYPE) "
                        "VALUES (:ID_AGENCE,:CIN,:ID_PRODUIT,:DATE_CONTRAT,:TYPE)");
    query.bindValue(":ID_AGENCE", id_agence);
    query.bindValue(":CIN", cin);
    query.bindValue(":ID_PRODUIT", id_produit);
    query.bindValue(":DATE_CONTRAT",date_contrat);
    query.bindValue(":TYPE", type);
    return    query.exec();
}

bool Contrat::envoyerMessage(int idEMP,QString contenu){
    QSqlQuery query;
    query.prepare("INSERT INTO MESSAGE (CONTENU,DATE_ENVOI,ID_EMP_DEST) "
                        "VALUES (:ID_AGENCE,:CIN,:ID_PRODUIT)");
    query.bindValue(":ID_AGENCE", contenu);
    query.bindValue(":CIN", QDate::currentDate());
    query.bindValue(":ID_PRODUIT", idEMP);
    return    query.exec();
}


bool Contrat::supprimer(int id)
{
QSqlQuery query;
query.prepare("Delete from CONTRAT where ID_CONTRAT = :id ");
query.bindValue(":id", id);
return    query.exec();
}


bool Contrat::modifier()
{   QSqlQuery query;
    query.prepare( "UPDATE CONTRAT SET ID_AGENCE=:ID_AGENCE,CIN=:CIN,ID_PRODUIT=:ID_PRODUIT,DATE_CONTRAT=:DATE_CONTRAT,TYPE=:TYPE WHERE ID_CONTRAT=:id");
    query.bindValue(":ID_AGENCE", id_agence);
    query.bindValue(":CIN", cin);
    query.bindValue(":ID_PRODUIT", id_produit);
    query.bindValue(":DATE_CONTRAT",date_contrat);
    query.bindValue(":TYPE", type);
        query.bindValue(":id", id_contrat);

    return query.exec();
}



QSqlQueryModel * Contrat::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from CONTRAT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id contrat"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("id agence"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id produit"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date de contrat"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("type"));

    return model;
}

QSqlQueryModel * Contrat::messagesEnvoyees()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from MESSAGE");//where .....
    return model;
}

QSqlQueryModel * Contrat::triType()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from CONTRAT ORDER BY TYPE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id contrat"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("id agence"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id produit"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date de contrat"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("type"));

    return model;
}

QSqlQueryModel * Contrat::triProduit()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from CONTRAT ORDER BY ID_PRODUIT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id contrat"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("id agence"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id produit"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date de contrat"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("type"));

    return model;
}

QSqlQueryModel * Contrat::recherche(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from CONTRAT WHERE CIN LIKE '%"+a+"%' OR ID_PRODUIT LIKE '%"+a+"%' OR ID_AGENCE LIKE '%"+a+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id contrat"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("id agence"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id produit"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date de contrat"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("type"));

    return model;
}

QSqlQueryModel * Contrat::triDate()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from CONTRAT ORDER BY DATE_CONTRAT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id contrat"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("id agence"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("id produit"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date de contrat"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("type"));

    return model;
}

QSqlQueryModel * Contrat::getEMP()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from EMPLOYEE");
    return model;
}


bool Contrat::contratexist(int id){
    QSqlQueryModel * model= new QSqlQueryModel();
    QString res= QString::number(id);
    model->setQuery("select * from CONTRAT WHERE ID_CONTRAT="+res);
    return  model->rowCount();
}

