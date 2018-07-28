#ifndef ANSWERLISTITEM_H
#define ANSWERLISTITEM_H
#include <QWidget>
#include "answer.h"
#include "QString"
#include <QMessageBox>
#include "user.h"
#include "question.h"

namespace Ui {
class AnswerListItem;
}
/**
 * @brief AnswerListItem::AnswerListItem
 * @param parent
 *   qt中自定义空间类，用于问题列表在listwidget中的显示
 *   使用前需要传入需要显示的信息，并且动态加载的场景下，该对象需要通过指针方式传入listwidget中
 */
class AnswerListItem : public QWidget
{
    Q_OBJECT

public:
    explicit AnswerListItem(QWidget *parent = 0);
    ~AnswerListItem();
    //getter and setter
    QString getCreatorId();
    void setCreator(QString userid);
    void setCurrentQuestion(Question* currentQuestion);
    Question* getCurrentQuestion();
    void setAnswerIndex(int i);
    int getAnswerIndex();
    void setCurrentAnswer(Answer answer);
    //更新点赞显示
    void addPraiseNum();
    void addDissNum();
    void subPraiseNum();
    void subDissNum();
    //将获取的信息填充到控件布局展示
    void inflate();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_praise_clicked();

    void on_pushButton_diss_clicked();

signals:
    void clickToFocus(User);

private:
    Ui::AnswerListItem *ui;         //控件布局
    bool IsPraise;                  //是否点赞
    bool IsDiss;                    //是否diss
    Question* CurrentQuestion;      //当前问题指针，获取所属问题的指针，以处理点赞等信息更新操作
    Answer CurrentAnswer;           //当前问题，用于问题内容的显示
    int AnswerIndex;                //当前回答在回答列表中的位置
    int UserIndex;                  //当前用户在用户列表中的位置
    User Creator;                   //当前问题的回答者，基于回答者用户名在用户哭中检索获得

                                    //点赞按钮的stylesheet常量，用于更改点赞按钮的显示状态
    const QString STYLESHEET_PRAISE_UNCLICKED = "background-color: rgb(255, 255, 255,0%);"
                                                "border-radius:0px;"
                                                "border-image: url(:/Resource/praise_unclick.png);";
    const QString STYLESHEET_PRAISE_CLICKED = "background-color: rgb(255, 255, 255,0%);"
                                              "border-radius:0px;"
                                              "border-image: url(:/Resource/praise_clicked.png)";
    const QString STYLESHEET_DISS_UNCLICKED = "background-color: rgb(255, 255, 255,0%);"
                                              "border-radius:0px;"
                                              "border-image: url(:/Resource/diss_unclicked.png)";
    const QString STYLESHEET_DISS_CLICKED = "background-color: rgb(255, 255, 255,0%);"
                                              "border-radius:0px;"
                                              "border-image: url(:/Resource/diss_clicked.png)";


};

#endif // ANSWERLISTITEM_H
