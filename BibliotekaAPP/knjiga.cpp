#include "knjiga.h"
#include "ui_knjiga.h"

knjiga::knjiga(QWidget *parent, QStringList s) :
    QDialog(parent),
    ui(new Ui::knjiga)
{
    ui->setupUi(this);

    ui->Zanr->addItem("");
    ui->Zanr->addItems(s);

    setWindowIcon(QIcon(":/Resursi/Screenshot_1233.png"));
    setWindowTitle("Dodavanje Knjiga");

    clearFocus();
}

knjiga::~knjiga()
{
    delete ui;
}

void knjiga::on_nazad_clicked()
{
    close();
}

void knjiga::on_dodaj_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlRelationalTableModel *model = new QSqlRelationalTableModel;

    model->setTable("Knjige");
    model->select();

    db.transaction();

    QSqlRecord record = model->record();

    QString n,a;
    n = ui->naziv->text().toLower().simplified();
    n[0] = n[0].toUpper();

    record.setValue("Naziv",n);
    record.setValue("Autor",ui->autor->text().simplified());
    record.setValue("Zanr",ui->Zanr->currentText().simplified());
    record.setValue("Kolicina",ui->kolicina->text().simplified());
    record.setValue("ISBN",ui->isbn->text().simplified());

    if(ui->naziv->text().isEmpty()){
        QMessageBox::warning(this,tr("Unos knjige"),tr("Naziv knjige ne smije biti prazno!"));
        ui->naziv->setStyleSheet("border: 1px solid red; background-color: rgb(255, 255, 255);");
        return;
    }
    else if(ui->autor->text().isEmpty()){
        QMessageBox::warning(this,tr("Unos knjige"),tr("Autor knjige ne smije biti prazno!"));
        ui->autor->setStyleSheet("border: 1px solid red; background-color: rgb(255, 255, 255);");
        return;
    }
    else if(ui->Zanr->currentText().isEmpty()){
        QMessageBox::warning(this,tr("Unos knjige"),tr("Zanr knjige ne smije biti prazan!"));
        ui->Zanr->setStyleSheet("border: 1px solid red; background-color: rgb(255, 255, 255);");
        return;
    }
    else if(ui->kolicina->text().isEmpty()){
        QMessageBox::warning(this,tr("Unos knjige"),tr("Kolicina knjige ne smije biti prazan!"));
        ui->kolicina->setStyleSheet("border: 1px solid red; background-color: rgb(255, 255, 255);");
        return;
    }


    if(!model->insertRecord(-1,record)){
        QMessageBox::warning(this,tr("Unos nove knjige"),tr("Greska!"));
        db.rollback();

        qDebug() << db.lastError();
    }
    else{
        db.commit();
        QMessageBox::information(this,tr("Unos nove knjige"),tr("Uspijesno unesena"));
    }

    close();
}

