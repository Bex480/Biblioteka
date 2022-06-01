#include "izmjenaknjiga.h"
#include "ui_izmjenaknjiga.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

izmjenaKnjiga::izmjenaKnjiga(QWidget *parent, int id, QString naziv, QString autor, QString zanr, int kolicina, int row) :
    QDialog(parent),
    ui(new Ui::izmjenaKnjiga)
{
    ui->setupUi(this);

    ui->naziv->setText(naziv);
    ui->autor->setText(autor);
    ui->zanr->setCurrentText(zanr);
    QString s = QString::number(kolicina);
    ui->kolicina->setText(s);

    rb = row;
    id2=id;

    setWindowTitle("Izmjena Knjige");
    setWindowIcon(QIcon(":/Resursi/Screenshot_1237.png"));

}

izmjenaKnjiga::~izmjenaKnjiga()
{
    delete ui;
}

void izmjenaKnjiga::on_nazad_clicked()
{
    close();
}

void izmjenaKnjiga::on_izmjeni_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlRelationalTableModel *model = new QSqlRelationalTableModel;
    QSqlQuery query;

    model->setTable("Knjige");

    QSqlRecord record = model->record();

    if(ui->naziv->text().isEmpty()){
        QMessageBox::warning(this,tr("Izmjena Knjige"),tr("Naziv knjige ne smije biti prazno!"));
        ui->naziv->setStyleSheet("border: 1px solid red; background-color: rgb(255, 255, 255);");
        return;
    }
    else if(ui->autor->text().isEmpty()){
        QMessageBox::warning(this,tr("Izmjena Knjige"),tr("Autor Knjige ne smije biti prazno!"));
        ui->autor->setStyleSheet("border: 1px solid red; background-color: rgb(255, 255, 255);");
        return;
    }
    else if(ui->zanr->currentText().isEmpty()){
        QMessageBox::warning(this,tr("Izmjena Knjige"),tr("Zanr Knjige ne smije biti prazan!"));
        ui->zanr->setStyleSheet("border: 1px solid red; background-color: rgb(255, 255, 255);");
        return;
    }

    query.prepare("UPDATE Knjige SET naziv = :naziv, autor = :autor, zanr = :zanr, kolicina = :kolicina WHERE IdKnjige = :id");
    query.bindValue(":naziv", ui->naziv->text());
    query.bindValue(":autor", ui->autor->text());
    query.bindValue(":zanr", ui->zanr->currentText());
    query.bindValue(":kolicina", ui->kolicina->text());
    query.bindValue(":id", id2);
    query.exec();

    close();
}
