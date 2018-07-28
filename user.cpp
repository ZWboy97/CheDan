#include "user.h"
#include <QDebug>
using namespace std;

User::User()
{
    UserID = "未填写";
    UserName = "未填写";
    Password = "未填写";
    PraiseNum = 0;
    AnswerNum = 0;
    QuestionNum = 0;
}
User::User(QString name,QString userId,QString password){
    UserID = userId;
    UserName = name;
    Password = password;
    PraiseNum = 0;
    AnswerNum = 0;
    QuestionNum = 0;
}

/***********************************转换方法*************************************/
/**
 * @brief User::toQString 将user对象以字符串形式格式化成字符串
 * @return
 */
QString User::toQString(){
    QString str= UserName +","+ UserID +","+Password+","+QString::number(ImageId)+","
            +QString::number(PraiseNum)+","+QString::number(QuestionNum)+","
            +QString::number(AnswerNum)+","+focusListToQString();
    return str;
}
/**
 * @brief User::focusListToQString 将关注列表转化为格式化字符串输出
 * @return
 */
QString User::focusListToQString(){
    QString str;
    for(int i=0; i<FocusUserList.size();i++){
        str = str +FocusUserList[i]+"#";
    }
    return str;
}
/**
 * @brief User::focusFromString 从格式化字符串读取关注用户id列表
 * @param focusstr
 */
void User::focusFromString(QString focusstr){
    for(int i=0; focusstr.section('#',i,i).trimmed() !="";i++){
        FocusUserList.push_back(focusstr.section('#',i,i).trimmed());
    }
}
/**
 * @brief User::fromString 读取格式化字符串，解析User信息
 * @param src
 */
void User::fromString(QString src){
    UserName = src.section(',',0,0).trimmed();
    UserID = src.section(',',1,1).trimmed();
    Password = src.section(',',2,2).trimmed();
    ImageId = src.section(',',3,3).trimmed().toInt(nullptr,10);
    PraiseNum = src.section(',',4,4).trimmed().toInt(nullptr,10);
    QuestionNum = src.section(',',5,5).trimmed().toInt(nullptr,10);
    AnswerNum = src.section(',',6,6).trimmed().toInt(nullptr,10);
    QString focusstr = src.section(',',7,7).trimmed();

    for(int i=0; focusstr.section('#',i,i).trimmed() !="";i++){
        FocusUserList.push_back(focusstr.section('#',i,i).trimmed());
    }
}

/**
 * @brief User::operator = 重载 = 运算符
 * @param src
 */
void User::operator= (User src){
    UserName = src.getUserName();
    UserID = src.getUserId();
    Password = src.getPassword();
    FocusUserList = src.getFocusList();
    PraiseNum = src.getPrasieNum();
    AnswerNum = src.getAnswerNum();
    QuestionNum = src.getQuestionNum();
    ImageId = src.getImageId();
}


/************************************getter和setter********************************/
QString User::getUserName(){
    return UserName;
}
QString User::getUserId(){
    return UserID;
}
QString User::getPassword(){
    return Password;
}
QVector<QString> User::getFocusList(){
    return FocusUserList;
}
int User::getPrasieNum(){
    return PraiseNum;
}
int User::getQuestionNum(){
    return QuestionNum;
}
int User::getAnswerNum(){
    return AnswerNum;
}
void User::setUserName(QString username){
    UserName = username;
}
void User::setUserId(QString userid){
    UserID = userid;
}
void User::setUserPassword(QString password){
    Password = password;
}
void User::setFocusList(QVector<QString> focusUserList){
    for(int i=0;i<focusUserList.size()-1;i++)
    {
        FocusUserList.push_back(focusUserList[i]);
    }
}
void User::setPraiseNum(int num){
    PraiseNum = num;
}
void User::setQuestionNum(int num){
    QuestionNum = num;
}
void User::setAnserNum(int num){
    AnswerNum = num;
}
void User::setImageId(int imageid){
    ImageId = imageid;
}
int User::getImageId(){
    return ImageId;
}

/**********************************更新User对象内容,adder*****************************/
void User::addPraiseNum(){
    PraiseNum++;
}

void User::addQuestionNum(){
    QuestionNum++;
}

void User::addAnswerNum(){
    AnswerNum++;
}

void User::addFocusUser(QString focusUsername){

    FocusUserList.push_front(focusUsername);
}




