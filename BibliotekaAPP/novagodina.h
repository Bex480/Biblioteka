#ifndef NOVAGODINA_H
#define NOVAGODINA_H

#include <QDialog>

namespace Ui {
class novagodina;
}

class novagodina : public QDialog
{
    Q_OBJECT

public:
    explicit novagodina(QWidget *parent = nullptr, QStringList s = {}, int br=0, int c=0, int c2=0);
    ~novagodina();

private slots:
    void on_pushButton_clicked();

private:
    Ui::novagodina *ui;
};

#endif // NOVAGODINA_H
