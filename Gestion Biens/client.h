#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQueryModel>
#include <QDateEdit>
#include <QSqlQueryModel>
#include <QTextBrowser>
#include <QTextEdit>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>

class Client
{
public:
    //constricteur
    Client();
    Client(int,QString,QString,QString,QString,QString,int,QString);
        //getters
            int getIDCC();
            QString getNOM();
            QString getPRENOM();
            QString getSEXE();
            QString getDATENA();
            QString getMAIL();
            int getTELE();
            QString getDATEIN();
        //setters
            void setIDCC(int idc);
            void setNOM(QString nom);
            void setPRENOM(QString prenom);
            void setSEXE(QString sexe);
            void setDATENA(QString datena);
            void setMAIL(QString mail);
            void setTELE(int tele);
            void setDATEIN(QString datein);
         //fonctionalites

            //methode
            bool ajoutercl();
            QSqlQueryModel* affichercl();
            bool supprimercl(int);
            bool modifiercl(int idc);

            QSqlQueryModel * rechercher(QString);
            QSqlQueryModel *tri();
            int nbetat0();
            int nbetat1();
            void exporterpdf(QTextBrowser *text);


            //atribut
    private:
       int idc,tele;
       QString nom,prenom,sexe,mail,datena,datein;
    };

#endif // CLIENT_H
