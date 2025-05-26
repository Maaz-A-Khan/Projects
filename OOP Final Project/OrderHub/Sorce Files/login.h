#ifndef LOGIN_H
#define LOGIN_H
#include "store.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class login;
}
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void validateRegisterFields();
    void toggleLoginPasswordVisibility(int state);
    void toggleRegisterPasswordVisibility(int state);

    void on_loginbutton_clicked();

    void on_registerBtn_clicked();

    void on_LP_clicked();
    void hideAll();
    void on_RP_clicked();

private:
    Ui::login *ui;
};
#endif
