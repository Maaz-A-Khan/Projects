#include "orderinfo.h"
#include "ui_orderinfo.h"

OrderInfo::OrderInfo(const Order &order, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OrderInfo)
{
    ui->setupUi(this);
    this->setWindowTitle("Order Details");


    
    ui->orderId->setText(QString::number(order.getId()));
    ui->orderId->setReadOnly(true);
    

    
    ui->status->setText(QString::fromStdString(order.getStatus()));
    ui->status->setReadOnly(true);
    

    
    ui->address->setText(QString::fromStdString(order.getAddress()));
    ui->address->setReadOnly(true);
    

    
    ui->payMethod->setText(QString::fromStdString(order.getPayMethod()));
    ui->payMethod->setReadOnly(true);
    

    
    
    const auto& cart = order.getCart();
    ui->cartList->setColumnCount(4);
    ui->cartList->setHorizontalHeaderLabels({"Product Name", "Unit Price", "Quantity", "Subtotal"});
    ui->cartList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->cartList->setRowCount(static_cast<int>(cart.size()));

    for (int i = 0; i < static_cast<int>(cart.size()); ++i) {
        const OrderItem& item = cart[i];

        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(item.getName()));
        QTableWidgetItem* priceItem = new QTableWidgetItem(QString::number(item.getPrice(), 'f', 2));
        QTableWidgetItem* qtyItem = new QTableWidgetItem(QString::number(item.getQuantity()));
        QTableWidgetItem* subtotalItem = new QTableWidgetItem(QString::number(item.totalPrice(), 'f', 2));

        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        priceItem->setFlags(priceItem->flags() & ~Qt::ItemIsEditable);
        qtyItem->setFlags(qtyItem->flags() & ~Qt::ItemIsEditable);
        subtotalItem->setFlags(subtotalItem->flags() & ~Qt::ItemIsEditable);

        ui->cartList->setItem(i, 0, nameItem);
        ui->cartList->setItem(i, 1, priceItem);
        ui->cartList->setItem(i, 2, qtyItem);
        ui->cartList->setItem(i, 3, subtotalItem);
    }
}

OrderInfo::~OrderInfo()
{
    delete ui;
}
