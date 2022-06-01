#ifndef NOVIRAZRED_H
#define NOVIRAZRED_H

#include <QDialog>

namespace Ui {
class noviRazred;
}

class noviRazred : public QDialog
{
    Q_OBJECT

public:
    explicit noviRazred(QWidget *parent = nullptr, QStringList sl={});
    ~noviRazred();

    void fill(QStringList list);

    QStringList list;

private slots:
    void on_dodaj_grupaciju_clicked();

    void on_finish_clicked();

private:
    Ui::noviRazred *ui;

    QString int_to_Roman(int n);
};

#endif // NOVIRAZRED_H
