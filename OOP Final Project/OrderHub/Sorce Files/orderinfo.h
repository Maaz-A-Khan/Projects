#ifndef ORDERINFO_H
#define ORDERINFO_H

#include <QWidget>
#include "store.h"

namespace Ui {
class OrderInfo;
}

class OrderInfo : public QWidget
{
    Q_OBJECT

public:
    explicit OrderInfo(const Order&order, QWidget *parent = nullptr);
    ~OrderInfo();

private:
    Ui::OrderInfo *ui;
};

#endif
