#ifndef QUESTION_H
#define QUESTION_H
#include "basicinfo.h"
#include <QString>
#include "answer.h"
#include <QVector>
/**
 * @brief Question::Question
 * 共有继承自basicinfo类，表征用户提问的问题
 */
class Question:public BasicInfo
{
public:
    Question();
    Question(QString title,QString detail,QString creatorname,QString userid,QDate createtime); //重载构造函数
    //setter 和 getter
    void setQuestionTitle(QString title);
    QString getQuestionTitle();
    void addAnAnswer(Answer answer);
    QVector<Answer> getAnswer();
    void setAnswerNum(int num);
    int getAnswerNum();
    //更新对象内容
    void updateAnswerAt(int i,Answer answer);
    void addAnswerNum();
    //重载运算符
    void operator= (Question src);
    //覆盖虚函数
    void display() const override;
    void saveToDateBase() const override;
    void creator() const override;


private:
     QString QuestionTitle;             //问题标题
     QVector <Answer> AnswerList;       //回答列表
     int AnswerNum;                     //回答数目
};

#endif // QUESTION_H
