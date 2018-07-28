#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QVector>
#include "question.h"
#include "user.h"
#include "questionlistitem.h"
#include "userlistitem.h"
#include "detaildialog.h"

namespace Ui {
class MainWindow;
}
/**
 * @brief The MainWindow class 主界面
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void refreshQuestionList();     //刷新并填充提问列表


public:
    Question* PrepareQuestion;                          //保存缓存待提交的提问
    static User CurrentUser;                            //当前用户信息
    QVector<Question*> QuestionList;                    //保存当前已存在的问题，数据来自数据库读取，并为问题列表提供最原始的数据
    QVector <QListWidgetItem*> QuestionListWidgetItems; //问题列表的item列表
    QVector <QuestionListItem*> QuestionListItems;      //问题列表每个item的布局列表
    QVector <User*> FocusUserList;                      //保存当前用户的关注列表，数据来自数据库读取，原始数据
    QVector <QListWidgetItem*> FocusListWidgetItems;    //关注列表的item控件列表
    QVector <UserListItem*> FocusListItems;             //关注列表的每个item的布局列表
    int Pages;                                          //问题列表的页码
    int currentPage;                                    //问题列表的当前页码

    static QVector<User> UserList;                      //零时的用户列表，之后通过数据库查询

private slots:
    void on_pushButton_send_question_clicked();

    void on_pushButton_time_line_clicked();

    void on_pushButton_collection_focus_clicked();

    void on_listWidget_question_clicked(const QModelIndex &index);

    void on_pushButton_summit_question_clicked();

    void on_pushButton_image_clicked();

    void on_pushButton_logout_clicked();

    void on_pushButton_quit_clicked();

    void on_pushButton_quit_manager_clicked();

    void on_pushButton_nextpage_clicked();

    void on_pushButton_prevpage_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
