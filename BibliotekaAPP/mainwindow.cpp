#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ucenik.h"
#include "ui_ucenik.h"
#include "knjiga.h"
#include "ui_knjiga.h"
#include "izmjena.h"
#include "ui_izmjena.h"
#include "ui_izmjenaknjiga.h"
#include "izmjenaknjiga.h"
#include "helpwindow.h"
#include "novagodina.h"
#include "ui_novagodina.h"
#include "novirazred.h"
#include "ui_novirazred.h"
#include "izmjenarazreda.h"
#include "ui_izmjenarazreda.h"
#include "uvod.h"
#include "novizanr.h"
#include "ui_novizanr.h"
#include "izmjenazanra.h"
#include "ui_izmjenazanra.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Connection();

    model = new QSqlRelationalTableModel;
    proxy = new QSqlRelationalTableModel;
    search = new QSortFilterProxyModel;
    search2 = new QSortFilterProxyModel;
    selected = new QItemSelectionModel;

    QSqlDatabase mydb = QSqlDatabase::database();
    model->setTable("Ucenici");
    model->select();
    model->sort(3, Qt::SortOrder::AscendingOrder);

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    ui->tableView->setSortingEnabled(true);

//    QSqlQuery query("SELECT * FROM Razredi");
//    QSqlRecord record;
//    query.exec();
//    while(query.next()){
//        record = query.record();
//        QTreeWidgetItem *item = new QTreeWidgetItem;
//        item->setText(0, record.value(1).toString());
//        ui->treeWidget->addTopLevelItem(item);
//    }

     PrePersonalizacija();

     funkcijaRazred();
     funkcijaZanr();

     setWindowIcon(QIcon(":/Resursi/Screenshot_1113.png"));
     setWindowTitle("Biblioteka");

//     if(ui->tableView->rowAt(1)==-1){
//     ui->detalji->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0); border-image: url(:/Resursi/Screenshot_1224.png);");
//     }

    ui->book_take->hide();
    ui->detalji->hide();
    ui->book_give->hide();
    ui->filtriranje_roka->hide();

  //DONT TOUCH!!!//
    setStyleSheet("QScrollBar:horizontal {border: 1px solid #999999; background:white; height:15px; margin: 0px 0px 0px 0px;""}"
        "QScrollBar::handle:horizontal {background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 rgba(175, 175, 175, 140), stop: 0.5 rgba(175, 175, 175, 140), stop:1 rgba(175, 175, 175, 140));"
        "min-width: 0px;}"
        "QScrollBar:vertical {border: 1px solid #999999; background:white; width:15px; margin: 0px 0px 0px 0px;""}"
        "QScrollBar::handle:vertical {background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 rgba(175, 175, 175, 140), stop: 0.5 rgba(175, 175, 175, 140), stop:1 rgba(175, 175, 175, 140));"
        "min-height: 0px;}");
  //DONT TOUCH!!!//

    ui->checkBox->setIcon(QIcon(":/Resursi/Screenshot_1262.png"));
    ui->checkBox_2->setIcon(QIcon(":/Resursi/crescent-moon-emoji.png"));

    hoce_li_pokazati();
    ui->tableView->setShowGrid(false);
    ui->detalji->setShowGrid(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Connection(){

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QMYSQL");
    mydb.setDatabaseName("bfijjqcpm7vlw3vochr9");


        mydb.setHostName("bfijjqcpm7vlw3vochr9-mysql.services.clever-cloud.com");
        mydb.setPort(3306);
        mydb.setUserName("uzttet4qqixril7s");
        mydb.setPassword("LuOxuE9fdDEpUYhd8WMN");

        bool OK = mydb.open();

        QString str;
        str = mydb.lastError().text();

        qDebug() <<str;
        qDebug() <<OK;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPixmap bkgnd;
    if(img=="Pozadina")
        bkgnd.load(":/Resursi/BibliotekaDruga.png");
    else
        bkgnd.load(":/Resursi/"+img+".png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->LE1->clear();
    ui->LE2->clear();
    ui->give_book->show();
    ui->book_give->hide();
    ui->take_book->show();
    ui->book_take->hide();

    model->setTable("Ucenici");

    QString f;
    f = item->text(column);
    QString c = f[0];
    int num = c.toInt();

    if(num > 0){
        f = "Razred like '"+int_to_Roman(num).simplified()+"-%'";
    }
    else {
        f = "Razred = '"+f+"'";
    }

    filter = f;
    model->setFilter(f);
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    ui->L1->setText("Ime:");
    ui->L2->setText("Prezime:");

//    if(ui->tableView->rowAt(0)==-1){
//        ui->tableView->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0); border-image: url(:/Resursi/Screenshot_1224.png);");
//        }
//        else
//        ui->tableView->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0);");

}

void MainWindow::on_treeWidget_2_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->LE1->clear();
    ui->LE2->clear();

    model->setTable("Knjige");

    QString f;
    f = item->text(column);

    if(f.contains("\u200E",Qt::CaseInsensitive)){
        f.remove("\u200E",Qt::CaseInsensitive);
    }

    f = "Zanr like '%"+f+"%'";

    model->setFilter(f);
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    ui->L1->setText("Knjiga:");
    ui->L2->setText("Autor:");

//    if(ui->tableView->rowAt(0)==-1){
//        ui->tableView->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0); border-image: url(:/Resursi/Screenshot_1224.png);");
//        }
//        else
//        ui->tableView->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0);");

}

void MainWindow::on_LE1_textChanged(const QString &arg1)
{
    argU = arg1;
    searchFunction();
}

void MainWindow::on_LE2_textChanged(const QString &arg1)
{
    argK = arg1;
    searchFunction();
}

void MainWindow::searchFunction()
{
      search2->setSourceModel(model);
      search2->setFilterCaseSensitivity(Qt::CaseInsensitive);
      search->setFilterCaseSensitivity(Qt::CaseInsensitive);

      search2->setFilterKeyColumn(1);
      search2->setFilterWildcard(argU.simplified());

      search->setSourceModel(search2);

      search->setFilterKeyColumn(2);
      search->setFilterWildcard(argK.simplified());

      ui->tableView->setModel(search);
      ui->tableView->hideColumn(0);
      ui->tableView->resizeColumnsToContents();
      ui->tableView->resizeRowsToContents();
}

void MainWindow::on_Dodaj_Ucenika_clicked()
{
    QStringList s;

    for(int i=0; i<ui->treeWidget->topLevelItemCount(); i++){
    QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);

    for(int j=0; j<item->childCount(); j++){
    s << item->child(j)->text(0);
    }
}

    ucenik u(this, s);
    u.exec();

    model->select();

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->tableView->selectRow(-1);

//    if(ui->tableView->rowAt(0)==-1){
//    ui->tableView->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0); border-image: url(:/Resursi/Screenshot_1224.png);");
//    }
//    else
//    ui->tableView->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0);");
}

