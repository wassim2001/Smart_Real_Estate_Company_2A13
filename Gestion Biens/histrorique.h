#ifndef HISTRORIQUE_H
#define HISTRORIQUE_H
#include <QDateTime>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class histrorique
{
public:
    histrorique();
    histrorique(QString);
    void setEtat(QString);

    void ajouter_historique();
    void supprimer_historique();
    void update_historique();
    QSqlQueryModel * afficherHistorique();

private:
    QString etat;
    QDateTime date;
};

#endif // HISTRORIQUE_H
