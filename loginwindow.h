#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "user.h"

namespace Ui {
class LoginWindow;
}
/**
 * @brief LoginWindow::LoginWindow 登陆界面，以及注册界面
 * @param parent
 */
class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

public:
    int ImageID;    //保存当选的注册头像id
    User currentUser;

private slots:
    void on_login_pushButton_clicked();

    void on_pushButton_register_clicked();

    void on_uesr_name_lineEdit_editingFinished();

    void on_pushButton_quit_register_clicked();

    void on_pushButton_prev_image_clicked();

    void on_pushButton_next_image_clicked();

    void on_pushButton_register_2_clicked();

private:
    Ui::LoginWindow *ui;
};
#endif // LOGINWINDOW_H
