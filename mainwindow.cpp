#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "questionlistitem.h"
#include "QHBoxLayout"
#include "QVector"
#include "userlistitem.h"
#include <QMessageBox>
#include <QDebug>
#include "detaildialog.h"
#include "tools.h"
#include "loginwindow.h"

User MainWindow::CurrentUser;//静态成员变量需要在外边再进行定义
QVector<User> MainWindow::UserList;//零时的用户列表，之后通过数据库查询

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_image->setStyleSheet(Tools::getImageStyleSheet(CurrentUser.getImageId()));
    ui->label_username->setText(CurrentUser.getUserName());


    //从公共数据库载入问题数据到QuestionList
    //..........
    //假装几个问题数据
    QuestionList.push_front(new Question("你在电影院遇到过哪些奇葩的事情？？","奇闻异事！！！！","JackChance","123453",QDate::currentDate()));
    QuestionList.push_front(new Question("都是怎么处理旧笔记本电脑的？",
                                         "卖二手的话也不知道什么行情好不好卖。想问下大家都怎么处置旧笔记本电脑的？",
                                         "enenenen","123453",QDate::currentDate()));
    QuestionList.push_front(new Question("如何评价微博将发布内容独家版权？",
                                         "微博新版用户协议，将用户发布的一切内容据为己有，甚至要求用户放弃维权所得赔偿。你怎么看？",
                                         "Pig","123453",QDate::currentDate()));
    QuestionList.push_front(new Question("身份证前两位是按照什么规律排列的？",
                                         "为什么[北京，天津，河北，山西，内蒙古]都是1开头；[辽宁，吉林，黑龙江]都是2开头。","Pig","123453",QDate::currentDate()));
    QuestionList.push_front(new Question("你有什么道理后悔没有早点知道？",
                                         "“要是我早点知道比特币这个东西，我现在就是大富翁了啊”"
                                         "“要是我早点知道读书的重要性，现在就不会混这样了啊”","Cat","123453",QDate::currentDate()));
    QuestionList.push_front(new Question("百度还是电信总部。","两种方案，艰苦拉萨解放了卡啊就是看浪费大家阿斯利康啊时间快到了放假啊","Dog","123453",QDate::currentDate()));
    QuestionList.push_front(new Question("留学费用最低的国家有哪些。。","备注，一年制的","JackChance","123453",QDate::currentDate()));
    QuestionList.push_front(new Question("中关村万千套路之一——20170913","如题，昨晚晚去中关村被套路了。。。。","Pig","123453",QDate::currentDate()));
    //每个问题下假装一个回答
    //假装预填充的回答
    Answer answer;
    answer.setCreateUserName("JackChance");
    answer.setCreatTime(QDate::currentDate());
    answer.setDetail("这么高大上的问题，当然是留给楼下来回答了。。。。");
    answer.setPraiseNum(100);
    answer.setDissNum(10);
    answer.setCreatUserId("12138");
    answer.setId("1233");
    for(int i=0;i<QuestionList.size();i++){
        QuestionList[i]->addAnAnswer(answer);
    }

    on_pushButton_time_line_clicked();//载入问题列表
}

MainWindow::~MainWindow()
{
    int N = QuestionListWidgetItems.size();
    for(int i = 0; i < N;i++){
        ui->listWidget_question->removeItemWidget(QuestionListWidgetItems[i]);
        if(QuestionListWidgetItems[i])
            delete QuestionListWidgetItems[i];
    }
    QuestionListWidgetItems.clear();
    for(int i = 0; i<QuestionListItems.size();i++){
        if(QuestionListItems[i]){
            delete QuestionListItems[i];
        }
    }
    QuestionListItems.clear();
    N = FocusListWidgetItems.size();
    for(int i = 0; i < N;i++){
        ui->listWidget_focus->removeItemWidget(FocusListWidgetItems[i]);
        if(FocusListWidgetItems[i])
            delete FocusListWidgetItems[i];
    }
    FocusListWidgetItems.clear();
    for(int i = 0; i<FocusListItems.size();i++){
        if(FocusListItems[i]){
            delete FocusListItems[i];
        }
    }
    FocusListItems.clear();
    for(int i =0;i<QuestionList.size();i++){
        if(QuestionList[i])
            delete QuestionList[i];
    }
    QuestionList.clear();
    for(int i=0;i<FocusUserList.size();i++){
        if(FocusUserList[i])
            delete FocusUserList[i];
    }
    FocusUserList.clear();
    delete ui;
}

