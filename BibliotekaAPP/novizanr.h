#ifndef NOVIZANR_H
#define NOVIZANR_H

#include <QDialog>

namespace Ui {
class noviZanr;
}

class noviZanr : public QDialog
{
    Q_OBJECT

public:
    explicit noviZanr(QWidget *parent = nullptr);
    ~noviZanr();

private slots:
    void on_Dodaj_clicked();

private:
    Ui::noviZanr *ui;
};

#endif // NOVIZANR_H
