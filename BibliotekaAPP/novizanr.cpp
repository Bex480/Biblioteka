#include "novizanr.h"
#include "ui_novizanr.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

noviZanr::noviZanr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::noviZanr)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/Resursi/Screenshot_1113.png"));
}

noviZanr::~noviZanr()
{
    delete ui;
}

void noviZanr::on_Dodaj_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Zanrovi VALUES (:id, :zanr)");

    query.bindValue(":zanr", ui->Naziv->text().simplified());

    query.exec();

    close();
}
