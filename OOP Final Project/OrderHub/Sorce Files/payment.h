#ifndef PAYMENT_H
#define PAYMENT_H
#include "store.h"
#include <QWidget>
using namespace std;

namespace Ui {
class Payment;
}

class Payment : public QWidget
{
    Q_OBJECT

public:
    explicit Payment(Order& order,QWidget *parent = nullptr);
    ~Payment();
    void hideAllPaymentFields();
signals:
    void orderPlacedSuccessfully();
    void paymentCompleted();
    void deleteOrder();
public slots:
    void onPaymentCompleted();

private slots:
    void on_paymentType_currentIndexChanged(int index);

    void on_placeOrder_clicked();

private:
    Ui::Payment *ui;
    Order& ord;
    Store* store;
};

#endif
