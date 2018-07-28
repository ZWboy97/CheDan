#ifndef TOOLS_H
#define TOOLS_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QVariant>
#include "user.h"
#include "basicinfo.h"

/* sql语句模版
判断数据库中是否存在某个表： SELECT 1 FROM sqlite_master where type = 'table' and  name = 'book';
判断表中是否存在某字段：SELECT 1 FROM sqlite_master where type = 'table' and name= 'book' and sql like '%idtest%';
建表语句：CREATE TABLE book(id VARCHAR(20) PRIMARY KEY  , name VARCHAR(100), info VARCHAR(100));
添加字段：ALTER TABLE book ADD descinfo VARCHAR(100);
创建索引：CREATE INDEX book_index1 on book(id);
添加：INSERT INTO book(id, name, info) VALUES('1111', 'Qt编程', '这是一本好书');
删除：DELETE FROM book  WHERE id = '1111';
更新：UPDATE book SET name = 'test' WHERE id = '1111';
精确搜索：SELECT * FROM book WHERE id = '111';
模糊搜索：SELECT * FROM book WHERE name like '%:strBookName%' ESCAPE '!';
*/



class Tools
{
public:
    Tools();

    static  QString getImageStyleSheet(int imageid);//基于imageId获得image资源地址
    static int getNextId(); //获得下一个id
    static void addNextId();    //id编号+1
    static void setStartId(int id); //设置起始的id

    //数据库操作
    static bool createDataFile(const QString& strFileName);//创建数据库文件
    static bool openDataBase(const QString& strFileName);//打开数据库文件(Sqlite,*.db文件)
    static void closeDataBase(); //关闭数据库

    static void createUserTable();//创建用户数据表
    static void addUserToUserTable(User newUser);//添加新用户到数据库用户表
    static void updateUserInfpToDateBase(User updateUserInfo);//基于userid修改用户信息
    static bool loginQuery(QString userName,QString password);//基于username以及password进行登陆验证操作

    static void testDuoTai(BasicInfo* info);





    static void dbTest(); //测试数据库


public:
    static int NextId;

    static QSqlDatabase m_db; //数据库

};

#endif // TOOLS_H
