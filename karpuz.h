#ifndef KARPUZ_H
#define KARPUZ_H

#include <QPushButton>
#include <QWidget>

class karpuz : public QPushButton
{
    Q_OBJECT
public:
    karpuz(QWidget *parrent=0);

public slots:
    void tikla();
};

#endif // KARPUZ_H