void MainWindow::on_Dodaj_Knjigu_clicked()
{
    QStringList s;

    for(int i=0; i<ui->treeWidget_2->topLevelItemCount(); i++){
    QTreeWidgetItem *item = ui->treeWidget_2->topLevelItem(i);
    s << item->text(0);

}

    knjiga k(this, s);
    k.exec();

    model->select();

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

//    if(ui->tableView->rowAt(0)==-1){
//    ui->tableView->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0); border-image: url(:/Resursi/Screenshot_1224.png);");
//    }
//    else
//    ui->tableView->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0);");
}

void MainWindow::on_obrisi_clicked()
{
    selected = ui->tableView->selectionModel();
    QModelIndex rowIndex = selected->currentIndex();
    int rb=rowIndex.row();

    if(rb<0){
        return;
    }
    QMessageBox msgBox;
        msgBox.setText("Brisanje Sloga");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setInformativeText("Da li ste sigurni da zelite izbrisati ovaj slog?");
        msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        int odg=msgBox.exec();
        if(odg==QMessageBox::Yes)
        {
            model->removeRow(rb);
            model->submitAll();
    }
    else {
            model->revertAll();
        }

    model->select();
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    ui->LE1->clear();
    ui->LE2->clear();
}

void MainWindow::on_Izmjeni_clicked()
{
    selected = ui->tableView->selectionModel();
    QModelIndex rowIndex = selected->currentIndex();
    int rb=rowIndex.row();
    int id;
    QSqlRecord record;

    if(rb<0){
        return;
    }

    if(model->tableName() == "Ucenici"){

        QString ime;
        QString prezime;
        QString razred;
        QString email;
        QString telefon;

        if(ui->LE1->text().isEmpty() && ui->LE2->text().isEmpty()){
            id =model->index(rb,0).data().toInt();
            ime = model->index(rb,1).data().toString();
            prezime = model->index(rb,2).data().toString();
            razred = model->index(rb,3).data().toString();
            email = model->index(rb,4).data().toString();
            telefon = model->index(rb,5).data().toString();
        }else{
            id = search->index(rb,0).data().toInt();
            ime = search->index(rb,1).data().toString();
            prezime = search->index(rb,2).data().toString();
            razred = search->index(rb,3).data().toString();
            email = search->index(rb,4).data().toString();
            telefon = search->index(rb,5).data().toString();
        }


        izmjena i(this, id, ime, prezime, razred, email, telefon, rb);
        i.exec();

        model->select();
        ui->tableView->setModel(model);
        ui->tableView->hideColumn(0);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
    }

    if(model->tableName() == "Knjige"){

        QString naziv;
        QString autor;
        QString zanr;
        int kolicina;

        if(ui->LE1->text().isEmpty() && ui->LE2->text().isEmpty()){
            id =model->index(rb,0).data().toInt();
            naziv = model->index(rb,1).data().toString();
            autor = model->index(rb,2).data().toString();
            zanr = model->index(rb,3).data().toString();
            kolicina = model->index(rb,4).data().toInt();
        }else{
            id = search->index(rb,0).data().toInt();
            naziv = search->index(rb,1).data().toString();
            autor = search->index(rb,2).data().toString();
            zanr = search->index(rb,3).data().toString();
            kolicina = search->index(rb,4).data().toInt();
        }

        if(zanr.contains("\u200E",Qt::CaseInsensitive)){
            zanr.remove("\u200E",Qt::CaseInsensitive);
        }

        izmjenaKnjiga ik(this, id, naziv, autor, zanr, kolicina, rb);
        ik.exec();

        model->select();
        ui->tableView->setModel(model);
        ui->tableView->hideColumn(0);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
    }


}

void MainWindow::on_log_clicked()
{
    ui->rok->show();
    ui->log->hide();
    ui->filtriranje_roka->hide();
    otvori_drugu_tabelu();

    proxy->setTable("Log");

        proxy->setRelation(3, QSqlRelation("Ucenici", "IdUcenici", "Ime"));
        proxy->setRelation(4, QSqlRelation("Ucenici", "IdUcenici", "Prezime"));
        proxy->setRelation(5, QSqlRelation("Ucenici", "IdUcenici", "Razred"));
        proxy->setRelation(6, QSqlRelation("Knjige", "IdKnjige", "Naziv"));
        proxy->setRelation(7, QSqlRelation("Knjige", "IdKnjige", "Autor"));

        proxy->select();

        ui->detalji->setModel(proxy);
        ui->detalji->hideColumn(0);
        ui->detalji->hideColumn(1);
        ui->detalji->hideColumn(2);
        ui->detalji->hideColumn(10);
        ui->detalji->resizeColumnsToContents();
        ui->detalji->resizeRowsToContents();

        ui->detalji->scrollToBottom();
        if(ui->checkBox_2->isChecked())
        ui->detalji->setStyleSheet("QTableView {color: white; background-color: rgba(50, 50, 50, "+s+");};");
        else
        ui->detalji->setStyleSheet("QTableView {color: black; background-color: rgba(225, 225, 225, "+s+");};");
//    if(ui->detalji->rowAt(0)==-1){
//    ui->detalji->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0); border-image: url(:/Resursi/Screenshot_1224.png);");
//    }
//    else
//    ui->detalji->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0);");
}

