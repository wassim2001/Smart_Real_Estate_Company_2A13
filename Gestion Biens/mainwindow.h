#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include <QMainWindow>
#include "biens.h"
#include "employe.h"
#include "arduino.h"
#include "statistique.h"
#include "histrorique.h"
#include <QPainter>
#include <QtPrintSupport/QPrinter>

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
     void refresh();
     void clear();

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

         /*------------dom----------*/
         void on_ajoutcl_clicked();

         void on_supcl_clicked();

         void on_modifcl_clicked();

         void on_tabcl_activated(const QModelIndex &index);


         void on_pushButton_2dom_clicked();

         void on_pushButton_3dom_clicked();

         void on_pushButton_statdom_clicked();

         void update_label1();

         //void on_pushButton_4dom_clicked();

          void exporterpdf(QTextBrowser *text);


          void on_pushButton_6dom_clicked();


          //void on_pushButton_dom6_clicked();

          //void on_pushButton_dom3_clicked();

          void on_pushButtondom_clicked();

          void on_pushButton_4dom_clicked();
          /*--------------damergi---------------*/
          void on_pushButton_ajouterContrat_clicked();

          void on_pushButton_supprimerContrat_clicked();

          void on_pushButton_modifierContrats_clicked();

          void on_lineEdit_idsuppmodifContrat_textChanged(const QString &arg1);

          //void on_lineEdit_textChangedDa(const QString &arg1);

         // void on_pushButton_clickedDa();

          void on_pushButton_pdf_clicked();

         // void on_pushButton_3_clicked();

          void on_pushButton_Da_clicked();

          void on_lineEdit_12_textChanged(const QString &arg1);

          void on_pb_ajouter_1_clicked();

          void on_pb_modifier_2Em_clicked();

          void on_pushButton_suppEm_clicked();

          void on_pb_trier_sexe_clicked();

          void on_pb_trier_salaire_clicked();

          void on_pb_trirer_poste_clicked();

          void on_chercher_clicked();

          void on_pb_age_stat_clicked();

          void on_pushButton_imagesk_clicked();

private:
    Ui::MainWindow *ui;
    Biens B;
    QByteArray data; // variable contenant les données reçues
    Arduino A;


    /*---------dom--------*/
    Client CL;
    statistique *stat;
    /*---------dom-------*/
    /*---------skan----------*/
    Employe E;
    /*-----------------------*/
signals:
     void setCenter(QVariant, QVariant);
     void addMarker(QVariant, QVariant);
};
#endif // MAINWINDOW_H
