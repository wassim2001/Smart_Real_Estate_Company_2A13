#include "mainwindow.h"
#include "connection.h"
#include "QMessageBox"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connection c;


    bool ok = c.createconnect();
    MainWindow w;
    if(ok)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("succes"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("fail"),
                    QObject::tr("problem.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    return a.exec();
}
