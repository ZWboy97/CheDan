#include "question.h"
#include "basicinfo.h"
#include "QDebug"
#include "tools.h"
/**
 * @brief Question::Question
 * 共有继承自basicinfo类，表征用户提问的问题
 */
Question::Question()
{
    QuestionTitle = "未知";
    AnswerNum = 0;
}
/**
 * @brief Question::Question 重载构造函数
 * @param title
 * @param detail
 * @param creatorname
 * @param userid
 * @param createtime
 */
Question::Question(QString title,QString detail,QString creatorname,QString userid,QDate createtime){
    QuestionTitle = title;
    Detail = detail;
    CreateUserName = creatorname;
    CreatUserId = userid;
    CreatDate = createtime;
    AnswerNum = 0;
    Id = QString::number(Tools::getNextId());
}

/******************************getter 和 setter*******************************/
void Question::setQuestionTitle(QString title){
    QuestionTitle = title;
}

QString Question::getQuestionTitle(){
    return QuestionTitle;
}
QVector<Answer> Question::getAnswer(){
    return AnswerList;
}
void Question::setAnswerNum(int num){
    AnswerNum = num;
}
int Question::getAnswerNum(){
    return AnswerNum;
}

/*****************************更新对象内容***********************************/
/**
 * @brief Question::addAnswerNum 回答数加一
 */
void Question::addAnswerNum(){
    AnswerNum++;
}
/**
 * @brief Question::updateAnswerAt 更新回答列表中第i个位置的内容，主要是点赞数等
 * @param i
 * @param answer
 */
void Question::updateAnswerAt(int i,Answer answer){
    AnswerList[i] = answer;
}
/**
 * @brief Question::addAnAnswer 在回答列表中新添加一个回答
 * @param answer
 */
void Question::addAnAnswer(Answer answer){
    AnswerList.push_front(answer);
    qDebug()<<"添加一个回答";
}
/**********************************重载运算符*********************************/
/**
 * @brief Question::operator = 重载 = 运算符
 * @param src
 * @return
 */
void Question::operator= (Question src){
    CreateUserName = src.getCreateUserName();
    CreatDate =src.getCreateTime();
    CreatUserId =src.getCreatUserId();
    Detail = src.getDetail();
    Id = src.getId();
    QuestionTitle = src.getQuestionTitle();
    AnswerNum = src.getAnswerNum();
}

/*******************************覆盖实现父类虚函数*****************************/
/**
 * @brief Question::display 格式化输出问题到命令行
 */
void Question::display() const{
    qDebug()<<"问题信息：\n"<<"创建者："<<CreateUserName<<"\n创建者ID："<<CreatUserId<<"\n创建日期："<<CreatDate.toString()<<"\n问题内容："<<Detail<<"\n问题标题："<<QuestionTitle;
}
/**
 * @brief Question::saveToDateBase 将此问题保存到数据库
 */
void Question::saveToDateBase() const{
    //等待编写，将数据提交到问题数据库
}
void Question::creator() const{
    qDebug()<<"创建一个问题";
}