/***********************************qT UI 控制*************************************/
/**
 * @brief MainWindow::refreshQuestionList 刷新问题列表，载入新数据
 */
void MainWindow::refreshQuestionList(){
    int n = QuestionList.size() - QuestionListWidgetItems.size();
    if( n > 0 ){
        int N = QuestionListWidgetItems.size();
        for(int i = 0; i < N;i++){
            ui->listWidget_question->removeItemWidget(QuestionListWidgetItems[i]);
            if(QuestionListWidgetItems[i])
                delete QuestionListWidgetItems[i];
        }
        QuestionListWidgetItems.clear();
        for(int i = 0; i<QuestionListItems.size();i++){
            if(QuestionListItems[i]){
                delete QuestionListItems[i];
            }
        }
        QuestionListItems.clear();
        qDebug()<<"ok";
        for(int i = 0; i < QuestionList.size();i++){
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget_question);
            QuestionListWidgetItems.push_front(item);
            QuestionListItem *questionListItem = new QuestionListItem();
            questionListItem->setUserName(QuestionList[i]->getCreateUserName());
            questionListItem->setTitle(QuestionList[i]->getQuestionTitle());
            for(int j=0;j<MainWindow::UserList.size();j++){
                if(QuestionList[i]->getCreateUserName() == UserList[j].getUserName()){
                    questionListItem->setImageId(UserList[j].getImageId());
                    qDebug()<<UserList[j].getImageId();
                    break;
                }
            }
            questionListItem->setDetail(QuestionList[i]->getDetail());
            questionListItem->inflate();
            QuestionListItems.push_front(questionListItem);
        }
        for(int i = currentPage*10; i < QuestionList.size()-currentPage*10 && i < 10;i++){
            ui->listWidget_question->setItemWidget(QuestionListWidgetItems[i],QuestionListItems[i]);
        }
    }
    ui->listWidget_question->show();
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief MainWindow::on_pushButton_send_question_clicked 进入提问界面
 */
void MainWindow::on_pushButton_send_question_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_question_title->setFocus();
}

/**
 * @brief MainWindow::on_pushButton_time_line_clicked 进入时间线界面---显示所有的提问
 */
void MainWindow::on_pushButton_time_line_clicked()
{
    Pages = QuestionList.size() /20;
    currentPage = 0;
    ui->label_currentpage->setText("当前第"+QString::number(currentPage+1,10)+"页，共"+QString::number(Pages+1,10)+"页");

    int n = QuestionList.size() - QuestionListWidgetItems.size();
    if( n > 0){
        int N = QuestionListWidgetItems.size();
        for(int i = 0; i < N;i++){
            ui->listWidget_question->removeItemWidget(QuestionListWidgetItems[i]);
            if(QuestionListWidgetItems[i])
                delete QuestionListWidgetItems[i];
        }
        QuestionListWidgetItems.clear();
        for(int i = 0; i<QuestionListItems.size();i++){
            if(QuestionListItems[i]){
                delete QuestionListItems[i];
            }
        }
        QuestionListItems.clear();

        for(int i = 0; i < QuestionList.size()&& i <20;i++){
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget_question);
            QuestionListWidgetItems.push_front(item);
            QuestionListItem *questionListItem = new QuestionListItem();
            questionListItem->setUserName(QuestionList[i]->getCreateUserName());
            questionListItem->setTitle(QuestionList[i]->getQuestionTitle());
            for(int j=0;j<MainWindow::UserList.size();j++){
                if(QuestionList[i]->getCreateUserName() == UserList[j].getUserName()){
                    questionListItem->setImageId(UserList[j].getImageId());
                    qDebug()<<UserList[j].getImageId();
                    break;
                }
            }
            questionListItem->setDetail(QuestionList[i]->getDetail());
            questionListItem->inflate();
            QuestionListItems.push_front(questionListItem);
        }
        for(int i = 0; i < QuestionList.size()&& i < 20;i++){
            ui->listWidget_question->setItemWidget(QuestionListWidgetItems[i],QuestionListItems[i]);
        }
    }
    ui->listWidget_question->show();
    ui->stackedWidget->setCurrentIndex(1);

}

/**
 * @brief MainWindow::on_pushButton_collection_focus_clicked 进入查看关注列表界面
 */