void MainWindow::on_rok_clicked()
{
    ui->rok->hide();
    ui->log->show();
    ui->filtriranje_roka->show();
    otvori_drugu_tabelu();

    proxy->setTable("Rok");

    proxy->setRelation(1, QSqlRelation("Ucenici", "IdUcenici", "Ime"));
    proxy->setRelation(2, QSqlRelation("Ucenici", "IdUcenici", "Prezime"));
    proxy->setRelation(3, QSqlRelation("Ucenici", "IdUcenici", "Razred"));
    proxy->setRelation(4, QSqlRelation("Knjige", "IdKnjige", "Naziv"));
    proxy->setRelation(5, QSqlRelation("Knjige", "IdKnjige", "Autor"));

    proxy->select();

    ui->detalji->setModel(proxy);
    ui->detalji->hideColumn(0);
    ui->detalji->resizeColumnsToContents();
    ui->detalji->resizeRowsToContents();

    ui->detalji->scrollToBottom();
    if(ui->checkBox_2->isChecked())
    ui->detalji->setStyleSheet("QTableView {color: white; background-color: rgba(50, 50, 50, "+s+");};");
    else
    ui->detalji->setStyleSheet("QTableView {color: black; background-color: rgba(225, 225, 225, "+s+");};");
//    if(ui->detalji->rowAt(0)==-1){
//    ui->detalji->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0); border-image: url(:/Resursi/Screenshot_1224.png);");
//    }else
//    ui->detalji->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0);");
}

void MainWindow::on_Razredi_clicked()
{
    ui->LE1->clear();
    ui->LE2->clear();
    ui->give_book->show();
    ui->book_give->hide();
    ui->take_book->show();
    ui->book_take->hide();

    model->setTable("Ucenici");
    model->select();
    model->sort(3, Qt::SortOrder::AscendingOrder);

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    ui->L1->setText("Ime:");
    ui->L2->setText("Prezime:");

//    if(ui->tableView->rowAt(0)==-1){
//        ui->tableView->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0); border-image: url(:/Resursi/Screenshot_1224.png);");
//        }
//        else
//        ui->tableView->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0);");
}

void MainWindow::on_Knjige_clicked()
{
    ui->LE1->clear();
    ui->LE2->clear();
    model->setTable("Knjige");
    model->select();
    model->sort(2, Qt::SortOrder::AscendingOrder);

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    ui->L1->setText("Knjiga:");
    ui->L2->setText("Autor:");

//    if(ui->tableView->rowAt(0)==-1){
//        ui->tableView->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0); border-image: url(:/Resursi/Screenshot_1224.png);");
//        }
//        else
//        ui->tableView->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0);");
}

void MainWindow::on_take_book_clicked()
{
    if(model->tableName() != "Ucenici"){
        return;
    }

    selected = ui->tableView->selectionModel();
    QModelIndex rowIndex = selected->currentIndex();
    int rb=rowIndex.row();

    qDebug()<< rb;

    if(rb<0){
        return;
    }

    if(ui->LE1->text().isEmpty() && ui->LE2->text().isEmpty()){
        idU = model->index(rb,0).data().toInt();
    }else{
        idU = search->index(rb,0).data().toInt();
    }

    model->setTable("Knjige");
    model->select();
    model->sort(2, Qt::SortOrder::AscendingOrder);

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    ui->take_book->hide();
    ui->book_take->show();
    ui->LE1->clear();
    ui->LE2->clear();

    ui->L1->setText("Knjiga:");
    ui->L2->setText("Autor:");

}

