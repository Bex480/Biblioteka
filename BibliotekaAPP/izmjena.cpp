#include "izmjena.h"
#include "ui_izmjena.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

izmjena::izmjena(QWidget *parent, int id, QString ime, QString prezime, QString razred, QString email, QString telefon, int row, QString filter) :
    QDialog(parent),
    ui(new Ui::izmjena)
{
    ui->setupUi(this);

    ui->ime->setText(ime);
    ui->prezime->setText(prezime);
    ui->razred->setCurrentText(razred);
    ui->email->setText(email);
    ui->telefon->setText(telefon);

    rb = row;
    id2=id;
    f = filter;

    setWindowTitle("Izmjena Učenika");
    setWindowIcon(QIcon(":/Resursi/Screenshot_1237.png"));
}

izmjena::~izmjena()
{
    delete ui;
}

void izmjena::on_nazad_clicked()
{
    close();
}

void izmjena::on_izmjeni_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlRelationalTableModel *model = new QSqlRelationalTableModel;
    QSqlQuery query;

    model->setTable("Ucenici");

    QSqlRecord record = model->record();

    if(ui->ime->text().isEmpty()){
        QMessageBox::warning(this,tr("Unos ucenika"),tr("Ime učenika ne smije biti prazno!"));
        ui->ime->setStyleSheet("border: 1px solid red; background-color: rgb(255, 255, 255);");
        return;
    }
    else if(ui->prezime->text().isEmpty()){
        QMessageBox::warning(this,tr("Unos ucenika"),tr("Prezime učenika ne smije biti prazno!"));
        ui->prezime->setStyleSheet("border: 1px solid red; background-color: rgb(255, 255, 255);");
        return;
    }
    else if(ui->razred->currentText().isEmpty()){
        QMessageBox::warning(this,tr("Unos ucenika"),tr("Razred učenika ne smije biti prazan!"));
        ui->razred->setStyleSheet("border: 1px solid red; background-color: rgb(255, 255, 255);");
        return;
    }

    query.prepare("UPDATE Ucenici SET ime = :ime, prezime = :prezime, razred = :razred, email = :email, telefon = :telefon WHERE IdUcenici = :id");
    query.bindValue(":ime", ui->ime->text());
    query.bindValue(":prezime", ui->prezime->text());
    query.bindValue(":razred", ui->razred->currentText());
    query.bindValue(":email", ui->email->text());
    query.bindValue(":telefon", ui->telefon->text());
    query.bindValue(":id", id2);
    query.exec();

    close();

}
