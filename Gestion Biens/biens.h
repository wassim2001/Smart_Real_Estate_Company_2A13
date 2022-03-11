#ifndef BIENS_H
#define BIENS_H

#include <QString>
#include <QSqlQueryModel>

class Biens
{
public:
    //constructors
    Biens();
    Biens(int,QString  ,QString ,QString ,QString ,QString ,float ,float ,float ,int );
    //getters
        int getIDC();
        int getIDP();
        QString getDescription();
        QString getGov();
        QString getCity();
        QString getType();
        QString getListe();
        float getPrice();
        float getLatitude();
        float getLongititude();
    //setters
        void setIDC(int);
        void setIDP(int);
        void setDescription(QString);
        void setGov(QString);
        void setCity(QString);
        void setType(QString);
        void setListe(QString);
        void setPrice(float);
        void setLatitude(float);
        void setLongititude(float);
     //fonctionalites
        bool ajouter();
        QSqlQueryModel* afficher();
        bool supprimer(int);
        bool modifier(int idp);
private:
   int idc,idp;
   QString type,liste,description,governorate,city;
   double price,latitude,longititude;
};

#endif // BIENS_H
