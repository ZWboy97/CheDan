#include "detaildialog.h"
#include "ui_detaildialog.h"
#include "mainwindow.h"
#include <QDebug>
#include"tools.h"

DetailDialog::DetailDialog(Question* selectedQuestion,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailDialog)
{
    ui->setupUi(this);
    SelectedQuestion = selectedQuestion;//获取来自mainwindow的question
    ui->label_username->setText(SelectedQuestion->getCreateUserName());
    ui->label_question_tittle->setText(SelectedQuestion->getQuestionTitle());
    ui->textEdit_question_detail->setText(SelectedQuestion->getDetail());
    ui->label_time->setText("创建时间："+SelectedQuestion->getCreateTime().toString());
    //基于问题创建者name检索user
    for(int i=0;i<MainWindow::UserList.size();i++){
        if(SelectedQuestion->getCreateUserName() == MainWindow::UserList[i].getUserName()){
            ui->pushButton_userImage->setStyleSheet(Tools::getImageStyleSheet(MainWindow::UserList[i].getImageId()));
            break;
        }
    }

    //将问题的回答数据填充到item的AnseweList中，待显示
    for(int i=0;i<SelectedQuestion->getAnswer().size();i++){
        Answer* answer = new Answer();
        answer->setCreateUserName(SelectedQuestion->getAnswer()[i].getCreateUserName());
        answer->setCreatTime(SelectedQuestion->getAnswer()[i].getCreateTime());
        answer->setCreatUserId(SelectedQuestion->getAnswer()[i].getCreatUserId());
        answer->setDetail(SelectedQuestion->getAnswer()[i].getDetail());
        answer->setDissNum(SelectedQuestion->getAnswer()[i].getDissNum());
        answer->setPraiseNum(SelectedQuestion->getAnswer()[i].getPraiseNum());
        answer->setId(SelectedQuestion->getAnswer()[i].getId());
        AnswerList.push_back(answer);
    }
    //界面显示
    refreshAnserList();
}

DetailDialog::~DetailDialog()
{
    //清除控件
    int N = AnswerListWidgetItems.size();
    for(int i = 0; i < N;i++){
        ui->listWidget_answer_list->removeItemWidget(AnswerListWidgetItems[i]);
        if(AnswerListWidgetItems[i])
            delete AnswerListWidgetItems[i];
    }
    AnswerListWidgetItems.clear();
    for(int i = 0; i<AnswerListItems.size();i++){
        if(AnswerListItems[i]){
            delete AnswerListItems[i];
        }
    }
    AnswerListItems.clear();
    for(int i =0;i<AnswerList.size();i++){
        if(AnswerList[i]){
            delete AnswerList[i];
        }
    }
    if(PrepareAnswer)
        delete PrepareAnswer;
    delete ui;
}
/*******************************getter and setter******************************/
void DetailDialog::setSelectedQuestion(Question* question){
    SelectedQuestion = question;
}

Question* DetailDialog::getSelectedQuestion(){
    return SelectedQuestion;
}



/*******************************Qt UI操作逻辑***********************************/
/**
 * @brief DetailDialog::on_pushButton_clicked，点击显示回答编辑页面
 */
void DetailDialog::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
/**
 * @brief DetailDialog::on_pushButton_quit_answer_clicked，点击退出回答编辑
 */
void DetailDialog::on_pushButton_quit_answer_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
/**
 * @brief DetailDialog::on_pushButton_2_clicked，提交回答
 */
void DetailDialog::on_pushButton_2_clicked()
{
    PrepareAnswer = new Answer();
    PrepareAnswer->setCreateUserName(MainWindow::CurrentUser.getUserName());
    PrepareAnswer->setCreatTime(QDate::currentDate());
    PrepareAnswer->setCreatUserId(MainWindow::CurrentUser.getUserId());
    PrepareAnswer->setDetail(ui->textEdit_answer->toPlainText());
    PrepareAnswer->setDissNum(0);
    PrepareAnswer->setPraiseNum(0);
    AnswerList.push_front(PrepareAnswer);
    SelectedQuestion->addAnAnswer(*PrepareAnswer);
    refreshAnserList();
    ui->stackedWidget->setCurrentIndex(0);

    //用户回答问题数+1
    for(int i=0;i<MainWindow::UserList.size();i++){
        if(MainWindow::CurrentUser.getUserName() == MainWindow::UserList[i].getUserName()){
            CurrentUser.addAnswerNum();
            MainWindow::UserList[i].addAnswerNum();
            break;
        }
    }
}
/**
 * @brief DetailDialog::refreshAnserList，更新载入回答列表
 */
