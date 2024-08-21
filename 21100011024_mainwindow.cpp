#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QDebug>
#include <QTimer>
#include <QtWidgets>
#include <QMessageBox>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <QFont>
// BATUHAN AYDOGDU 21100011024


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    kagitOku();
    kagitOku2();
    YuksekSkor();
    QTimer *timer= new QTimer(this);
    QTimer *timerkacan = new QTimer(this);
    timer->start(700);
    timerkacan->start(4000);
    connect(timer,QTimer::timeout,this,&MainWindow::karpuzolustur);
    connect(timer,QTimer::timeout,this,&MainWindow::yerDegistir);
    connect(timerkacan,QTimer::timeout,this,MainWindow::karpuzkac);
    YuksekSkor();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::yerDegistir()
{
    if(sayac>=0)
    {
        ui->lb_sayac->setText("SÜRE : <font color='cyan'>"+ QString::number(sayac)+"<font>");
        sayac--;
    }

    else
    {
        dosyayaz();
        QMessageBox::StandardButton cevap;
        if(kesilenkarpuz>yuksekskor)
        {
            yuksekskor=kesilenkarpuz;
            cevap = QMessageBox::information(this,"Bilgi!","Oyun Bitti TEBRİKLER MAKSİMUM SKORA ULAŞTINIZ""\n"
                                          "Kesilen Karpuz Sayısı: "
                                          +QString::number(kesilenkarpuz)+"\n"
                                          "Kaçırılan Karpuz Sayısı: "
                                          +QString::number(kacakkarpuz)+
                                          "\n""Maksimum Skor: "
                                          +QString::number(yuksekskor),QMessageBox::Ok);
            if(cevap==QMessageBox::Ok)
                this->close();

        }

        else
        {
            cevap = QMessageBox::information(this,"Bilgi!","Oyun Bitti""\n"
                                          "Kesilen Karpuz Sayısı:"
                                          +QString::number(kesilenkarpuz)+"\n"
                                          "Kaçırılan Karpuz Sayısı: "
                                          +QString::number(kacakkarpuz)+
                                          "\n""Maksimum Skor: "
                                          +QString::number(yuksekskor),QMessageBox::Ok);
            if(cevap==QMessageBox::Ok)
                this->close();

        }




        ui->lb_sayac->setText("SÜRE : BİTTİ");



    }
    for(int i=0;i<karpuz_list.size();i++)
    {
        karpuz_list[i]->setGeometry(karpuz_list[i]->x(),karpuz_list[i]->y()+50,100,100);
        if(karpuz_list[i]->y()>1080)
        {
            karpuz_list.remove(i);
            kacakkarpuz++;
            ui->lb_kacan->setText("KACAN KARPUZ: <font color='red'>"+ QString::number(kacakkarpuz)+"<font>");

        }

    }


}

void MainWindow::karpuzolustur()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int rand1=0+(std::rand() % (okunan_yeni.size()+1));
    int rand2=rand1+1;
    karpuz *karpuz1 = new karpuz(this);
    if(rand1%2==0)
    {
        karpuz1->setGeometry(okunan_yeni[rand1].toInt(),okunan_yeni[rand2].toInt(),100,100);
        karpuz1->setStyleSheet("border-image: url(:/resimler/images/fruit.png);");
        karpuz_list.push_back(karpuz1);
        karpuz1->show();
        connect(karpuz1,QPushButton::clicked,this,&MainWindow::kes);

    }


}

void MainWindow::kagitOku()
{
    QString konum_url = "C:/Users/batuh/Desktop/ODEV/21100011024_odev1/files/konumlar.txt";

    QFile konumdosyam(konum_url);
    if(!konumdosyam.open(QIODevice::ReadOnly | QIODevice::Text))
    {
    }

    QTextStream konumum(&konumdosyam);

    QString satir = konumum.readLine();
    while(!satir.isNull())
    {
        okunan_eski.append(satir);
        satir = konumum.readLine();
    }

    for(int a=0;a<okunan_eski.size();a++)
    {
        okunan_yeni.append(okunan_eski[a].split(" "));
    }


}

void MainWindow::kagitOku2()
{
    QString skor_url = "C:/Users/batuh/Desktop/ODEV/21100011024_odev1/files/skorlar.txt";

    QFile skordosyam(skor_url);
    if(!skordosyam.open(QIODevice::ReadWrite | QIODevice::Text))
    {
    }

    QTextStream skorum(&skordosyam);

    QString skorsatir = skorum.readLine();
    while(!skorsatir.isNull())
    {
        okunan_skor.append(skorsatir);
        skorsatir = skorum.readLine();
    }


}

void MainWindow::kes()
{
    karpuz* yerkarpuz = qobject_cast<karpuz*>(sender());
    int buttonX = yerkarpuz->x();
    int buttonY = yerkarpuz->y();
    yerkarpuz->hide();

    karpuz *karpuz2 = new karpuz(this);
    karpuz2->setGeometry(buttonX,buttonY,100,100);
    karpuz2->setStyleSheet("border-image: url(:/resimler/images/2.png);");
    kesik_list.push_back(karpuz2);
    kesilenkarpuz++;
    ui->lb_kesilen->setText("KESİLEN KARPUZ : <font color='green'>"+ QString::number(kesilenkarpuz)+"<font>");
    karpuz2->show();

}

void MainWindow::YuksekSkor()
{
    for(int h=0;h<okunan_skor.size();h++)
    {

        if(yuksekskor<okunan_skor[h].toInt())
        {
            yuksekskor=okunan_skor[h].toInt();
        }


    }

}

void MainWindow::dosyayaz()
{

    QString skor2_url = "C:/Users/batuh/Desktop/ODEV/21100011024_odev1/files/skorlar.txt";

    QFile skordosyam(skor2_url);
    if(skordosyam.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream strem(&skordosyam);
        strem <<"\n" << kesilenkarpuz;
        skordosyam.close();
    }



}

void MainWindow::karpuzkac()
{
    for(int k=0;k<kesik_list.size();k++)
    {
        kesik_list[k]->hide();
    }
}


























