#ifndef IZMJENAZANRA_H
#define IZMJENAZANRA_H

#include <QDialog>

namespace Ui {
class izmjenaZanra;
}

class izmjenaZanra : public QDialog
{
    Q_OBJECT

public:
    explicit izmjenaZanra(QWidget *parent = nullptr, QString s="", QStringList sl={});
    ~izmjenaZanra();

    QString naziv;

private slots:
    void on_Izmjena_clicked();

private:
    Ui::izmjenaZanra *ui;
};

#endif // IZMJENAZANRA_H