void DetailDialog::refreshAnserList(){
    //页码初始化
    Pages = AnswerList.size() /20;
    currentPage = 0;
    ui->label_currentpage->setText("当前第"+QString::number(currentPage+1,10)+"页，共"+QString::number(Pages+1,10)+"页");
    int n = AnswerList.size() - AnswerListWidgetItems.size();
    if( n > 0 ){
        //清除原有控件
        int N = AnswerListWidgetItems.size();
        for(int i = 0; i < N;i++){
            ui->listWidget_answer_list->removeItemWidget(AnswerListWidgetItems[i]);
            if(AnswerListWidgetItems[i])
                delete AnswerListWidgetItems[i];
        }
        AnswerListWidgetItems.clear();
        for(int i = 0; i<AnswerListItems.size();i++){
            if(AnswerListItems[i]){
                delete AnswerListItems[i];
            }
        }
        AnswerListItems.clear();
        //填充新数据到控件
        for(int i = 0; i < AnswerList.size();i++){
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget_answer_list);
            AnswerListWidgetItems.push_front(item);
            AnswerListItem *answerListItem = new AnswerListItem();
            answerListItem->setCurrentQuestion(SelectedQuestion);
            answerListItem->setAnswerIndex(i);
            answerListItem->setCurrentAnswer(*AnswerList[i]);
            answerListItem->inflate();
            AnswerListItems.push_front(answerListItem);
            connect(answerListItem,SIGNAL(clickToFocus(User)),this,SLOT(add_focus(User)));

        }
        //控件填充到listwidget显示
        for(int i = 0; i<AnswerList.size();i++){
            ui->listWidget_answer_list->setItemWidget(AnswerListWidgetItems[i],AnswerListItems[i]);
        }
    }
    ui->listWidget_answer_list->show();
    ui->stackedWidget->setCurrentIndex(0);
}

/**
 * @brief DetailDialog::on_pushButton_quit_focus_clicked,退出关注用户按钮
 */
void DetailDialog::on_pushButton_quit_focus_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/**
 * @brief DetailDialog::on_pushButton_focus_add_clicked 点击关注用户按钮逻辑
 */
void DetailDialog::on_pushButton_focus_add_clicked()
{
        MainWindow::CurrentUser.addFocusUser(WantToFocusUser.getUserName());
        ui->pushButton_focus_add->setStyleSheet("background-color: rgb(18, 150, 219,75%);");
        ui->pushButton_focus_add->setText("已关注");

        //更新到用户库
        for(int i=0;i<MainWindow::UserList.size();i++){
            if(MainWindow::CurrentUser.getUserName() == MainWindow::UserList[i].getUserName()){
                MainWindow::UserList[i].addFocusUser(WantToFocusUser.getUserName());
                break;
            }
        }
}
/**
 * @brief DetailDialog::add_focus 接受来自自定义控件的signal之后，显示特定user的信息，是否关注
 * @param user
 */
void DetailDialog::add_focus(User user){
    WantToFocusUser = user;
    ui->label_focus_name->setText(user.getUserName());
    ui->label_focus_image->setStyleSheet(Tools::getImageStyleSheet(user.getImageId()));
    ui->label_answer_num->setText(QString::number(user.getAnswerNum(),10));
    ui->label_fan_num->setText(QString::number(user.getFocusList().size(),10));
    ui->label_praise_num->setText(QString::number(user.getPrasieNum(),10));
    ui->label_question_num->setText(QString::number(user.getQuestionNum(),10));
    ui->stackedWidget->setCurrentIndex(2);
}

/**
 * @brief DetailDialog::on_pushButton_userImage_clicked，提问者头像点击，进入关注界面
 */
