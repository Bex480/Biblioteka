#include "helpwindow.h"
#include "ui_helpwindow.h"

helpwindow::helpwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpwindow)
{
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("border-image: url(:/Resursi/Screenshot_1302.png);");
    ui->pushButton_2->setStyleSheet("border-image: url(:/Resursi/Screenshot_1303.png);");
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->label_2->hide();
    ui->textEdit->hide();
    ui->label->hide();
    ui->textEdit->setReadOnly(true);
    ui->Plus->hide();
    ui->Minus->hide();
    file.setFileName(":/Resursi/Tekst.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this,"Error!", "Text file ne postoji!");
    }
    setWindowIcon(QIcon(":/Resursi/Screenshot_1282.png"));
}

helpwindow::~helpwindow()
{
    delete ui;
}

void helpwindow::Ispis(QString a, int phase)
{   phase2=phase;
    QTextStream stream(&file);
    stream.seek(0);
    bool l=false;
    QString linija;
    ui->textEdit->clear();
    QString phasePic=QString::number(phase2), br="4";
    while(!stream.atEnd())
    {
        linija=stream.readLine();
        if(linija.contains(a))
        {
            l=true;
            if(linija.contains("three"))
                br="3";
            else if(linija.contains("five"))
                br="5";
            continue;
       }
       if(linija.startsWith("#"))
            ui->textEdit->clear();
       if(!linija.endsWith("$") && l==true && phase!=0)
       {
           linija.remove("#");
           ui->textEdit->append(linija);
       }
       if(linija.endsWith("$") && l==true)
           phase--;
       if(linija.endsWith("$") && l==true && phase==0)
       {
           linija.remove("$");
           linija.remove("#");
           ui->textEdit->append(linija);
           break;
       }
    }
    if(br=="3" && phase2==3)
        ui->pushButton->hide();
    else if(br=="3" && phase2==2)
        ui->pushButton->show();
    else if(br=="5" && phase2==5)
        ui->pushButton->hide();
    else if(br=="5" && phase2==4)
        ui->pushButton->show();
    ui->label_2->setStyleSheet("border-image: url(:/Resursi/Counter " +br+ "-" +phasePic+ ".png)");
    ui->label->setStyleSheet("border-image: url(:/Resursi/" +koja+ " " +phasePic+ ".png)");
}

void helpwindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QString a=item->text(column);
    if(a.contains(":"))
        return;
    ui->pushButton->show();
    ui->pushButton_2->hide();
    ui->label_2->show();
    ui->textEdit->show();
    ui->label->show();
    ui->Minus->show();
    ui->Plus->show();
    if(a.contains("č") || a.contains("ć"))
    {
        a.replace("č", "c");
        a.replace("ć", "c");
    }
    koja=a;
    Ispis(a, 1);
}

void helpwindow::on_pushButton_clicked()
{
    if(phase2==3)
        ui->pushButton->hide();
    if(phase2==1)
        ui->pushButton_2->show();
    Ispis(koja, phase2+1);
}

void helpwindow::on_pushButton_2_clicked()
{
    if(phase2==2)
    {ui->pushButton->show();
     ui->pushButton_2->hide();
    }
    if(phase2==4)
        ui->pushButton->show();
    if(phase2==2)
        ui->pushButton_2->hide();
    if(phase2==4)
            ui->pushButton->show();

    Ispis(koja, phase2-1);
}


void helpwindow::on_Minus_clicked()
{
    ui->textEdit->zoomOut();
}

void helpwindow::on_Plus_clicked()
{
    ui->textEdit->zoomIn();
}