void MainWindow::on_pushButton_collection_focus_clicked()
{
    if(MainWindow::CurrentUser.getFocusList().size() > FocusUserList.size()){
        int n = MainWindow::CurrentUser.getFocusList().size() - FocusUserList.size();
        for(int i = n-1; i >=0; i--){
            User* temp = new User();
            qDebug()<<MainWindow::CurrentUser.getFocusList()[i];
            temp->setUserName(MainWindow::CurrentUser.getFocusList()[i]);
            temp->setUserId(MainWindow::CurrentUser.getFocusList()[i]);
            FocusUserList.push_front(temp);
        }
    }
    int n = FocusUserList.size() - FocusListWidgetItems.size();
    if( n > 0 ){
        int N = FocusListWidgetItems.size();
        for(int i = 0; i < N;i++){
            ui->listWidget_focus->removeItemWidget(FocusListWidgetItems[i]);
            if(FocusListWidgetItems[i])
                delete FocusListWidgetItems[i];
        }
        FocusListWidgetItems.clear();
        for(int i = 0; i<FocusListItems.size();i++){
            if(FocusListItems[i]){
                delete FocusListItems[i];
            }
        }
        FocusListItems.clear();

        for(int i = 0; i < FocusUserList.size();i++){
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget_focus);
            FocusListWidgetItems.push_front(item);
            UserListItem *userListItem = new UserListItem();
            userListItem->setUserName(FocusUserList[i]->getUserName());
            userListItem->inflate();
            FocusListItems.push_front(userListItem);
        }
        for(int i = 0; i<FocusUserList.size();i++){
            ui->listWidget_focus->setItemWidget(FocusListWidgetItems[i],FocusListItems[i]);
        }
    }
    ui->listWidget_focus->show();
    ui->stackedWidget->setCurrentIndex(2);
}

/**
 * @brief MainWindow::on_listWidget_question_clicked 点击list进入对应的问题详情
 * @param index
 */
void MainWindow::on_listWidget_question_clicked(const QModelIndex &index)
{
    qDebug()<<"点击位置："<<index.row();

    DetailDialog* detailDialog = new DetailDialog(QuestionList[index.row()],this);
    detailDialog->setFocus();
    detailDialog->setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体
    detailDialog->show();
}
/**
 * @brief 提交问题按钮逻辑
 */
void MainWindow::on_pushButton_summit_question_clicked()
{   //读取用户提问标题以及详情
    QString title = ui->lineEdit_question_title->text();
    QString detail = ui->textEdit_question_detail->toPlainText();
    //生成对应的新问题，并进行相应的初始化操作
    PrepareQuestion = new Question();
    PrepareQuestion->setQuestionTitle(title);
    PrepareQuestion->setCreateUserName(MainWindow::CurrentUser.getUserName());
    PrepareQuestion->setCreatUserId(MainWindow::CurrentUser.getUserId());
    PrepareQuestion->setCreatTime(QDate::currentDate());
    PrepareQuestion->setDetail(detail);
    //用户交互差错控制
    if(title == ""){
        QMessageBox::warning(this,"错误","请输入问题标题",QMessageBox::Yes);
    }else if (detail == "") {
        QMessageBox::warning(this, "错误", "请输入问题描述", QMessageBox::Yes);
    }else{
        //将新提问添加到提问列表中
        QuestionList.push_front(PrepareQuestion);
        //清空界面显示
        ui->lineEdit_question_title->clear();
        ui->textEdit_question_detail->setText("问题详细描述");
        on_pushButton_time_line_clicked();
    }
}
/**
 * @brief MainWindow::on_pushButton_image_clicked 点击当前用户头像，进入用户管理
 */
void MainWindow::on_pushButton_image_clicked()
{
    ui->label_manager_image->setStyleSheet(Tools::getImageStyleSheet(CurrentUser.getImageId()));
    ui->label_manager_name->setText(CurrentUser.getUserName());
    ui->label_praise_num->setText(QString::number(CurrentUser.getPrasieNum(),10));
    ui->label_answer_num->setText(QString::number(CurrentUser.getAnswerNum(),10));
    ui->label_question_num->setText(QString::number(CurrentUser.getQuestionNum(),10));
    ui->label_fan_num->setText(QString::number(CurrentUser.getFocusList().size()));
    ui->stackedWidget->setCurrentIndex(3);
}
/**
 * @brief MainWindow::on_pushButton_logout_clicked 退出登陆
 */
