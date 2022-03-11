#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    Client CL;
};

#endif // MAINWINDOW_H
