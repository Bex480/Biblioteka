#ifndef UVOD_H
#define UVOD_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
namespace Ui {
class Uvod;
}

class Uvod : public QDialog
{
    Q_OBJECT

public:
    explicit Uvod(QWidget *parent = nullptr);
    ~Uvod();

private slots:

    void on_pushButton_clicked();

private:
    Ui::Uvod *ui;
    QFile file;
};

#endif // UVOD_H
