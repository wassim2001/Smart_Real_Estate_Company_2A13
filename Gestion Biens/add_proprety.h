#ifndef ADD_PROPRETY_H
#define ADD_PROPRETY_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>

namespace Ui {
class Add_proprety;
}

class Add_proprety : public QDialog
{
    QString description,governorate,city,type,liste;
    int idc,idp;
    float price,latitude,longititude;
    Q_OBJECT

public:
    explicit Add_proprety(QWidget *parent = nullptr);
    ~Add_proprety();
    void title();

    //constructors
    //Add_proprety(){}
    Add_proprety(int,int,QString,QString,QString,QString,QString,float,float,float);

    //Getters
    int getIDC(int idc){return idc;}
    int getIDP(int idp){return idp;}
    QString getDescription(){return description;}
    QString getGov(){return governorate;}
    QString getCity(){return city;}
    QString getType(){return type;}
    QString getListe(){return liste;}

    //Setters
    void setIDC(int idc){this->idc=idc;}
    void setIDP(int idp){this->idp=idp;}
    void setDescription(QString d){description=d;}
    void setGov(QString g){description=g;}
    void setCity(QString c){description=c;}
    void setType(QString t){description=t;}
    void setListe(QString l){description=l;}
    //fonctionnalites
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer();
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Add_proprety *ui;
};

#endif // ADD_PROPRETY_H