void MainWindow::on_book_take_clicked()
{

    selected = ui->tableView->selectionModel();
    QModelIndex rowIndex = selected->currentIndex();
    int rb=rowIndex.row();

    QSqlRecord r2;
    QSqlQuery query;

    QDateTime time;

    int idK;

    if(ui->LE1->text().isEmpty() && ui->LE2->text().isEmpty()){
        idK = model->index(rb,0).data().toInt();
    }else{
        idK = search->index(rb,0).data().toInt();
    }

    QString s = QString::number(idK);

    query.exec("SELECT * FROM Log WHERE Bool = 1");
    while(query.next()){
        r2 = query.record();
        if(idU == r2.value(1) && idK == r2.value(2)){
            QMessageBox::warning(this,"Error!","Ovaj ucenik/ca je vec podigao/la ovu knjigu.");
            return;
        }
    }

    QSqlQuery query1("SELECT Kolicina FROM Knjige Where IdKnjige = "+s+"");
    query1.exec();
    query1.first();
    QSqlRecord record1 = query1.record();

    if(record1.value(0).toInt() <= 0){
        QMessageBox::warning(this,tr("Dizanje Knjige"),tr("Nema te knjige na stanju :D \n molim vas izaberite drugu knjigu"));
        model->revertAll();
        return;
    }

    query.prepare("UPDATE Knjige SET Kolicina = Kolicina - 1 WHERE idKnjige = :var");
    query.bindValue(":var",idK);
    query.exec();

    model->setTable("Log");

    QSqlRecord record = model->record();

    record.setValue("IdUcenika",idU);
    record.setValue("Ime",idU);
    record.setValue("Prezime",idU);
    record.setValue("Razred",idU);

    record.setValue("IdKnjiga",idK);
    record.setValue("Naziv",idK);
    record.setValue("Autor",idK);
    record.setValue("Vrijeme",time.currentDateTime());
    record.setValue("Status", "Podignuto");
    record.setValue("Bool",1);

    model->insertRecord(-1, record);

    model->setTable("Rok");

    record = model->record();

    record.setValue("Ime",idU);
    record.setValue("Prezime",idU);
    record.setValue("Razred",idU);

    record.setValue("Naziv",idK);
    record.setValue("Autor",idK);
    record.setValue("Rok",time.currentDateTime().addDays(14));

    model->insertRecord(-1, record);

    model->setTable("Ucenici");
    model->select();
    model->sort(3, Qt::SortOrder::AscendingOrder);

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    if(proxy->tableName() == "Log"){

        proxy->select();

        ui->detalji->setModel(proxy);
        ui->detalji->hideColumn(0);
        ui->detalji->hideColumn(1);
        ui->detalji->hideColumn(2);
        ui->detalji->hideColumn(10);
        ui->detalji->resizeColumnsToContents();
        ui->detalji->resizeRowsToContents();

    }else{

        proxy->select();

        ui->detalji->setModel(proxy);
        ui->detalji->hideColumn(0);
        ui->detalji->resizeColumnsToContents();
        ui->detalji->resizeRowsToContents();
    }

    ui->take_book->show();
    ui->book_take->hide();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    ui->detalji->show();

    int rb=index.row();
    int id;

    if(search->rowCount() >0){
        id = search->index(rb,0).data().toInt();
    }else{
        id = model->index(rb,0).data().toInt();
    }

    QString s = QString::number(id);
    QString f;

    if(model->tableName() == "Ucenici"){
         f = "IdUcenika = "+s+"";
    }else if(model->tableName() == "Knjige"){
         f = "IdKnjiga = "+s+" AND Bool = 1";
    }else if(model->tableName() != "Ucenici" && model->tableName() != "Knjige"){
        return;
    }

    proxy->setTable("Log");

    proxy->setRelation(3, QSqlRelation("Ucenici", "IdUcenici", "Ime"));
    proxy->setRelation(4, QSqlRelation("Ucenici", "IdUcenici", "Prezime"));
    proxy->setRelation(5, QSqlRelation("Ucenici", "IdUcenici", "Razred"));
    proxy->setRelation(6, QSqlRelation("Knjige", "IdKnjige", "Naziv"));
    proxy->setRelation(7, QSqlRelation("Knjige", "IdKnjige", "Autor"));

    proxy->select();
    proxy->setFilter(f);

    ui->detalji->setModel(proxy);
    ui->detalji->hideColumn(0);
    ui->detalji->hideColumn(1);
    ui->detalji->hideColumn(2);
    ui->detalji->hideColumn(10);
    ui->detalji->resizeColumnsToContents();
    ui->detalji->resizeRowsToContents();

//    if(ui->detalji->rowAt(0)==-1){
//        ui->detalji->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0); border-image: url(:/Resursi/Screenshot_1224.png);");
//        }
//        else
//        ui->detalji->setStyleSheet("background-color: rgba(225, 225, 225, 140); selection-background-color: rgb(85, 170, 255); selection-color: rgb(0, 0, 0);");

}

void MainWindow::on_close_detalji_clicked()
{
    ui->log->show();
    ui->rok->show();
    ui->detalji->hide();
    ui->filtriranje_roka->hide();
}

void MainWindow::on_give_book_clicked()
{

    if(model->tableName() != "Ucenici"){
        return;
    }

    selected = ui->tableView->selectionModel();
    QModelIndex rowIndex = selected->currentIndex();
    int rb=rowIndex.row();

    if(rb<0){
        return;
    }

    if(ui->LE1->text().isEmpty() && ui->LE2->text().isEmpty()){
        idU = model->index(rb,0).data().toInt();
    }else{
        idU = search->index(rb,0).data().toInt();
    }

    QString s = QString::number(idU);
    QString f = "IdUcenika = "+s+" AND Bool = 1";
    model->setTable("Log");

    model->setRelation(6, QSqlRelation("Knjige", "IdKnjige", "Naziv"));
    model->setRelation(7, QSqlRelation("Knjige", "IdKnjige", "Autor"));

    model->select();
    model->setFilter(f);
    model->sort(8, Qt::SortOrder::AscendingOrder);

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(1);
    ui->tableView->hideColumn(2);
    ui->tableView->hideColumn(3);
    ui->tableView->hideColumn(4);
    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(10);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    ui->give_book->hide();
    ui->book_give->show();
    ui->LE1->clear();
    ui->LE2->clear();

}

void MainWindow::on_book_give_clicked()
{

    selected = ui->tableView->selectionModel();
    QModelIndex rowIndex = selected->currentIndex();
    int rb=rowIndex.row();

    QSqlQuery query;

    QDateTime time;

    int idK;

    if(ui->LE1->text().isEmpty() && ui->LE2->text().isEmpty()){
        idK = model->index(rb,2).data().toInt();
    }else{
        idK = search->index(rb,2).data().toInt();
    }

    query.prepare("UPDATE Knjige SET Kolicina = Kolicina + 1 WHERE idKnjige = :var");
    query.bindValue(":var",idK);
    query.exec();
    query.prepare("UPDATE Log SET Bool = 0 WHERE IdUcenika = :idU AND IdKnjiga = :idK");
    query.bindValue(":idU", idU);
    query.bindValue(":idK", idK);
    query.exec();

    model->setTable("Log");

    QSqlRecord record = model->record();

    record.setValue("IdUcenika",idU);
    record.setValue("Ime",idU);
    record.setValue("Prezime",idU);
    record.setValue("Razred",idU);

    record.setValue("IdKnjiga",idK);
    record.setValue("Naziv",idK);
    record.setValue("Autor",idK);
    record.setValue("Vrijeme",time.currentDateTime());
    record.setValue("Status", "Vraceno");
    record.setValue("Bool",0);

    model->insertRecord(-1, record);

    query.prepare("DELETE FROM Rok WHERE Ime = :idU AND Naziv = :idK");
    query.bindValue(":idU",idU);
    query.bindValue(":idK",idK);
    query.exec();

    qDebug() << query.lastError();

    model->setTable("Ucenici");
    model->select();
    model->sort(3, Qt::SortOrder::AscendingOrder);

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    if(proxy->tableName() == "Log"){

        proxy->select();

        ui->detalji->setModel(proxy);
        ui->detalji->hideColumn(0);
        ui->detalji->hideColumn(1);
        ui->detalji->hideColumn(2);
        ui->detalji->hideColumn(10);
        ui->detalji->resizeColumnsToContents();
        ui->detalji->resizeRowsToContents();

    }else{

        proxy->select();

        ui->detalji->setModel(proxy);
        ui->detalji->hideColumn(0);
        ui->detalji->resizeColumnsToContents();
        ui->detalji->resizeRowsToContents();
    }

    ui->give_book->show();
    ui->book_give->hide();
}

