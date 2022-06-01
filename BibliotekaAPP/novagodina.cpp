#include "novagodina.h"
#include "ui_novagodina.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

novagodina::novagodina(QWidget *parent, QStringList s, int br, int c, int c2) :
    QDialog(parent),
    ui(new Ui::novagodina)
{
    ui->setupUi(this);

    for(int i=0; i<c2; i++){
    QComboBox *cb1 = new QComboBox;
    cb1->addItems(s);
    cb1->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    ui->gridLayout->addWidget(cb1);
    cb1->setCurrentIndex(i);
    }

    for(int i=c; i<br; i++){
    QComboBox *cb1 = new QComboBox;
    cb1->addItems(s);
    cb1->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    ui->gridLayout_2->addWidget(cb1);
    cb1->setCurrentIndex(i);
    }

    for(int i=0; i<c2; i++){
    QLabel *l = new QLabel;
    l->setText("⟶");
    ui->gridLayout_3->addWidget(l);
    }

}

novagodina::~novagodina()
{
    delete ui;
}

void novagodina::on_pushButton_clicked()
{

}

