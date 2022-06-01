#include "novirazred.h"
#include "ui_novirazred.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

noviRazred::noviRazred(QWidget *parent, QStringList sl) :
    QDialog(parent),
    ui(new Ui::noviRazred)
{
    ui->setupUi(this);

    list = sl;

    fill(list);

    setWindowTitle("Dodaj Razred");
    setWindowIcon(QIcon(":/Resursi/Razred.png"));
}

noviRazred::~noviRazred()
{
    delete ui;
}

void noviRazred::on_dodaj_grupaciju_clicked()
{
    if(ui->nova_grupacija->text().isEmpty()){
        return;
    }

    QString s;
    s += ui->nova_grupacija->text();
    s += ".Razredi";

    list << s;

    fill(list);

}

void noviRazred::fill(QStringList list){

    ui->grupacija_select->clear();

    for(int i=0; i<list.count(); i++){

        ui->grupacija_select->addItem(list.at(i));

    }

}

void noviRazred::on_finish_clicked()
{
    QString s;

    int num = ui->razred->text().toInt();

    if(num > 0){
        s += int_to_Roman(num);
    }
    else {
        s += ui->razred->text();
    }

    s += "-";
    s += ui->odjeljenje->text();

    QSqlQuery query;
    query.prepare("INSERT INTO Razredi VALUES (:id, :raz, :od)");

    query.bindValue(":raz", ui->grupacija_select->currentText());
    query.bindValue(":od", s);

    query.exec();

    close();

}

QString noviRazred::int_to_Roman(int n) {

        QString str_romans[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

        QString result = "";

        for (int i = 0; i < 13; ++i)
        {
            while(n - values[i] >= 0)
            {
                result += str_romans[i];
                n -= values[i];
            }
        }

        return result;
    }