void MainWindow::PrePersonalizacija()
{
    QFile file("PersonalizacijaSave.txt");
    if(!file.exists())
    {
        if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
            QMessageBox::warning(this,"Error","PersonalizacijaSave nije otvoren pri kreiranju!");
        QTextStream stream1(&file);
        stream1.seek(0);
        stream1<<"Providnost:175\n";
        stream1<<"Boja:0\n";
        stream1<<"Font:12\n";
    }else
    {
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
        QMessageBox::warning(this,"Error","PersonalizacijaSave nije otvoren!");}
    QTextStream stream(&file);
    stream.seek(11);
    QString providnost=stream.read(3);
    stream.seek(21);
    QString boja=stream.read(1);
    int boja2=boja.toInt();
    stream.seek(29);
    QString font=stream.read(2);

    if(boja=="1")
        ui->checkBox_2->setChecked(true);
    else
        ui->checkBox->setChecked(true);
    int providnost2=providnost.toInt()/2.5;
    QString providnost3=QString::number(providnost2);
    ui->Providnost->setCurrentText(""+providnost3+"%");
    ui->comboBox->setCurrentText(""+font+"");

    PostPersonalizacija(providnost, boja2);
    on_comboBox_currentTextChanged(font);
}

void MainWindow::PostPersonalizacija(QString provid, int boja)
{
    QString p=ui->Providnost->currentText();
    if(p=="Providnost")
      {
           int sq=provid.toInt();
           p=QString::number(sq/2.5);
      }
    if(p.contains("%"))
       p.chop(1);
    int n=p.toInt();
    int m=n*3.2;
    n=n*2.5;
    provid=QString::number(n);
    s=provid;
    QString d=QString::number(m);

    int pro=provid.toInt();
    if(pro<10)
        provid="00"+provid+"";
    else if(pro<100 && pro>=10)
        provid="0"+provid+"";
    QString fo=ui->comboBox->currentText();
    if(fo=="Veličina Fonta")
        fo="12";
    int fo2=fo.toInt();
    if(fo2<10)
        fo="0"+fo+"\n";

    QFile file("PersonalizacijaSave.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
        QMessageBox::warning(this,"Error","PersonalizacijaSave nije otvoren!");
    QTextStream stream(&file);
    QString bo=QString::number(boja);
    if(fo=="Veličina Fonta")
        fo="12";
    //int pos=stream.pos();
    stream.seek(11);
    stream<<""+provid+"\n";
    stream.seek(21);
    stream<<""+bo+"\n";
    stream.seek(29);
    stream<<""+fo+"\n";
    if(boja==1){
    ui->tableView->setStyleSheet("QTableView {color: white; background-color: rgba(50, 50, 50, "+provid+");}"
                                 "QHeaderView::section{color: white; background-color:black}"
                                 "QTableCornerButton::section{background-color:rgb(50, 50, 50)};");
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView{ background-color:black};");
    ui->tableView->verticalHeader()->setStyleSheet("QHeaderView{ background-color:black};");
    ui->detalji->setStyleSheet("QTableView {color: white; background-color: rgba(50, 50, 50, "+provid+");};");
    ui->treeWidget->setStyleSheet("QTreeWidget{color: white; background-color: rgba(50, 50, 50, "+provid+");};");
    ui->treeWidget_2->setStyleSheet("QTreeWidget{color: white; background-color: rgba(50, 50, 50, "+provid+");};");
    ui->Razredi->setStyleSheet("color: white; background-color: rgb(50, 50, 50);");
    ui->Knjige->setStyleSheet("color: white; background-color: rgb(50, 50, 50);");
    ui->L1->setStyleSheet("QLabel {color: white; background-color:rgb(50, 50, 50)};");
    ui->L2->setStyleSheet("QLabel {color: white; background-color:rgb(50, 50, 50)};");
    ui->LE1->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->LE2->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->Dugmad_3->setStyleSheet("background-color: rgba(50, 50, 50, 200);");
    ui->ZanrFrame->setStyleSheet("background-color: rgba(50, 50, 50, 200);");
    ui->Upravljanje_zanrovima->setStyleSheet("color: white; background-color: rgba(50, 50, 50, 200);");
    ui->Izmjeni->setStyleSheet("color: white; background-color:rgb(50, 50, 50); text-align:left;");
    ui->Dodaj_Knjigu->setStyleSheet("color: white; background-color:rgb(50, 50, 50); text-align:left;");
    ui->Dodaj_Ucenika->setStyleSheet("color: white; background-color:rgb(50, 50, 50); text-align:left;");
    ui->obrisi->setStyleSheet("color: white; background-color:rgb(50, 50, 50); text-align:left;");
    ui->log->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->rok->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->close_detalji->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->take_book->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->book_take->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->Dodaj_Zanr->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->Izm_Zanr->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->Obrisi_Zanr->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->give_book->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->book_give->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->label->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->label_2->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->label_4->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->Providnost->setStyleSheet("color: white; background-color: rgb(50, 50, 50);");
    ui->comboBox->setStyleSheet("color: white; background-color: rgb(50, 50, 50);");
    ui->Pozadina->setStyleSheet("color: white; background-color: rgb(50, 50, 50);");
    ui->Dodaj_Ucenika->setIcon(QIcon(":/Resursi/Screenshot_1231 - kopija.png"));
    ui->Dodaj_Knjigu->setIcon(QIcon(":/Resursi/Screenshot_1234 - kopija.png"));
    ui->obrisi->setIcon(QIcon(":/Resursi/Screenshot_1236 - kopija.png"));
    ui->Personalizacija_Frame->setStyleSheet("color: white; background-color: rgba(50, 50, 50, 140);");
    ui->Izmjeni->setIcon(QIcon(":/Resursi/EDITFINAL2 - kopija.png"));
    ui->rok->setIcon(QIcon(":/Resursi/Rok Ikonica Dan.png"));
    ui->log->setIcon(QIcon(":/Resursi/Log Icon Dan.png"));
    setStyleSheet("QScrollBar:horizontal {border: 1px solid #999999; background:black; height:15px; margin: 0px 0px 0px 0px;""}"
        "QScrollBar::handle:horizontal {background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 rgba(0, 0, 0, "+provid+"), stop: 0.5 rgba(0, 0, 0, "+provid+"), stop:1 rgba(0, 0, 0, "+provid+"));"
        "min-width: 0px;}"
        "QScrollBar:vertical {border: 1px solid #999999; background:white; width:15px; margin: 0px 0px 0px 0px;""}"
        "QScrollBar::handle:vertical {background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 rgba(0, 0, 0, "+provid+"), stop: 0.5 rgba(0, 0, 0, "+provid+"), stop:1 rgba(0, 0, 0, "+provid+"));"
        "min-height: 0px;}");
    ui->dodaj_raz->setIcon(QIcon(":/Resursi/Razred_Real_White.png"));
    ui->izmjena_razreda->setIcon(QIcon(":/Resursi/Edit_Razredi_Real_White.png"));
    ui->obrisi_razred->setIcon(QIcon(":/Resursi/Delete_Razredi_Real_White.png"));
    ui->frame->setStyleSheet("background-color: rgba(50, 50, 50, 200);");
    ui->dodaj_raz->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->izmjena_razreda->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->obrisi_razred->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->novaGodina->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");
    ui->label_3->setStyleSheet("color: white; background-color:rgb(50, 50, 50);");}
    else if(boja==0)
        {
        if(m>255)
            d="255";
           ui->tableView->setStyleSheet("QTableView {color: black; background-color: rgba(225, 225, 225, "+provid+");}"
                                        "QHeaderView::section{color: black; background-color:white}"
                                        "QTableCornerButton::section{background-color:rgb(255, 255, 255)};");
           ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView{ background-color:white};");
           ui->tableView->verticalHeader()->setStyleSheet("QHeaderView{ background-color:white};");
           ui->detalji->setStyleSheet("QTableView {color: black; background-color: rgba(225, 225, 225, "+provid+");};");
           ui->treeWidget->setStyleSheet("QTreeWidget{color: black; background-color: rgba(225, 225, 225, "+d+");};");
           ui->treeWidget_2->setStyleSheet("QTreeWidget{color: black; background-color: rgba(225, 225, 225, "+d+");};");
           ui->Razredi->setStyleSheet("color: black; background-color: rgb(255, 255, 255);;");
           ui->Knjige->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->L1->setStyleSheet("QLabel {color: black; background-color: rgb(255, 255, 255);};");
           ui->L2->setStyleSheet("QLabel {color: black; background-color:rgb(255, 255, 255);};");
           ui->LE1->setStyleSheet("color: black; background-color:rgb(255, 255, 255);");
           ui->LE2->setStyleSheet("color: black; background-color:rgb(255, 255, 255);");
           ui->Dugmad_3->setStyleSheet("background-color: rgba(225, 225, 225, 200);");
           ui->ZanrFrame->setStyleSheet("background-color: rgba(225, 225, 225, 200);");
           ui->Upravljanje_zanrovima->setStyleSheet("color: black; background-color: rgba(225, 225, 225, 200);");
           ui->Izmjeni->setStyleSheet("color: black; background-color: rgb(255, 255, 255); text-align:left;");
           ui->Dodaj_Knjigu->setStyleSheet("color: black; background-color: rgb(255, 255, 255); text-align:left;");
           ui->Dodaj_Ucenika->setStyleSheet("color: black; background-color: rgb(255, 255, 255); text-align:left;");
           ui->obrisi->setStyleSheet("color: black; background-color: rgb(255, 255, 255); text-align:left;");
           ui->log->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->rok->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->close_detalji->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->take_book->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->book_take->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->Dodaj_Zanr->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->Izm_Zanr->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->Obrisi_Zanr->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->give_book->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->book_give->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->label->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->label_2->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->label_4->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->Providnost->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->comboBox->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->Pozadina->setStyleSheet("color: black; background-color: rgb(255, 255, 255);");
           ui->Personalizacija_Frame->setStyleSheet("color: black; background-color: rgba(255, 255, 255, 140);");
           ui->Dodaj_Ucenika->setIcon(QIcon(":/Resursi/Screenshot_1231.png"));
           ui->Dodaj_Knjigu->setIcon(QIcon(":/Resursi/Screenshot_1234.png"));
           ui->obrisi->setIcon(QIcon(":/Resursi/Screenshot_1236.png"));
           ui->Izmjeni->setIcon(QIcon(":/Resursi/EDITFINAL2.png"));
           ui->rok->setIcon(QIcon(":/Resursi/Rok Icon.png"));
           ui->log->setIcon(QIcon(":/Resursi/Log Icon.png"));
           setStyleSheet("QScrollBar:horizontal {border: 1px solid #999999; background:black; height:15px; margin: 0px 0px 0px 0px;""}"
               "QScrollBar::handle:horizontal {background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 rgba(255, 255, 255, "+s+"), stop: 0.5 rgba(255, 255, 255, "+provid+"), stop:1 rgba(255, 255, 255, "+provid+"));"
               "min-width: 0px;}"
               "QScrollBar:vertical {border: 1px solid #999999; background:white; width:15px; margin: 0px 0px 0px 0px;""}"
               "QScrollBar::handle:vertical {background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 rgba(255, 255, 255, "+s+"), stop: 0.5 rgba(255, 255, 255, "+provid+"), stop:1 rgba(255, 255, 255, "+provid+"));"
               "min-height: 0px;}");
           ui->dodaj_raz->setIcon(QIcon(":/Resursi/Razred.png"));
           ui->izmjena_razreda->setIcon(QIcon(":/Resursi/Edit_Razredi.png"));
           ui->obrisi_razred->setIcon(QIcon(":/Resursi/Delete_Razredi.png"));
           ui->frame->setStyleSheet("background-color: rgba(225, 225, 225, 200);");
           ui->dodaj_raz->setStyleSheet("color: black; background-color:rgb(255, 255, 255);");
           ui->izmjena_razreda->setStyleSheet("color: black; background-color:rgb(255, 255, 255);");
           ui->obrisi_razred->setStyleSheet("color: black; background-color:rgb(255, 255, 255);");
           ui->novaGodina->setStyleSheet("color: black; background-color:rgb(255, 255, 255);");
           ui->label_3->setStyleSheet("color: black; background-color:rgb(255, 255, 255);");
        }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    PostPersonalizacija(s, 0);
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    PostPersonalizacija(s, 1);
}

void MainWindow::on_Providnost_textActivated(const QString &arg1)
{
    if(ui->checkBox_2->isChecked())
        on_checkBox_2_stateChanged(0);
    else if(ui->checkBox->isChecked())
        on_checkBox_stateChanged(0);
}

void MainWindow::on_Help_clicked()
{
    helpwindow *h=new helpwindow;
    h->show();
}

void MainWindow::on_novaGodina_clicked()
{
    int br = 0;
    QStringList s;

    for(int i=0; i<ui->treeWidget->topLevelItemCount(); i++){
    QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
    br += item->childCount();

    for(int j=0; j<item->childCount(); j++){
    s << item->child(j)->text(0);
    }
}
    int c2 = br - ui->treeWidget->topLevelItem(ui->treeWidget->topLevelItemCount()-1)->childCount();
    int c = ui->treeWidget->topLevelItem(0)->childCount();
    novagodina n(this,s,br,c,c2);
    n.exec();

}

void MainWindow::funkcijaRazred(){

    ui->treeWidget->clear();

    QSqlQuery query;
    QStringList s;
    QSqlRecord record;
    int num = 0;

    query.exec("SELECT DISTINCT Razred FROM Razredi");

    while(query.next()){
        record = query.record();
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, record.value(0).toString());
        ui->treeWidget->addTopLevelItem(item);
        s << item->text(0);
        num++;
    }

    QString fil;
    for(int j=0; j < num; j++){
        fil = "Razred = '"+s.at(j)+"'";
        query.exec("SELECT Odjeljenje FROM Razredi WHERE "+fil+"");

            while(query.next()){

                record = query.record();
                QTreeWidgetItem *child = new QTreeWidgetItem;
                child->setText(0, record.value(0).toString());
                ui->treeWidget->topLevelItem(j)->addChild(child);

        }

    }
    ui->treeWidget->sortItems(0,Qt::AscendingOrder);
}

