#include "answer.h"
#include"QDebug"

/**
 * @brief Answer::Answer
 * 共有继承自basiconfo类，表征问题下的回答
 */
Answer::Answer()
{
    Id = "未知";
    CreateUserName = "未知";
    CreatDate = QDate::currentDate();
    CreatUserId = "未知";
    Detail = "未知";
    PraiseNum = 0;
    DissNum = 0;
}

/***************************getter 和 setter******************/
void Answer::setPraiseNum(int praiseNum){
    PraiseNum = praiseNum;
}
int Answer::getPraiseNum(){
    return PraiseNum;
}
void Answer::setDissNum(int dissNum){
    DissNum = dissNum;
}

int Answer::getDissNum(){
    return DissNum;
}

/**************************更新对象内容**************************/
void Answer::addAPrasie(){
    PraiseNum++;
}
void Answer::subAPraise(){
    PraiseNum--;
}
void Answer::subDiss(){
    DissNum--;
}
void Answer::addDiss(){
    DissNum++;
}
/*************************覆盖实现虚函数************************/
void Answer::display() const{
    qDebug()<<"回答信息：\n"<<"创建者："<<CreateUserName<<"\n创建者ID："<<CreatUserId<<"\n创建日期："<<CreatDate.toString()<<"\n回答内容："<<Detail;
}
void Answer::saveToDateBase() const{
    //等待编写，将数据提交到问题数据库
}
void Answer::creator() const{
    qDebug()<<"创建了一个回答";
}
