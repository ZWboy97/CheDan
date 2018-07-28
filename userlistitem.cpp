#include "userlistitem.h"
#include "ui_userlistitem.h"

UserListItem::UserListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserListItem)
{
    ui->setupUi(this);
    UserName = "未填写";
    ui->label_username->setText(UserName);
}

UserListItem::~UserListItem()
{
    delete ui;
}

void UserListItem::setUserName(QString name){
    UserName = name;
}

QString UserListItem::getUserName(){
    return UserName;
}
void UserListItem::inflate(){
    ui->label_username->setText(UserName);
}
