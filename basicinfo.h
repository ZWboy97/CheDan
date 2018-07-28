#ifndef BASICINFO_H
#define BASICINFO_H

#include<QString>
#include<QDate>


class BasicInfo
{
public:
    BasicInfo();
    //getter和setter
    void setId(QString id);
    void setCreateUserName(QString createUserName);
    void setCreatTime(QDate creatdate);
    void setCreatUserId(QString creatUserId);
    void setDetail(QString detail);
    QString getCreateUserName();
    QString getId();
    QString getCreatUserId();
    QDate getCreateTime();
    QString getDetail();
    //纯虚函数
    virtual void display() const = 0;           //将对象内容输出到命令行
    virtual void saveToDateBase() const = 0;    //将对象内容保存到数据库
    virtual void creator() const = 0;           //创建问题或者回答

protected:
    QString Id;                     //唯一性id
    QString CreateUserName;         //信息创建者
    QString CreatUserId;            //信息创建者id
    QDate CreatDate;                //创建日期
    QString Detail;                 //创建内容，在子类中作为不同的用处

};
#endif // BASICINFO_H
