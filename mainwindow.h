#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "karpuz.h"
#include "qtimer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int sayac=30;
    int kacakkarpuz=0;
    int kesilenkarpuz=0;
    int yuksekskor=0;
    int buttonX;
    int buttonY;

public slots:
    void yerDegistir();
    void karpuzolustur();
    void kagitOku();
    void kagitOku2();
    void kes();
    void YuksekSkor();
    void dosyayaz();
    void karpuzkac();

private:
    Ui::MainWindow *ui;
    QList <karpuz*> karpuz_list;
    QList <karpuz*> kesik_list;
    QList <QString> okunan_yeni;
    QList <QString> okunan_eski;
    QList <QString> okunan_skor;


};
#endif // MAINWINDOW_H
