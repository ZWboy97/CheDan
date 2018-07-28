#include "basicinfo.h"

BasicInfo::BasicInfo()
{
    Id = "未知";
    CreateUserName = "未知";
    CreatDate = QDate::currentDate();
    CreatUserId = "未知";
    Detail = "未知";
}
/***********************getter和setter************************/
void BasicInfo::setId(QString id){
    Id = id;
}
void BasicInfo::setCreateUserName(QString createUserName){
    CreateUserName = createUserName;
}
void BasicInfo::setCreatTime(QDate creatdate){
    CreatDate = creatdate;
}
void BasicInfo::setCreatUserId(QString creatUserId){
    CreatUserId = creatUserId;
}
void BasicInfo::setDetail(QString detail){
    Detail = detail;
}
QString BasicInfo::getCreateUserName(){
    return CreateUserName;
}
QString BasicInfo::getId(){
    return Id;
}
QString BasicInfo::getCreatUserId(){
    return CreatUserId;
}
QDate BasicInfo::getCreateTime(){
    return CreatDate;
}
QString BasicInfo::getDetail(){
    return Detail;
}