void DetailDialog::on_pushButton_userImage_clicked()
{
    User user;
    for(int i=0;i<MainWindow::UserList.size();i++){
        if(SelectedQuestion->getCreateUserName() == MainWindow::UserList[i].getUserName()){
            user = MainWindow::UserList[i];
            WantToFocusUser = user;
            qDebug()<<WantToFocusUser.getUserName();
            break;
        }
    }
    ui->label_focus_name->setText(user.getUserName());
    ui->label_focus_image->setStyleSheet(Tools::getImageStyleSheet(user.getImageId()));
    ui->label_answer_num->setText(QString::number(user.getAnswerNum(),10));
    ui->label_fan_num->setText(QString::number(user.getFocusList().size(),10));
    ui->label_praise_num->setText(QString::number(user.getPrasieNum(),10));
    ui->label_question_num->setText(QString::number(user.getQuestionNum(),10));
    ui->stackedWidget->setCurrentIndex(2);
}
/**
 * @brief DetailDialog::on_pushButton_prevpage_clicked，上一页按钮
 */
void DetailDialog::on_pushButton_prevpage_clicked()
{
    if(currentPage > 0){
        currentPage--;
        ui->label_currentpage->setText("当前第"+QString::number(currentPage+1,10)+"页，共"+QString::number(Pages+1,10)+"页");
        int N = AnswerListWidgetItems.size();
        for(int i = 0; i < N;i++){
            ui->listWidget_answer_list->removeItemWidget(AnswerListWidgetItems[i]);
            if(AnswerListWidgetItems[i])
                delete AnswerListWidgetItems[i];
        }
        AnswerListWidgetItems.clear();
        for(int i = 0; i<AnswerListItems.size();i++){
            if(AnswerListItems[i]){
                delete AnswerListItems[i];
            }
        }
        AnswerListItems.clear();

        for(int i = currentPage*20; i < AnswerList.size() && i-currentPage*20 <20;i++){
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget_answer_list);
            AnswerListWidgetItems.push_front(item);

            AnswerListItem *answerListItem = new AnswerListItem();
            answerListItem->setCurrentQuestion(SelectedQuestion);
            answerListItem->setAnswerIndex(i);
            answerListItem->setCurrentAnswer(*AnswerList[i]);

            answerListItem->inflate();
            AnswerListItems.push_front(answerListItem);
            connect(answerListItem,SIGNAL(clickToFocus(User)),this,SLOT(add_focus(User)));

        }
        for(int i = 0; i<AnswerListWidgetItems.size();i++){
            ui->listWidget_answer_list->setItemWidget(AnswerListWidgetItems[i],AnswerListItems[i]);
        }
    }
    ui->listWidget_answer_list->show();
    ui->stackedWidget->setCurrentIndex(0);
}
/**
 * @brief DetailDialog::on_pushButton_nextpage_clicked，下一页按钮
 */
void DetailDialog::on_pushButton_nextpage_clicked()
{
    if(currentPage < Pages){
        currentPage++;
        ui->label_currentpage->setText("当前第"+QString::number(currentPage+1,10)+"页，共"+QString::number(Pages+1,10)+"页");
        int N = AnswerListWidgetItems.size();
        for(int i = 0; i < N;i++){
            ui->listWidget_answer_list->removeItemWidget(AnswerListWidgetItems[i]);
            if(AnswerListWidgetItems[i])
                delete AnswerListWidgetItems[i];
        }
        AnswerListWidgetItems.clear();
        for(int i = 0; i<AnswerListItems.size();i++){
            if(AnswerListItems[i]){
                delete AnswerListItems[i];
            }
        }
        AnswerListItems.clear();

        for(int i = currentPage*20; i < AnswerList.size() && i-currentPage*20 <20;i++){
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget_answer_list);
            AnswerListWidgetItems.push_front(item);

            AnswerListItem *answerListItem = new AnswerListItem();
            answerListItem->setCurrentQuestion(SelectedQuestion);
            answerListItem->setAnswerIndex(i);
            answerListItem->setCurrentAnswer(*AnswerList[i]);

            answerListItem->inflate();
            AnswerListItems.push_front(answerListItem);
            connect(answerListItem,SIGNAL(clickToFocus(User)),this,SLOT(add_focus(User)));

        }
        for(int i = 0; i<AnswerListWidgetItems.size();i++){
            ui->listWidget_answer_list->setItemWidget(AnswerListWidgetItems[i],AnswerListItems[i]);
        }
    }
    ui->listWidget_answer_list->show();
    ui->stackedWidget->setCurrentIndex(0);
}