void MainWindow::funkcijaZanr(){

    ui->treeWidget_2->clear();

    QSqlQuery query;
    QSqlRecord record;

    query.exec("SELECT DISTINCT nazivZanra FROM Zanrovi");

    while(query.next()){
        record = query.record();
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, record.value(0).toString());
        ui->treeWidget_2->addTopLevelItem(item);
    }
    ui->treeWidget_2->sortItems(0,Qt::AscendingOrder);
}

void MainWindow::on_dodaj_raz_clicked()
{
    treewidget_contents();

    noviRazred *nr = new noviRazred(this, stringlist_forwarded);
    nr->exec();

    funkcijaRazred();

}

void MainWindow::treewidget_contents(){

    QStringList sl;

    for(int i=0; i<ui->treeWidget->topLevelItemCount(); i++){

        sl << ui->treeWidget->topLevelItem(i)->text(0);
    }

    stringlist_forwarded = sl;
}

void MainWindow::treewidget2_contents(){

    QStringList sl;

    for(int i=0; i<ui->treeWidget_2->topLevelItemCount(); i++){

        sl << ui->treeWidget_2->topLevelItem(i)->text(0);
    }

    stringlist_forwarded = sl;
}

void MainWindow::on_obrisi_razred_clicked()
{
    QItemSelectionModel *selectedItem;
    selectedItem = ui->treeWidget->selectionModel();

    QModelIndex index = selectedItem->currentIndex();

    if(!index.isValid()){
        return;
    }

    //message box here

    QMessageBox box;
    box.setText("Jeste li sigurni da želite izbrisati ovaj razred?");
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setDefaultButton(QMessageBox::No);
    box.setStyleSheet("background-color: rgb(181, 181, 181);");
    box.setIcon(QMessageBox::Question);
    box.setWindowIcon(QIcon(":/Resursi/Screenshot_1283.png"));
    if(box.exec()==QMessageBox::Yes)
    {
    QString s = ui->treeWidget->itemFromIndex(index)->text(0);

    QSqlQuery query;

    query.exec("DELETE FROM Razredi WHERE Razred = '"+ s +"'");
    query.exec("DELETE FROM Ucenici WHERE Razred = '"+ s +"'");
    query.exec("DELETE FROM Razredi WHERE Odjeljenje = '"+ s +"'");

    funkcijaRazred();
    }
}

