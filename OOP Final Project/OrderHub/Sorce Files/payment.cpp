#include "payment.h"
#include "ui_payment.h"
#include <QWidget>
#include <QMessageBox>
#include <QDebug>

Payment::Payment(Order& order, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Payment),
    ord(order),
    store(Store::getInstance())
{
    

    connect(this, &Payment::paymentCompleted, this, &Payment::onPaymentCompleted);

    Store* store = Store::getInstance();
    

    ui->setupUi(this);
    

    hideAllPaymentFields();

    const auto& cart = ord.getCart();
    

    ui->cartList->clear();
    ui->cartList->setRowCount(0);
    ui->cartList->setColumnCount(4);
    ui->cartList->setHorizontalHeaderLabels({"Name", "Unit Price", "Qty", "Sub-total"});
    ui->cartList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < static_cast<int>(cart.size()); ++i) {
        const OrderItem& it = cart[i];
        

        ui->cartList->insertRow(i);

        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(it.getName()));
        QTableWidgetItem* priceItem = new QTableWidgetItem(QString::number(it.getPrice(), 'f', 2));
        QTableWidgetItem* qtyItem = new QTableWidgetItem(QString::number(it.getQuantity()));
        QTableWidgetItem* subtotalItem = new QTableWidgetItem(QString::number(it.totalPrice(), 'f', 2));

        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        priceItem->setFlags(priceItem->flags() & ~Qt::ItemIsEditable);
        qtyItem->setFlags(qtyItem->flags() & ~Qt::ItemIsEditable);
        subtotalItem->setFlags(subtotalItem->flags() & ~Qt::ItemIsEditable);

        ui->cartList->setItem(i, 0, nameItem);
        ui->cartList->setItem(i, 1, priceItem);
        ui->cartList->setItem(i, 2, qtyItem);
        ui->cartList->setItem(i, 3, subtotalItem);
    }

    QString oTotal = QString::number(ord.calculateTotalPrice(), 'f', 2);
    
    ui->orderTotal->setText(oTotal);
}

void Payment::hideAllPaymentFields()
{
    
    ui->lcardnum->setVisible(false);
    ui->lexp->setVisible(false);
    ui->lcvv->setVisible(false);
    ui->cardnum->setVisible(false);
    ui->exp->setVisible(false);
    ui->cvv->setVisible(false);
    ui->accnum->setVisible(false);
    ui->laccnum->setVisible(false);
}

Payment::~Payment()
{
    
    delete ui;
}

void Payment::on_paymentType_currentIndexChanged(int index)
{
    
    hideAllPaymentFields();

    if (index == 1) {
        ui->lcardnum->setVisible(true);
        ui->lexp->setVisible(true);
        ui->lcvv->setVisible(true);
        ui->cardnum->setVisible(true);
        ui->exp->setVisible(true);
        ui->cvv->setVisible(true);
        
    } else if (index == 2 || index == 3) {
        ui->accnum->setVisible(true);
        ui->laccnum->setVisible(true);
        
    }
}

void Payment::on_placeOrder_clicked()
{
    
    int idx = ui->paymentType->currentIndex();
    PaymentMethod* payment = nullptr;
    QString err;
    bool ok = true;

    if (idx == 0) {
        
        payment = new CashPayment();
        ord.setPayMethod("Cash");
    } else if (idx == 1) {
        
        QString cardNo = ui->cardnum->text();
        QString exp = ui->exp->text();
        QString cvv = ui->cvv->text();

        QRegularExpression cardRegex("^\\d{16}$");
        QRegularExpression cvvRegex("^\\d{3}$");
        QRegularExpression expRegex("^(0[1-9]|1[0-2])/\\d{2}$");

        if (!cardRegex.match(cardNo).hasMatch()) {
            err += "Card number must be exactly 16 digits.\n";
            ok = false;
        }
        if (!cvvRegex.match(cvv).hasMatch()) {
            err += "CVV must be exactly 3 digits.\n";
            ok = false;
        }
        if (!expRegex.match(exp).hasMatch()) {
            err += "Expiry date must be in MM/YY format.\n";
            ok = false;
        }

        if (ok) {
            
            payment = new CardPayment(cardNo.toStdString(), exp.toStdString(), cvv.toStdString(), ord.calculateTotalPrice());
            ord.setPayMethod("Card");
        } else {
            
        }

    } else if (idx == 2 || idx == 3) {
        
        QString acc = ui->laccnum->text().trimmed();
        QRegularExpression accRegex("^03\\d{9}$");

        

        if (!accRegex.match(acc).hasMatch()) {
            err = "Account number must be 11 digits and start with 03.";
            ok = false;
        } else {
            if (idx == 2){
                payment = new EasyPaisaPayment(acc.toStdString());
                ord.setPayMethod("EasyPaisa");}
            else{
                payment = new JazzCashPayment(acc.toStdString());
                ord.setPayMethod("JazzCash");}

            
        }
    }

    if (!ok) {
        QMessageBox::warning(this, "Invalid data", err);
        return;
    }

    
    ord.setPaymentMethod(payment);
    store->addOrder(ord);

    QString msg = "Payment recorded, order placed.\n Order Id: " + QString::number(ord.getId());
    QMessageBox::information(this, "Success", msg);

    emit deleteOrder();
    emit paymentCompleted();
}

void Payment::onPaymentCompleted() {
    
    delete this;
}
