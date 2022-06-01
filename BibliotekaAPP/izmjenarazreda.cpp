#include "izmjenarazreda.h"
#include "ui_izmjenarazreda.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

izmjenarazreda::izmjenarazreda(QWidget *parent, QStringList sl, QString s, QString grupacija) :
    QDialog(parent),
    ui(new Ui::izmjenarazreda)
{
    ui->setupUi(this);

    list = sl;
    razred_str = grupacija;
    odjeljenje_str = s;

    fill(list);

    ui->grupacija_select->setCurrentText(grupacija);

    int j=0;
    QString raz, od;

    for(int i=0; i<s.count(); i++){

        if(s[i] == '-'){
            j=i+1;
            break;
        }

        raz.append(s[i]);

    }

    ui->razred->setText(raz);

    for(int i=j; i<s.count(); i++){

        od.append(s[i]);

    }

    ui->odjeljenje->setText(od);

    setWindowTitle("Izmjena Razreda");
    setWindowIcon(QIcon(":/Resursi/Edit_Razredi.png"));
}

izmjenarazreda::~izmjenarazreda()
{
    delete ui;
}

void izmjenarazreda::fill(QStringList list){

    ui->grupacija_select->clear();

    for(int i=0; i<list.count(); i++){

        ui->grupacija_select->addItem(list.at(i));

    }

}

void izmjenarazreda::on_finish_clicked()
{
    QString s;
    s = ui->razred->text();
    s.append('-');
    s += ui->odjeljenje->text();

    QSqlQuery query;

    query.prepare("UPDATE Razredi SET Razred = '"+ui->grupacija_select->currentText()+"', Odjeljenje = '"+s+"' "
                    "WHERE Razred = '"+razred_str+"' AND "
                    "Odjeljenje = '"+odjeljenje_str+"'");

    query.exec();

    query.prepare("UPDATE Ucenici SET Razred = '"+s+"' "
                    "WHERE Razred = '"+odjeljenje_str+"'");

    query.exec();

    close();
}
