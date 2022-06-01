#ifndef UCENIK_H
#define UCENIK_H

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
#include <QIcon>
#include <QTreeWidget>
namespace Ui {
class ucenik;
}

class ucenik : public QDialog
{
    Q_OBJECT

public:
    QTreeWidget tw;
    explicit ucenik(QWidget *parent = nullptr, QStringList s = {});
    ~ucenik();

private slots:
    void on_cancel_clicked();

    void on_dodaj_clicked();

private:
    Ui::ucenik *ui;
};

#endif // UCENIK_H
