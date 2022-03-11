#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "biens.h"

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

private:
    Ui::MainWindow *ui;
    Biens B;
};
#endif // MAINWINDOW_H
