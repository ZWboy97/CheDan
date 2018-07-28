#include "answerlistitem.h"
#include "ui_answerlistitem.h"
#include <QMessageBox>
#include "user.h"
#include "mainwindow.h"
#include <QDebug>
#include "tools.h"
/**
 * @brief AnswerListItem::AnswerListItem
 * @param parent
 *   qt中自定义空间类，用于问题列表在listwidget中的显示
 *   使用前需要传入需要显示的信息，并且动态加载的场景下，该对象需要通过指针方式传入listwidget中
 */
AnswerListItem::AnswerListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnswerListItem)
{
    ui->setupUi(this);

    //基于回答者name，检索User
    for(int i=0;i<MainWindow::UserList.size();i++){
        if(CurrentAnswer.getCreateUserName() == MainWindow::UserList[i].getUserName()){
            Creator = MainWindow::UserList[i];
            UserIndex = i;
            break;
        }
    }
    //初始化点赞
    IsPraise = false;
    IsDiss = false;

}

AnswerListItem::~AnswerListItem()
{
    delete ui;
}

/*******************************更新点赞显示***************************/
/**
 * @brief AnswerListItem::addPraiseNum 增加一个赞，并将次反馈到UI，并将点赞数据更新到原数据
 */
void AnswerListItem::addPraiseNum(){
    CurrentAnswer.addAPrasie();
    ui->label__number_praise->setText(QString::number(CurrentAnswer.getPraiseNum(),10));
    CurrentQuestion->updateAnswerAt(AnswerIndex,CurrentAnswer);

}

void AnswerListItem::addDissNum(){
    CurrentAnswer.addDiss();
    ui->label_diss_number->setText(QString::number(CurrentAnswer.getDissNum(),10));
    CurrentQuestion->updateAnswerAt(AnswerIndex,CurrentAnswer);

}
void AnswerListItem::subPraiseNum(){
    CurrentAnswer.subAPraise();
    ui->label__number_praise->setText(QString::number(CurrentAnswer.getPraiseNum(),10));
    CurrentQuestion->updateAnswerAt(AnswerIndex,CurrentAnswer);

}

void AnswerListItem::subDissNum(){
    CurrentAnswer.subDiss();
    ui->label_diss_number->setText(QString::number(CurrentAnswer.getDissNum(),10));
    CurrentQuestion->updateAnswerAt(AnswerIndex,CurrentAnswer);

}
/***********************************getter and setter************************************/
void AnswerListItem::setCurrentQuestion(Question* currentQuestion){
    CurrentQuestion = currentQuestion;
}

Question* AnswerListItem::getCurrentQuestion(){
    return CurrentQuestion;
}
void AnswerListItem::setAnswerIndex(int i){
    AnswerIndex = i;
}
int AnswerListItem::getAnswerIndex(){
    return AnswerIndex;
}
void AnswerListItem::setCurrentAnswer(Answer answer){
    CurrentAnswer = answer;
}

/******************************Qt UI 操作**********************************************/
/**
 * @brief AnswerListItem::inflate 实现将内容填充的到UI布局显示
 */
void AnswerListItem::inflate(){
    ui->label_answer_name->setText(CurrentAnswer.getCreateUserName());
    ui->label_answer_time->setText(CurrentAnswer.getCreateTime().toString());
    ui->textBrowser_answer_detail->setText(CurrentAnswer.getDetail());
    ui->label_diss_number->setText(QString::number(CurrentAnswer.getDissNum(),10));
    ui->label__number_praise->setText(QString::number(CurrentAnswer.getPraiseNum(),10));
    for(int i=0;i<MainWindow::UserList.size();i++){
        if(CurrentAnswer.getCreateUserName() == MainWindow::UserList[i].getUserName()){
            ui->pushButton->setStyleSheet(Tools::getImageStyleSheet(MainWindow::UserList[i].getImageId()));
            break;
        }
    }
}
/**
 * @brief AnswerListItem::on_pushButton_clicked 用户头像的点击逻辑
 */
void AnswerListItem::on_pushButton_clicked()
{

    for(int i=0;i<MainWindow::UserList.size();i++){
        if(CurrentAnswer.getCreateUserName() == MainWindow::UserList[i].getUserName()){
            emit clickToFocus(MainWindow::UserList[i]);
            break;
        }
    }
}
/**
 * @brief AnswerListItem::on_pushButton_praise_clicked，点赞按钮逻辑
 */
void AnswerListItem::on_pushButton_praise_clicked()
{
    if(IsPraise == false){
        ui->pushButton_praise->setStyleSheet(STYLESHEET_PRAISE_CLICKED);
        addPraiseNum();
        IsPraise = true;
        if(IsDiss){
            ui->pushButton_diss->setStyleSheet(STYLESHEET_DISS_UNCLICKED);
            subDissNum();
            IsDiss = false;
        }
    }else{
        ui->pushButton_praise->setStyleSheet(STYLESHEET_PRAISE_UNCLICKED);
        subPraiseNum();
        IsPraise = false;
    }
}
/**
 * @brief AnswerListItem::on_pushButton_diss_clicked diss按钮逻辑
 */
void AnswerListItem::on_pushButton_diss_clicked()
{
    if(IsDiss == false){
        ui->pushButton_diss->setStyleSheet(STYLESHEET_DISS_CLICKED);
        addDissNum();
        IsDiss = true;
        if(IsPraise){
            ui->pushButton_praise->setStyleSheet(STYLESHEET_PRAISE_UNCLICKED);
            subPraiseNum();
            IsPraise = false;
        }
    }else{
        ui->pushButton_diss->setStyleSheet(STYLESHEET_DISS_UNCLICKED);
        subDissNum();
        IsDiss = false;
    }
}
