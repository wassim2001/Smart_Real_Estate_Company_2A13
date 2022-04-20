#ifndef AGENCE_H
#define AGENCE_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Contrat
{
private:
    int id_contrat,id_agence,id_produit;
    QString cin,type;
    QDate date_contrat;
public:
    Contrat();
    Contrat(int,int,QString,int,QDate,QString);
    bool ajouter();
    bool envoyerMessage(int ,QString );
   QSqlQueryModel * messagesEnvoyees();
    QSqlQueryModel * afficher();
   QSqlQueryModel * triDate();
   QSqlQueryModel * triType();
   QSqlQueryModel * triProduit();
   QSqlQueryModel * getEMP();
   QSqlQueryModel * recherche(QString);
    bool supprimer(int);
    bool modifier();
    bool contratexist(int);
};

#endif // AGENCE_H
