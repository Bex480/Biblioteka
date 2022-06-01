#ifndef KNJIGA_H
#define KNJIGA_H

#include <QDialog>
#include <QSql>
#include <QtSql>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QModelIndex>
#include <QSqlDatabase>
#include <QSqlRelation>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include "mainwindow.h"
namespace Ui {
class knjiga;
}

class knjiga : public QDialog
{
    Q_OBJECT

public:
    explicit knjiga(QWidget *parent = nullptr, QStringList s = {});
    ~knjiga();

private slots:
    void on_nazad_clicked();

    void on_dodaj_clicked();

private:
    Ui::knjiga *ui;
};

#endif // KNJIGA_H
