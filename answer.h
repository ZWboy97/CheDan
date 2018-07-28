#ifndef ANSWER_H
#define ANSWER_H
#include "basicinfo.h"
/**
 * @brief Answer::Answer
 * 共有继承自basiconfo类，表征问题下的回答
 */
class Answer:public BasicInfo
{
public:
    Answer();
    //getter和setter
    void setPraiseNum(int praiseNum);
    int getPraiseNum();
    void setDissNum(int dissNum);
    int getDissNum();
    //更新内容
    void addDiss();
    void subAPraise();
    void subDiss();
    void addAPrasie();

    //覆盖虚函数
    void display() const override;           //将回答格式化输出到命令行
    void saveToDateBase() const override;    //将回答提交到数据库
    void creator() const override;           //创建问题或者回答

private:
    int PraiseNum;
    int DissNum;
};

#endif // ANSWER_H
