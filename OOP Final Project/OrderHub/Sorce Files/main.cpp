#include "login.h"
#include "store.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Store* store = Store::getInstance();
    login w;
    w.show();
    return a.exec();
}
