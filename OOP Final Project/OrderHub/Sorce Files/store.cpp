#include "store.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int Product::nextId=1;

Product::Product(string n, float p): id(nextId++), name(n), price(p) {}
Product::Product(int i, string n, float p)
    : id(i), name(std::move(n)), price(p) {
    if (i >= nextId) nextId = i + 1;
}

void Product::setName(string n){name=n;}


void Product::setPrice(float p){price=p;}
int Product::getId()const{return id;	}
string Product::getName()const{return name;	}
float Product::getPrice()const{return price;	}
void Product::display()const{
    cout<<"Name: "<<name<<endl<<"Price per unit: "<<price<<endl;
}
int OrderItem::getId() const {
    return Product::getId(); 
}
void OrderItem::setQuantity(int q) {
    this->quantity = q;
}
OrderItem::OrderItem(int i,string n,float p, int q): Product(i,n,p), quantity(q){

}
OrderItem::OrderItem(string n,float p, int q): Product(n,p), quantity(q){

}

int OrderItem::getQuantity()const{return quantity;}
float OrderItem::totalPrice()const{return getPrice()*quantity;}
void OrderItem::display() const{
    Product::display();
    cout<<"Subtotal: "<<totalPrice()<<endl;
}


string PaymentMethod::getPaymentType()const{return paymentType;}
float PaymentMethod::getAmountPaid()const{return amountPaid;}
void PaymentMethod::setPaymentType(string type){paymentType=type;}
PaymentMethod::~PaymentMethod(){}
CardPayment::CardPayment(){

}

CardPayment::CardPayment(string cn, string exp, string cvv,float amt) {
    cardNumber=cn;
    expiry=exp;
    this->cvv=cvv;
    amountPaid=amt;
    paymentType = "Card";
}

void CardPayment::pay(float amount){
    cout << "Enter Card Number: ";
    cin >> cardNumber;
    cout << "Enter Expiry Date (MM/YY): ";
    cin >> expiry;
    cout << "Enter CVV: ";
    cin >> cvv;
    amountPaid = amount;
    cout << "Card payment of Rs. " << amount << " processed successfully.\n";
}


CashPayment::CashPayment() {
    paymentType = "Cash";
    amountPaid = 0;
}

void CashPayment::pay(float amount){
    amountPaid = amount;
    cout << "Cash on delivery of Rs." << amount <<"selected" << endl;

}
EasyPaisaPayment::EasyPaisaPayment() {
}
EasyPaisaPayment::EasyPaisaPayment(string acc) {
    accountNumber=acc;
    paymentType = "EasyPaisa";
    amountPaid = 0;
}

void EasyPaisaPayment::pay(float amount){
    amountPaid = amount;
    cout << "Enter EasyPaisa Account Number: ";
    cin >> accountNumber;
    cout << "EasyPaisa payment of Rs." << amount << " processed successfully.\n";
}

JazzCashPayment::JazzCashPayment(){

}
JazzCashPayment::JazzCashPayment(string acc) {
    accountNumber=acc;
    paymentType = "JazzCash";
    amountPaid = 0;
}

void JazzCashPayment::pay(float amount){
    amountPaid = amount;
    cout << "Enter JazzCash Account Number: ";
    cin >> accountNumber;
    cout << "JazzCash payment of Rs." << amount << " processed successfully.\n";
}



Order::Order(int uid){
    orderId=nextId++;
    userId=uid;
    status="Pending";
    paymentMethod = nullptr;
    payMethod="";
}

Order::~Order(){
    delete paymentMethod;
}
const vector<OrderItem>& Order::getCart() const { return cart; }
int Order::getId() const{return orderId;}
int Order::getUserId() const{return userId;}
string Order::getAddress() const {return address;}
string Order::getStatus() const {return status;}
string Order::getPaymentType() const{return paymentMethod->getPaymentType();}
PaymentMethod* Order::getPaymentMethod() const{return paymentMethod;}


void Order::setStatus(string stat){status=stat;}
void Order::setAddress(string add){address=add;}
void Order::setPaymentMethod(PaymentMethod* pm){
    paymentMethod = pm;
}
void Order::setPayMethod(string method){payMethod=method;}
string Order::getPayMethod()const{return payMethod;}

