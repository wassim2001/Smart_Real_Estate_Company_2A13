#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void refresh();
    void clear();
    ~MainWindow();

private slots:
    void on_pushButton_ajouterContrat_clicked();

    void on_pushButton_supprimerContrat_clicked();

    void on_pushButton_modifierContrats_clicked();

    void on_lineEdit_idsuppmodifContrat_textChanged(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_pdf_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
