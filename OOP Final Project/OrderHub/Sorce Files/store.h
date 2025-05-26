#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include<QString>

using namespace std;

class Product{
    static int nextId;
    int id;
    string name;
    float price;
public:
    Product(string n="", float p=0);
    Product(int i,string n, float p);
    void setName(string n);
    void setPrice(float p);
    int getId()const;
    string getName()const;
    float getPrice()const;
    virtual void display()const;
};


class OrderItem: public Product{
    int quantity;
public:
    OrderItem(string n="",float p=0, int q=0);
    OrderItem(int i,string n,float p, int q);
    int getQuantity()const;
    float totalPrice()const;
    int getId() const;
    void display() const;
    void setQuantity(int q);
};

class PaymentMethod{
protected:
    string paymentType;
    float amountPaid;

public:
    string getPaymentType()const;
    float getAmountPaid()const;
    virtual void pay(float amount) = 0;
    virtual ~PaymentMethod();
    void setPaymentType(string type);
};

class CardPayment : public PaymentMethod {
    string cardNumber;
    string expiry;
    string cvv;

public:
    CardPayment(string cn, string exp, string cvv,float amt);
    CardPayment();
    void pay(float amount);
};

class CashPayment : public PaymentMethod {
public:
    CashPayment();
    void pay(float amount);
};

class EasyPaisaPayment : public PaymentMethod {
    string accountNumber;
public:
    EasyPaisaPayment(string acc);
    EasyPaisaPayment();
    void pay(float amount);
};

class JazzCashPayment : public PaymentMethod {
    string accountNumber;
public:
    JazzCashPayment(string acc);
    JazzCashPayment();

    void pay(float amount);
};

class Order{
    static int nextId;
    int orderId, userId;
    string address;
    string status;
    vector<OrderItem> cart;
    PaymentMethod* paymentMethod;
    string payMethod;


public:
    Order(int uid);
    ~Order();
    const vector<OrderItem>& getCart() const ;
    int getId() const;
    int getUserId() const;
    string getAddress()const;
    string getStatus() const ;
    string getPaymentType() const;
    PaymentMethod* getPaymentMethod() const;
    void removeItem(int productId);
    void decreaseQuantity(int productId);
    void increaseQuantity(int productId);
    void setStatus(string stat);
    void setAddress(string add);
    void setPaymentMethod(PaymentMethod* pm);
    void addItem(const Product& product, int quantity);    
    void clearOrder();
    void addItem(OrderItem item);
    float calculateTotalPrice() const;
    void display() const;
    void addItemToCart(OrderItem item);
    void setPayMethod(string method);
    string getPayMethod()const;
};


class Store{
private:
    vector<Product> products;
    vector<Order> orders;
    Store();
    void loadProducts();
    void loadOrders();

public:
    static Store* getInstance();

    Store(Store const&) = delete;
    Store(Store&&) = delete;
    Store& operator=(Store const&) = delete;
    Store& operator=(Store&&) = delete;

    ~Store();
    vector<Product>* allProducts();
    vector<Order>* allOrders();
    void saveProducts();

    void saveOrders();
    void addProduct(const Product& p);
    void addOrder(Order o);

    void editProduct(int id, const string& newName, float newPrice);

    Product* getProductById(int id);
    void displayProducts();
    void displayOrders();
    void displayUserOrders(int userId) const ;
    void updateOrderStatus(int orderId, const string& status);
    void trackOrder(int orderId);


};
class Admin{
public:
    void viewProducts(Store& store);
    void addProduct(Store& store);
    void editProduct(Store& store);
    void updateOrderStatus(Store& store);
};

class User{

    int id;
    string name;
public:
    static int nextUid;
    User( string n="");
    User(int i,string n="");
    int getId() const;
    string getName() const;
    void viewProducts(Store& store);
    void placeOrder(Store& store);
    void trackOrder(Store& store);
    void viewMyOrders(Store& store);
};

int authenticator(QString username,QString password);

#endif