void Order::addItem(OrderItem item){
    cart.push_back(item);
}

void Order::addItemToCart(OrderItem item) {
    for (auto& i : cart) {
        if (item.getId() == i.getId()) {
            i.setQuantity(i.getQuantity() + item.getQuantity());
            return;  
        }
    }
    cart.push_back(item);  
}


void Order::decreaseQuantity(int productId) {
    for (auto it = cart.begin(); it != cart.end(); ++it) {
        if (it->Product::getId() == productId) {
            int newQty = it->getQuantity() - 1;
            if (newQty <= 0)
                cart.erase(it);
            else
                it->setQuantity(newQty);
            return;
        }
    }
}

void Order::increaseQuantity(int productId) {
    for (auto it = cart.begin(); it != cart.end(); ++it) {
        if (it->Product::getId() == productId) {
            int newQty = it->getQuantity() + 1;
            it->setQuantity(newQty);
            return;
        }
    }
}

void Order::clearOrder(){
    cart.clear();
    orderId=nextId++;
}


void Order::removeItem(int productId) {
    cart.erase(std::remove_if(cart.begin(), cart.end(),
                              [=](const OrderItem& item) { return item.Product::getId() == productId; }),
               cart.end());
}

float Order::calculateTotalPrice() const{
    float total=0;
    for(const auto& item : cart){
        total+=item.totalPrice();
    }
    return total;
}
void Order::display() const {
    cout<<"Order ID: "<<orderId<<endl;
    cout<<"User ID: "<<userId<<endl;
    cout<<"Status: "<<status<<endl;
    cout<<"Payment Method: "<<paymentMethod->getPaymentType()<<endl;
    cout<<"Items in Cart:" <<endl;

    if (cart.empty()) {
        cout << "  No items in the cart." << endl;
    } else {
        for (const auto& item : cart) {
            item.display();
            cout << "-----------------" << endl;
        }
    }
    cout<<"Total Price: "<<calculateTotalPrice()<<endl;
}

int Order::nextId = 1;


Store::Store(){
    loadProducts();
    loadOrders();

}

void Store::loadProducts(){
    ifstream fin("products.bin", ios::binary);
    if (!fin) {
        ofstream fout("products.bin", ios::binary); 
        return;
    }
    int id;
    float price;
    size_t len;
    string name;
    while (fin.read(reinterpret_cast<char*>(&id), sizeof(id))) {
        fin.read(reinterpret_cast<char*>(&len), sizeof(len));
        name.resize(len);
        fin.read(&name[0], len);
        fin.read(reinterpret_cast<char*>(&price), sizeof(price));
        products.emplace_back(id, name, price);
    }
    fin.close();
}


Store* Store::getInstance() {
    static Store instance;
    return &instance;
}

vector<Product>* Store::allProducts() {
    return &products;
}
vector<Order>* Store::allOrders() {
    return &orders;
}


Store::~Store(){
    saveProducts();
    saveOrders();
}

void Store::saveProducts(){

    ofstream fout("products.bin", ios::binary | ios::trunc);
    for (const auto& p : products){
        int id = p.getId();
        string name = p.getName();
        float price = p.getPrice();
        size_t len = name.size();
        fout.write(reinterpret_cast<char*>(&id), sizeof(id));
        fout.write(reinterpret_cast<char*>(&len), sizeof(len));
        fout.write(name.c_str(), len);
        fout.write(reinterpret_cast<char*>(&price), sizeof(price));
    }
    fout.close();
}


