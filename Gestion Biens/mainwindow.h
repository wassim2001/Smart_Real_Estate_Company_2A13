#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "biens.h"
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void title();

private slots:
     //void on_pushButton_clicked();

     void on_valider_clicked();

     void on_sup_button_clicked();

     void on_modif_button_clicked();

     void on_pushButton_clicked();

     void on_lineEdit_textChanged(const QString &arg1);

     //void on_pushButton_2_clicked();

     void sendMail();

         void mailSent(QString) ;

         void on_envoyer_clicked();


         void on_locate_clicked();

         void on_search_textChanged(const QString &arg1);

         void on_comboBox_2_currentTextChanged(const QString &arg1);
         void update_label();


         void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Biens B;
    QByteArray data; // variable contenant les données reçues
    Arduino A;
signals:
     void setCenter(QVariant, QVariant);
     void addMarker(QVariant, QVariant);
};
#endif // MAINWINDOW_H
