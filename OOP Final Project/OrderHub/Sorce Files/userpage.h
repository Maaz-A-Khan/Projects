#ifndef USERPAGE_H
#define USERPAGE_H
#include "store.h"
#include <QWidget>

namespace Ui {
class userPage;
}

class userPage : public QWidget
{
    Q_OBJECT

public:
    explicit userPage(User& user,QWidget *parent = nullptr);
    ~userPage();

signals:
    void cartUpdated(const Order&);
    void logoutSignal();
public slots:
    void onPaymentFinished();

private slots:
    void on_tabWidget_tabBarClicked(int index);
    void on_placeOrder_clicked();
    void on_logout_clicked();

private:
    Ui::userPage *ui;
    User currentUser;
    Order order;
    void populateCartTable(const Order& ord);
    vector<Product>* prods;
};
#endif
