#include "questionlistitem.h"
#include "ui_questionlistitem.h"
#include <QMessageBox>
#include "tools.h"

QuestionListItem::QuestionListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionListItem)
{
    ui->setupUi(this);
    ui->label_username->setText(UserName);
    ui->label_question_title->setText(Title);
    ui->textBrowser_detail->setText(Detail);
    ui->pushButton_userimage->setStyleSheet(Tools::getImageStyleSheet(ImageId));

}

QuestionListItem::~QuestionListItem()
{
    delete ui;
}
void QuestionListItem::setImageId(int imageid){
    ImageId = imageid;
}

QString QuestionListItem::getDetail(){
    return Detail;
}
void QuestionListItem::setDetail(QString detail){
    Detail = detail;
}

void QuestionListItem::setUserName(QString name){
    UserName = name;
}
void QuestionListItem::setTitle(QString title){
    Title = title;
}

QString QuestionListItem::getName(){
    return UserName;
}
QString QuestionListItem::getTitle(){
    return Title;
}

void QuestionListItem::inflate(){
    ui->label_username->setText(UserName);
    ui->label_question_title->setText(Title);
    ui->textBrowser_detail->setText(Detail);
    ui->pushButton_userimage->setStyleSheet(Tools::getImageStyleSheet(ImageId));
}


