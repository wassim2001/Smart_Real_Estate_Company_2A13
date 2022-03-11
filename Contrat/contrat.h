#ifndef CONTRAT_H
#define CONTRAT_H
#include <QString>
#include <QSqlQueryModel>

class Contrat
{
public:
    Contrat();
    Contrat(int ,int ,QString ,QString ,int ,int );
    int getNumero();
    int getId();
    QString getType();
    QDate getDate();
    int getCIN();
    int getBien();

    void setNumero (int);
    void setId (int);
    void setType (QString);
    void setDate (QString);
    void setCIN (int);
    void setBien (int);

    bool ajouter();
            QSqlQueryModel* afficher();
            bool supprimer(int);
            bool modifier(int Numero);


            bool ajouter1();
            QSqlQueryModel* afficher();

    bool supprimer (int);
    bool modifier(int Numero,int Id,QString Type,QString Date,int CIN,int Bien);
    QSqlQueryModel* afficher_id();

    QSqlQueryModel* afficher_Numero(int );
    QSqlQueryModel* afficher_Id(int );
    QSqlQueryModel* afficher_Type(QString );
    QSqlQueryModel* afficher_Date(QString );
    QSqlQueryModel* afficher_CIN(int );
    QSqlQueryModel* afficher_Bien(int );


    //QString Date; int Numero,CIN;

private:
    int Numero,Id,CIN,Bien;
    QString Type, Date;
};

#endif // CONTRAT_H
