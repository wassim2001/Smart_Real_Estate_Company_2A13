#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include <QMainWindow>
#include "statistique.h"
#include"arduino.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajoutcl_clicked();

    void on_supcl_clicked();

    void on_modifcl_clicked();

    void on_tabcl_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_stat_clicked();

    void update_label();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    Client CL;
    statistique *stat;
    QByteArray data;
    Arduino A;
};

#endif // MAINWINDOW_H
