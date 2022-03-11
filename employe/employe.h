#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQueryModel>
class Employe
{
public:
    Employe();
    Employe(int,QString,int,int,int,QString,QString,QString,int);
    int getid ();
    QString getposte ();
    int getsalaire();
    int getheures_de_travail();
    int getabsences();
    QString getnom ();
    QString getprenom ();
    QString getsexe ();
    int getage ();




    void setid (int);
    void setposte (QString);
    void setsalaire(int);
    void setheures_de_travail (int);
    void setabsences(int);
    void setnom (QString);
    void setprenom (QString);
    void setsexe (QString);
    void setage (int);

    bool ajouter();
    bool ajouter1();
    QSqlQueryModel* afficher();
bool supprimer(int);
bool modifier(int id);
QSqlQueryModel* afficher_id();



QString USERNAME;
QString PASSWORD;
private:
        int id;
        QString poste;
       int salaire,heures_de_travail,absences;
    QString nom, prenom, sexe;
    int age;

};

#endif // EMPLOYE_H
