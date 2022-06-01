#ifndef IZMJENARAZREDA_H
#define IZMJENARAZREDA_H

#include <QDialog>

namespace Ui {
class izmjenarazreda;
}

class izmjenarazreda : public QDialog
{
    Q_OBJECT

public:
    explicit izmjenarazreda(QWidget *parent = nullptr, QStringList sl={}, QString s="", QString grupacija="");
    ~izmjenarazreda();

    QStringList list;

    void fill(QStringList list);

    QString razred_str;
    QString odjeljenje_str;

private slots:
    void on_finish_clicked();

private:
    Ui::izmjenarazreda *ui;
};

#endif // IZMJENARAZREDA_H
