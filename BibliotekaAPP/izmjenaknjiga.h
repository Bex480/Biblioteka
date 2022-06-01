#ifndef IZMJENAKNJIGA_H
#define IZMJENAKNJIGA_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class izmjenaKnjiga;
}

class izmjenaKnjiga : public QDialog
{
    Q_OBJECT

public:
    explicit izmjenaKnjiga(QWidget *parent = nullptr, int id=0, QString naziv="", QString autor="", QString zanr="", int kolicina=0, int row=0);
    ~izmjenaKnjiga();

    int rb;
    int id2;


private slots:
    void on_nazad_clicked();

    void on_izmjeni_clicked();

private:
    Ui::izmjenaKnjiga *ui;
};

#endif // IZMJENAKNJIGA_H
