#include "karpuz.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>


karpuz::karpuz(QWidget *parrent): QPushButton(parrent)
{
    connect(this,QPushButton::clicked,this,&karpuz::tikla);
}

void karpuz::tikla()
{

}
