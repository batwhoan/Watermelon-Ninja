#include "mainwindow.h"
#include "karpuz.h"
#include <QLabel>
#include <QDebug>
#include <QPixmap>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
