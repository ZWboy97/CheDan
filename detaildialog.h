#ifndef DETAILDIALOG_H
#define DETAILDIALOG_H

#include <QDialog>
#include "question.h"
#include <QListWidget>
#include "answerlistitem.h"
#include "user.h"

namespace Ui {
class DetailDialog;
}
/**
 * @brief The DetailDialog class ，问题详情界面，需要传入问题的指针，以便于进行更新操作
 */
class DetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DetailDialog(Question* selectedQuestion,QWidget *parent = 0);
    ~DetailDialog();
    //getter and setter
    void setSelectedQuestion(Question* question);
    Question* getSelectedQuestion();
    //Qt UI 操作
    void refreshAnserList();    //更新回答列表显示

private slots:
    void on_pushButton_clicked();

    void on_pushButton_quit_answer_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_quit_focus_clicked();

    void on_pushButton_focus_add_clicked();

    void add_focus(User);

    void on_pushButton_userImage_clicked();

    void on_pushButton_prevpage_clicked();

    void on_pushButton_nextpage_clicked();

private:

    Question* SelectedQuestion;             //传入选中问题的指针
    Answer* PrepareAnswer;                  //保存正在编辑的回答
    User CurrentUser;                       //当前提问者，需要基于name到用户库检索
    User WantToFocusUser;                   //准备关注的用户
    QVector <Answer*> AnswerList;           //回答数据列表
    QVector <QListWidgetItem*> AnswerListWidgetItems;  //用于配合回答自定义控件的显示
    QVector <AnswerListItem*> AnswerListItems;          //用于配合回答自定义控件的显示
    int Pages;      //总页数
    int currentPage;    //当前页数

private:
    Ui::DetailDialog *ui;
};

#endif // DETAILDIALOG_H
