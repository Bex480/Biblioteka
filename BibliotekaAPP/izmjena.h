#ifndef IZMJENA_H
#define IZMJENA_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class izmjena;
}

class izmjena : public QDialog
{
    Q_OBJECT

public:
    explicit izmjena(QWidget *parent = nullptr, int id=0, QString ime = "", QString prezime = "", QString razred = "", QString email = "", QString telefon = "", int row = 0, QString filter="");
    ~izmjena();

    int rb;
    int id2;
    QString f;

private slots:
    void on_nazad_clicked();

    void on_izmjeni_clicked();

private:
    Ui::izmjena *ui;
};

#endif // IZMJENA_H
