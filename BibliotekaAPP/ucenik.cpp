#include "ucenik.h"
#include "ui_ucenik.h"


ucenik::ucenik(QWidget *parent, QStringList s) :
    QDialog(parent),
    ui(new Ui::ucenik)
{
    ui->setupUi(this);

    ui->razred->addItem("");
    ui->razred->addItems(s);

  setWindowIcon(QIcon(":/Resursi/Ucenik.png"));
  setWindowTitle("Dodavanje Ucenika");

}

ucenik::~ucenik()
{
    delete ui;
}

void ucenik::on_cancel_clicked()
{
    close();
}

void ucenik::on_dodaj_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlRelationalTableModel *model = new QSqlRelationalTableModel;

    model->setTable("Ucenici");

    db.transaction();

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

    QString i,p;
    i = ui->ime->text().toLower().simplified();
    i[0] = i[0].toUpper();
    p = ui->prezime->text().toLower().simplified();
    p[0] = p[0].toTitleCase();

    record.setValue("Ime",i);
    record.setValue("Prezime",p);
    record.setValue("Razred",ui->razred->currentText());
    record.setValue("Email", ui->email->text());
    record.setValue("Telefon",ui->telefon->text().simplified());

    if(!model->insertRecord(-1,record)){
        QMessageBox::warning(this,tr("Unos ucenika"),tr("Greska!"));
        db.rollback();

        qDebug() << db.lastError();
    }
    else{
        db.commit();
        QMessageBox::information(this,tr("Unos ucenika"),tr("Uspijesno unesen"));
    }

    close();

}

