#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QWidget>
#include<QTableWidgetItem>
#include "store.h"
#include <vector>
#include "orderinfo.h"

namespace Ui {
class adminPage;
}

class adminPage : public QWidget
{
    Q_OBJECT

public:
    explicit adminPage(QWidget *parent = nullptr);
    void onItemChanged(QTableWidgetItem *item);
    void populateProdList();
    void populateOrdList();
    ~adminPage();
    void on_tabWidget_tabBarClicked(int index);


private slots:


    void on_logout_clicked();

    void on_pushButton_clicked();

private:
    vector<Product>* prods;
    Ui::adminPage *ui;
};

#endif
