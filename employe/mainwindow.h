#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<employe.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_clicked();

    void on_pb_modifier_2_clicked();

    void on_pb_ajouter_1_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Employe E;
};
#endif // MAINWINDOW_H