void MainWindow::on_izmjena_razreda_clicked()
{   
    QItemSelectionModel *selectedItem;
    selectedItem = ui->treeWidget->selectionModel();

    QModelIndex index = selectedItem->currentIndex();

    if(!index.isValid() or ui->treeWidget->itemFromIndex(index)->childCount()>0){
        return;
    }

    QString s = ui->treeWidget->itemFromIndex(index)->text(0);

    treewidget_contents();

    QString g = ui->treeWidget->itemFromIndex(index)->parent()->text(0);

    izmjenarazreda *raz = new izmjenarazreda(this, stringlist_forwarded, s, g);
    raz->exec();

    funkcijaRazred();

    model->setTable("Razredi");

    model->select();

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

QString MainWindow::int_to_Roman(int n) {

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

void MainWindow::hoce_li_pokazati()
{
  QFile file("dummy.txt");
  if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
      QMessageBox::warning(this,"Error","Dummy nije otvoren!");
  QTextStream stream(&file);
  QString linija=stream.readLine();
  if(linija.contains("."))
      return;
  Uvod *q=new Uvod;
  q->exec();
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    int h=arg1.toInt();
    QFont fontStandard("Segoe UI", h);
    if(ui->checkBox->isChecked())
    on_checkBox_stateChanged(0);
    else if(ui->checkBox_2->isChecked())
    on_checkBox_2_stateChanged(0);
    ui->tableView->setFont(fontStandard);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->detalji->setFont(fontStandard);
    ui->detalji->resizeColumnsToContents();
    ui->detalji->resizeRowsToContents();
}

void MainWindow::on_Dodaj_Zanr_clicked()
{
    noviZanr *z = new noviZanr;

    z->exec();

    funkcijaZanr();
}

void MainWindow::on_Obrisi_Zanr_clicked()
{
   QItemSelectionModel *selectedItem;
   selectedItem = ui->treeWidget_2->selectionModel();

   QModelIndex index = selectedItem->currentIndex();

   if(!index.isValid()){
        return;
    }

    //message box here
    QMessageBox box;
   box.setText("Jeste li sigurni da želite izbrisati ovaj žanr?");
   box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
   box.setDefaultButton(QMessageBox::No);
   box.setStyleSheet("background-color: rgb(181, 181, 181);");
   box.setIcon(QMessageBox::Question);
   box.setWindowIcon(QIcon(":/Resursi/Screenshot_1283.png"));
    if(box.exec()==QMessageBox::Yes)
    {
    QString s = ui->treeWidget_2->itemFromIndex(index)->text(0);

    QSqlQuery query;

    query.exec("DELETE FROM Zanrovi WHERE nazivZanra = '"+ s +"'");
    query.exec("DELETE FROM Knjige WHERE Zanr = '"+ s +"'");

    funkcijaZanr();
    }
}

void MainWindow::on_Izm_Zanr_clicked()
{
    QItemSelectionModel *selectedItem;
    selectedItem = ui->treeWidget_2->selectionModel();

    QModelIndex index = selectedItem->currentIndex();

    if(!index.isValid()){
        return;
    }

    QString s = ui->treeWidget_2->itemFromIndex(index)->text(0);

    treewidget2_contents();

    izmjenaZanra *i = new izmjenaZanra(this, s, stringlist_forwarded);

    i->exec();

    funkcijaZanr();

    model->setTable("Knjige");

    model->select();

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void MainWindow::otvori_drugu_tabelu(){

    ui->detalji->setVisible(true);
    if(ui->checkBox_2->isChecked())
    {  ui->detalji->setStyleSheet("QTableView {color: white; background-color: rgba(50, 50, 50, "+s+");"
                                  "            border-image: url(:/Resursi/Ucitavanje_Light.png);};");
    }else
    {ui->detalji->setStyleSheet("QTableView {color: black; background-color: rgba(225, 225, 225, "+s+");"
                                "            border-image: url(:/Resursi/Ucitavanje.png);};");
    }
}

void MainWindow::on_Pozadina_activated(const QString &arg1)
{
    img=ui->Pozadina->currentText();
    if(ui->Pozadina->currentText()=="Pozadina")
        return;
    QPixmap bkgnd(":/Resursi/Bijela Boja.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

void MainWindow::on_Pozadina_textActivated(const QString &arg1)
{
    img=ui->Pozadina->currentText();
    if(ui->Pozadina->currentText()=="Pozadina")
        return;
    QPixmap bkgnd(":/Resursi/"+img+".png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

void MainWindow::on_filtriranje_roka_stateChanged(int arg1)
{
    if(arg1==0){
        on_rok_clicked();
        return;
    }

    QDateTime dt;
    QSqlQuery query;
    QSqlRecord record;
    QString f = dt.currentDateTime().toString();

//    query.exec("SELECT * FROM Rok");



//    while(query.next()){
//        record = query.record();
//        dt2 = record.value(6).toDateTime();
//        if(dt2 < dt.currentDateTime()){

//        }
//    }


    query.exec("SELECT * FROM Rok WHERE Rok < '"+f+"'");
            qDebug() << query.lastError();

    while(query.next()){
        record = query.record();
        qDebug()<<record;
        qDebug() << "2";
    }

//    proxy->select();

//    ui->detalji->setModel(proxy);
//    ui->detalji->hideColumn(0);
//    ui->detalji->resizeColumnsToContents();
//    ui->detalji->resizeRowsToContents();

}
