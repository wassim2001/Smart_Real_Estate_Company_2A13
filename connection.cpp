#include "connection.h"

connection::connection()
{

}

bool connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");//inserer le nom de la source de données ODBC
db.setUserName("adem");//inserer nom de l'utilisateur
db.setPassword("adem");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}


