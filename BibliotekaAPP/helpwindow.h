#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
namespace Ui {
class helpwindow;
}

class helpwindow : public QDialog
{
    Q_OBJECT

public:
    explicit helpwindow(QWidget *parent = nullptr);
    ~helpwindow();

private slots:


    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void Ispis(QString a, int phase);

    void on_Minus_clicked();

    void on_Plus_clicked();

private:
    Ui::helpwindow *ui;
    QString koja;
    QString s=":/Resursi/UnosUcenika.txt";
    QFile file;
    int pozicija, proslaPozicija, proslaProslaPozicija;
    float phase2;
};

#endif // HELPWINDOW_H
