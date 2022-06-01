#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QtSql>
#include <QDebug>
#include <QPalette>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QModelIndex>
#include <QSqlDatabase>
#include <QSqlRelation>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTreeWidgetItem>
#include <QPainter>
#include <QTreeView>
#include <QTreeWidget>
#include <QIdentityProxyModel>
#include <QGraphicsOpacityEffect>
#include <QGraphicsEffect>
#include <QWheelEvent>
#include <QAbstractProxyModel>
#include <QDialog>
#include <QFont>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Connection();

    void paintEvent(QPaintEvent *event);

    QString filter;

    int idU;

    void searchFunction();
    QString argU,argK;

    void treewidget_contents();

    void treewidget2_contents();

    QStringList stringlist_forwarded;

    void otvori_drugu_tabelu();

private slots:

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_2_itemClicked(QTreeWidgetItem *item, int column);

    void on_LE1_textChanged(const QString &arg1);

    void on_LE2_textChanged(const QString &arg1);

    void on_Dodaj_Ucenika_clicked();

    void on_Dodaj_Knjigu_clicked();

    void on_obrisi_clicked();

    void on_Izmjeni_clicked();

    void on_log_clicked();

    void on_rok_clicked();

    void on_Razredi_clicked();

    void on_Knjige_clicked();

    void on_take_book_clicked();

    void on_book_take_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_close_detalji_clicked();

    void on_give_book_clicked();

    void on_book_give_clicked();

    void on_checkBox_2_stateChanged(int arg1);

    void PrePersonalizacija();

    void PostPersonalizacija(QString provid, int boja);

    void on_Providnost_textActivated(const QString &arg1);

    void on_Help_clicked();

    void on_novaGodina_clicked();

    void funkcijaRazred();

    void funkcijaZanr();

    void on_dodaj_raz_clicked();

    void on_obrisi_razred_clicked();

    void on_izmjena_razreda_clicked();

    void hoce_li_pokazati();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_Dodaj_Zanr_clicked();

    void on_Obrisi_Zanr_clicked();

    void on_Izm_Zanr_clicked();

    void on_Pozadina_activated(const QString &arg1);

    void on_Pozadina_textActivated(const QString &arg1);

    void on_filtriranje_roka_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *proxy;

    QSortFilterProxyModel *search;
    QSortFilterProxyModel *search2;

    QItemSelectionModel *selected;

    QModelIndex index;
    QModelIndex proxyIndex;

    QString int_to_Roman(int n);
    QString s="125";

    QString img="Pozadina";

};
#endif // MAINWINDOW_H
