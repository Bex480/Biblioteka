#include "izmjenazanra.h"
#include "ui_izmjenazanra.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

izmjenaZanra::izmjenaZanra(QWidget *parent, QString s, QStringList sl) :
    QDialog(parent),
    ui(new Ui::izmjenaZanra)
{
    ui->setupUi(this);

    naziv = s;

    ui->Naziv->setText(naziv);
}

izmjenaZanra::~izmjenaZanra()
{
    delete ui;
}

void izmjenaZanra::on_Izmjena_clicked()
{
    QString z;
    z = ui->Naziv->text().simplified();

    QSqlQuery query;

    query.prepare("UPDATE Zanrovi SET nazivZanra = '"+z+"' "
                    "WHERE nazivZanra = '"+naziv+"'");

    query.exec();

    query.prepare("UPDATE Knjige SET Zanr = '"+z+"' "
                    "WHERE Zanr = '"+naziv+"'");

    query.exec();

    close();
}