void MainWindow::on_pushButton_logout_clicked()
{
    close();
    LoginWindow* login = new LoginWindow();
    login->show();
}
/**
 * @brief MainWindow::on_pushButton_quit_clicked 退出系统按钮
 */
void MainWindow::on_pushButton_quit_clicked()
{
    close();
}

void MainWindow::on_pushButton_quit_manager_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
/**
 * @brief MainWindow::on_pushButton_nextpage_clicked 问题列表下一页按钮
 */
void MainWindow::on_pushButton_nextpage_clicked()
{

    if(currentPage < Pages)
    {
        currentPage++;
        ui->label_currentpage->setText("当前第"+QString::number(currentPage+1,10)+"页，共"+QString::number(Pages+1,10)+"页");
        int N = QuestionListWidgetItems.size();
        for(int i = 0; i < N;i++){
            ui->listWidget_question->removeItemWidget(QuestionListWidgetItems[i]);
            if(QuestionListWidgetItems[i])
                delete QuestionListWidgetItems[i];
        }
        QuestionListWidgetItems.clear();
        for(int i = 0; i<QuestionListItems.size();i++){
            if(QuestionListItems[i]){
                delete QuestionListItems[i];
            }
        }
        QuestionListItems.clear();

        for(int i = currentPage*20; i < QuestionList.size() && i-currentPage*20 <20;i++){
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget_question);
            QuestionListWidgetItems.push_front(item);
            QuestionListItem *questionListItem = new QuestionListItem();
            questionListItem->setUserName(QuestionList[i]->getCreateUserName());
            questionListItem->setTitle(QuestionList[i]->getQuestionTitle());
            for(int j=0;j<MainWindow::UserList.size();j++){
                if(QuestionList[i]->getCreateUserName() == UserList[j].getUserName()){
                    questionListItem->setImageId(UserList[j].getImageId());
                    qDebug()<<UserList[j].getImageId();
                    break;
                }
            }
            questionListItem->setDetail(QuestionList[i]->getDetail());
            questionListItem->inflate();
            QuestionListItems.push_front(questionListItem);
        }
        for(int i = 0; i < QuestionListWidgetItems.size();i++){
            ui->listWidget_question->setItemWidget(QuestionListWidgetItems[i],QuestionListItems[i]);
        }
    }
    ui->listWidget_question->show();
    ui->stackedWidget->setCurrentIndex(1);
}


/**
 * @brief MainWindow::on_pushButton_prevpage_clicked 问题列表上一页按钮
 */
void MainWindow::on_pushButton_prevpage_clicked()
{
    if(currentPage >0)
    {
        currentPage--;
        ui->label_currentpage->setText("当前第"+QString::number(currentPage+1,10)+"页，共"+QString::number(Pages+1,10)+"页");
        int N = QuestionListWidgetItems.size();
        for(int i = 0; i < N;i++){
            ui->listWidget_question->removeItemWidget(QuestionListWidgetItems[i]);
            if(QuestionListWidgetItems[i])
                delete QuestionListWidgetItems[i];
        }
        QuestionListWidgetItems.clear();
        for(int i = 0; i<QuestionListItems.size();i++){
            if(QuestionListItems[i]){
                delete QuestionListItems[i];
            }
        }
        QuestionListItems.clear();

        for(int i = currentPage*20; i < QuestionList.size() && i-currentPage*20 <20;i++){
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget_question);
            QuestionListWidgetItems.push_front(item);
            QuestionListItem *questionListItem = new QuestionListItem();
            questionListItem->setUserName(QuestionList[i]->getCreateUserName());
            questionListItem->setTitle(QuestionList[i]->getQuestionTitle());
            for(int j=0;j<MainWindow::UserList.size();j++){
                if(QuestionList[i]->getCreateUserName() == UserList[j].getUserName()){
                    questionListItem->setImageId(UserList[j].getImageId());
                    qDebug()<<UserList[j].getImageId();
                    break;
                }
            }
            questionListItem->setDetail(QuestionList[i]->getDetail());
            questionListItem->inflate();
            QuestionListItems.push_front(questionListItem);
        }
        for(int i = 0; i < QuestionListWidgetItems.size();i++){
            ui->listWidget_question->setItemWidget(QuestionListWidgetItems[i],QuestionListItems[i]);
        }
    }
    ui->listWidget_question->show();
    ui->stackedWidget->setCurrentIndex(1);
}
