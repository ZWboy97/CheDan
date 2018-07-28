#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "QMessageBox"
#include "user.h"
#include "mainwindow.h"
#include "tools.h"
#include <QDebug>

/**
 * @brief LoginWindow::LoginWindow 登陆界面，以及注册界面
 * @param parent
 */
LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ImageID = 1;
    currentUser = User();
    ui->stackedWidget->setCurrentIndex(0);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

/**************************************QT UI 逻辑*******************************/
/**
 * @brief 登陆按钮的点击逻辑
 */
void LoginWindow::on_login_pushButton_clicked()
{   //获取输入的登陆用户名以及密码
    QString loginUserName = ui->uesr_name_lineEdit->text();
    QString loginUserPassword = ui->user_password_lineEdit->text();
    //到用户列表中基于用户名和密码进行检索
    bool isright = true;
    int i;
    for(i=0;i<MainWindow::UserList.size();i++){//遍历查找
        if(loginUserName == MainWindow::UserList[i].getUserName() &&
                loginUserPassword == MainWindow::UserList[i].getPassword()){
            isright = true;
            break;
        }
    }
    if( i == MainWindow::UserList.size()){
        isright = false;
        QMessageBox::warning(this, "错误", "用户名或密码错误，请重新输入！", QMessageBox::Yes);
    }
    if(isright){
        //读取用户所有信息到currentuser
        MainWindow::CurrentUser = MainWindow::UserList[i];
        //打开主界面
        MainWindow * w = new MainWindow();
        w->show();
        close();
    }
}
/**
 * @brief LoginWindow::on_pushButton_register_clicked 注册按钮的点击逻辑
 */
void LoginWindow::on_pushButton_register_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief LoginWindow::on_uesr_name_lineEdit_editingFinished 用户名完成编辑按钮逻辑，用于后期载入头像
 */
void LoginWindow::on_uesr_name_lineEdit_editingFinished()
{

}
/**
 * @brief LoginWindow::on_pushButton_quit_register_clicked 退出用户注册逻辑
 */
void LoginWindow::on_pushButton_quit_register_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
/**
 * @brief LoginWindow::on_pushButton_prev_image_clicked 注册界面，上一张头像按钮
 */
void LoginWindow::on_pushButton_prev_image_clicked()
{
    if(ImageID == 1){
        ImageID = 8;
    }else{
        ImageID--;
    }
    ui->label_register_image->setStyleSheet(Tools::getImageStyleSheet(ImageID));
}
/**
 * @brief LoginWindow::on_pushButton_next_image_clicked 注册界面，下一张头像按钮
 */
void LoginWindow::on_pushButton_next_image_clicked()
{
    if(ImageID == 8){
        ImageID = 1;
    }else{
        ImageID++;
    }
    ui->label_register_image->setStyleSheet(Tools::getImageStyleSheet(ImageID));
}
/**
 * @brief 注册界面，点击注册按钮逻辑
 */
void LoginWindow::on_pushButton_register_2_clicked()
{
    User registerUser;
    //读取用户注册信息，生成新用户数据
    registerUser.setUserName(ui->lineEdit_register_username->text());
    registerUser.setUserPassword(ui->lineEdit_register_password->text());
    //初始化用户的其他相关属性数据
    registerUser.setUserId(QString::number(Tools::getNextId()));
    registerUser.setQuestionNum(0);
    registerUser.setPraiseNum(0);
    registerUser.setPraiseNum(0);
    registerUser.setImageId(ImageID);
    registerUser.setAnserNum(0);
    MainWindow::UserList.push_front(registerUser);  //新用户添加到用户列表中
    QMessageBox::warning(this, "注册", "注册成功", QMessageBox::Yes);
    ui->stackedWidget->setCurrentIndex(0);
}