void Store::saveOrders() {
    ofstream fout("orders.bin", ios::binary | ios::trunc);
    for (const auto& o : orders) {
        int oid = o.getId();
        int uid = o.getUserId();
        string status = o.getStatus();
        string address = o.getAddress();
        string payMethod = o.getPayMethod();

        size_t len;

        fout.write(reinterpret_cast<char*>(&oid), sizeof(oid));
        fout.write(reinterpret_cast<char*>(&uid), sizeof(uid));

        len = status.size();
        fout.write(reinterpret_cast<char*>(&len), sizeof(len));
        fout.write(status.c_str(), len);

        len = address.size();
        fout.write(reinterpret_cast<char*>(&len), sizeof(len));
        fout.write(address.c_str(), len);

        len = payMethod.size();
        fout.write(reinterpret_cast<char*>(&len), sizeof(len));
        fout.write(payMethod.c_str(), len);

        const vector<OrderItem>& cart = o.getCart();
        int cartSize = cart.size();
        fout.write(reinterpret_cast<char*>(&cartSize), sizeof(cartSize));

        for (const auto& item : cart) {
            int pid = item.getId();
            string name = item.getName();
            float price = item.getPrice();
            int qty = item.getQuantity();

            len = name.size();
            fout.write(reinterpret_cast<char*>(&pid), sizeof(pid));
            fout.write(reinterpret_cast<char*>(&len), sizeof(len));
            fout.write(name.c_str(), len);
            fout.write(reinterpret_cast<char*>(&price), sizeof(price));
            fout.write(reinterpret_cast<char*>(&qty), sizeof(qty));
        }
    }
    fout.close();
}

void Store::loadOrders() {
    ifstream fin("orders.bin", ios::binary);
    if (!fin) {
        ofstream fout("orders.bin", ios::binary);
        return;
    }

    int oid, uid, cartSize, pid, qty;
    float price;
    size_t len;
    string status, name, address, payMethod;

    while (fin.read(reinterpret_cast<char*>(&oid), sizeof(oid))) {
        fin.read(reinterpret_cast<char*>(&uid), sizeof(uid));

        fin.read(reinterpret_cast<char*>(&len), sizeof(len));
        status.resize(len);
        fin.read(&status[0], len);

        fin.read(reinterpret_cast<char*>(&len), sizeof(len));
        address.resize(len);
        fin.read(&address[0], len);

        fin.read(reinterpret_cast<char*>(&len), sizeof(len));
        payMethod.resize(len);
        fin.read(&payMethod[0], len);

        Order order(uid);
        order.setStatus(status);
        order.setAddress(address);
        order.setPayMethod(payMethod);

        fin.read(reinterpret_cast<char*>(&cartSize), sizeof(cartSize));
        for (int i = 0; i < cartSize; ++i) {
            fin.read(reinterpret_cast<char*>(&pid), sizeof(pid));
            fin.read(reinterpret_cast<char*>(&len), sizeof(len));
            name.resize(len);
            fin.read(&name[0], len);
            fin.read(reinterpret_cast<char*>(&price), sizeof(price));
            fin.read(reinterpret_cast<char*>(&qty), sizeof(qty));
            order.addItem(OrderItem(pid, name, price, qty));
        }

        orders.push_back(order);
    }

    fin.close();
}



void Store::addProduct(const Product& p){products.push_back(p);}
void Store::addOrder(Order o){orders.push_back(o);}

void Store::editProduct(int id, const string& newName, float newPrice) {
    for (auto& p : products) {
        if (p.getId() == id) {
            p = Product(newName, newPrice);
            break;
        }
    }
}

Product* Store::getProductById(int id) {
    if (products.empty()) {
        cout << "No products available." << endl;
        return nullptr;
    }
    for (auto& prod : products) {
        if (prod.getId()==id) {
            return &prod;
        }
    }
    cout << "Product not found." << endl;
    return nullptr;
}

void Store::displayProducts(){
    if(products.empty())
        cout<<" No Products "<< endl;
    else{
        for (const auto& prod : products){
            prod.display();
            cout << "-----------------" << endl;
        }
    }
}
void Store::displayOrders(){
    if(orders.empty())
        cout<<" No Orders"<<endl;
    else{
        for (const auto& ord : orders){
            ord.display();
            cout << "-----------------" << endl;
        }
    }

}
void Store::displayUserOrders(int userId) const {
    if (orders.empty()) {
        cout << "No orders found." << endl;
        return;
    }
    bool found = false;
    for (const auto& o : orders) {
        if (o.getUserId() == userId) {
            o.display();
            found = true;
        }
    }
    if (!found) {
        cout << "No orders found for User ID " << userId << ".\n";
    }
}

