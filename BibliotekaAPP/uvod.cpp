#include "uvod.h"
#include "ui_uvod.h"

Uvod::Uvod(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Uvod)
{
    ui->setupUi(this);
    this->close();
    ui->label->setStyleSheet("border-image: url(:/Resursi/Uvod 1.png);");
    file.setFileName("dummy.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox::warning(this, "Error!", "Dummy nije otvoren!");
    }
    setWindowIcon(QIcon(":/Resursi/Screenshot_1113.png"));
    setWindowTitle("Uvod");
}

Uvod::~Uvod()
{
    delete ui;
}

void Uvod::on_pushButton_clicked()
{
    if(ui->checkBox->isChecked())
      {  QTextStream stream(&file);
        stream<<"."; }
    this->close();
}