void Store::updateOrderStatus(int orderId, const string& status) {
    for (auto& o : orders) {
        if (o.getId() == orderId) {
            o.setStatus(status);
            cout << "Order status updated.\n";
            return;
        }
    }
    cout << "Order not found.\n";
}

void Store::trackOrder(int orderId){
    if(orders.empty())
        cout<<" No Orders"<<endl;
    else{
        bool found = false;
        for (const auto& ord : orders){
            if(ord.getId()==orderId){
                cout<<" Order ID= "<<ord.getId()<<endl<<" Status= "<<ord.getStatus() << endl;
                cout << "-----------------" << endl;
                found = true;
                break;
            }
        }
        if (!found) cout<<" Order not Found"<<endl;
    }
}


    void Admin::viewProducts(Store& store){
        cout<<"All Products:\n";
        store.displayProducts();
    }
    void Admin::addProduct(Store& store){
        int id;
        string name;
        float price;
        cout<<"Enter Product ID: ";
        cin>>id;
        cout<<"Enter Product Name: ";
        cin.ignore();
        getline(cin,name);
        cout<<"Enter Price: ";
        cin>>price;
        store.addProduct(Product(name,price));
        cout<<"Product added!\n";
    }
    void Admin::editProduct(Store& store){
        int id;
        string name;
        float price;
        cout<<"Enter Product ID to edit: ";
        cin>>id;
        cout<<"New Name: ";
        cin.ignore();
        getline(cin,name);
        cout<<"New Price: ";
        cin>>price;
        store.editProduct(id,name,price);
        cout<<"Product updated!\n";
    }
    void Admin::updateOrderStatus(Store& store){
        int orderId;
        string status;
        cout << "Enter Order ID to update: ";
        cin >> orderId;
        cout << "New Status: ";
        cin>>status;
        store.updateOrderStatus(orderId, status);
    }

    User::User(string n){
        id=nextUid;
        nextUid++;
        name=n;
    }
    User::User(int i,string n){
        id=i;
        nextUid++;
        name=n;
    }
    int User::getId() const{return id;}
    string User::getName() const{return name;}
    void User::viewProducts(Store& store){
        cout<<"All Products:\n";
        store.displayProducts();
    }
    void User::placeOrder(Store& store) {
        Order order(id);
        int pid, qty;
        char choice;

        do {
            cout << "Enter Product ID to add: ";
            cin >> pid;
            cout << "Quantity: ";
            cin >> qty;
            Product* product = store.getProductById(pid);
            if (product) {
                order.addItem(OrderItem(pid, product->getName(), product->getPrice(), qty));
            } else {
                cout << "Product not found.\n";
            }
            cout << "Add more items? (y/n): ";
            cin >> choice;
        } while (choice == 'y');

        order.display();
        cout << "Proceed with payment? (y/n): ";
        cin >> choice;

        if (choice == 'y') {
            int paymentOption;
            PaymentMethod* payment = nullptr;
            cout << "Choose payment method (1. Card, 2. Cash, 3. EasyPaisa, 4. JazzCash): ";
            cin >> paymentOption;

            switch (paymentOption) {
            case 1:
                payment = new CardPayment();
                break;
            case 2:
                payment = new CashPayment();
                break;
            case 3:
                payment = new EasyPaisaPayment();
                break;
            case 4:
                payment = new JazzCashPayment();
                break;
            default:
                cout << "Invalid option. Defaulting to Cash.\n";
                payment = new CashPayment();
            }

            order.setPaymentMethod(payment);
            store.addOrder(order);
            cout << "Order placed successfully!\n";
        } else {
            cout << "Order cancelled.\n";
        }
    }

    void User::trackOrder(Store& store) {
        int orderId;
        cout << "Enter Order ID to track: ";
        cin >> orderId;
        store.trackOrder(orderId);
    }

    void User::viewMyOrders(Store& store) {
        store.displayUserOrders(id);
    }

int User::nextUid=1;

int authenticator(QString username,QString password){
    if (username=="user123" && password=="user123"){
        return 1;
    }else 	if (username=="admin123" && password=="admin123"){
        return 2;
    }else{
        return 3;
    }
}
