#include "tools.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include "user.h"

QString getImageStyleSheet(int imageid);
int Tools::NextId = 0;
int getNextId();
void addNextId();
void setStartId(int id);
bool createDataFile(const QString& strFileName);//创建数据库文件
bool openDataBase(const QString& strFileName);//打开数据库文件(Sqlite,*.db文件)
void closeDataBase(); //关闭数据库
QSqlDatabase Tools::m_db; //数据库对象
void createUserTable();//创建用户数据表
void addUserToUserTable(User newUser);//添加新用户到用户表
void updateUserInfpToDateBase(User updateUserInfo);//基于userid修改用户信息
bool loginQuery(QString userName,QString password);//基于username以及password进行登陆验证操作

void testDuoTai(BasicInfo* info);//测试多态


Tools::Tools()
{

}

QString Tools::getImageStyleSheet(int imageid){
    switch (imageid) {
    case 1:
        return "background-color: rgb(255, 255, 255,0%);border-image: url(:/Resource/head_pic.png);";
        break;
    case 2:
        return "background-color: rgb(255, 255, 255,0%);border-image: url(:/Resource/head_pic1.png);";
        break;
    case 3:
        return "background-color: rgb(255, 255, 255,0%);border-image: url(:/Resource/head_pic2.png);";
        break;
    case 4:
        return "background-color: rgb(255, 255, 255,0%);border-image: url(:/Resource/head_pic3.png);";
        break;
    case 5:
        return "background-color: rgb(255, 255, 255,0%);border-image: url(:/Resource/head_pic4.png);";
        break;
    case 6:
        return "background-color: rgb(255, 255, 255,0%);border-image: url(:/Resource/head_pic5.png);";
        break;
    case 7:
        return "background-color: rgb(255, 255, 255,0%);border-image: url(:/Resource/head_pic6.png);";
        break;
    case 8:
        return "background-color: rgb(255, 255, 255,0%);border-image: url(:/Resource/head_pic7.png);";
        break;
    default:
        return "background-color: rgb(255, 255, 255,0%);border-image: url(:/Resource/head_pic.png);";
        break;
    }
}

int Tools::getNextId(){
    int i = NextId;
    addNextId();
    return i;
}
void Tools::addNextId(){
    NextId++;
}
void Tools::setStartId(int id){
    NextId = id;
}

/**
 * @brief Tools::createDataFile 创建数据库文件
 * @param strFileName
 * @return 返回是否创建成功
 */
bool Tools::createDataFile(const QString& strFileName){
    if(!QFile::exists(strFileName))//文件不存在，则创建
    {
        QDir fileDir = QFileInfo(strFileName).absoluteDir();
        QString strFileDir = QFileInfo(strFileName).absolutePath();
        if(!fileDir.exists()) //路径不存在，创建路径
        {
            fileDir.mkpath(strFileDir);
        }
        QFile dbFile(strFileName);
        if(!dbFile.open(QIODevice::WriteOnly))//未成功打开
        {
            dbFile.close();
            return false;
        }
        dbFile.close();
    }
    return true;
}
/**
 * @brief Tools::openDataBase 打开数据库文件
 * @param strFileName
 * @return 返回是否打开成功
 */
bool Tools::openDataBase(const QString& strFileName){
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(strFileName);
    if(m_db.open())
    {
        return true;
    }
    return false;
}
/**
 * @brief Tools::closeDataBase 关闭数据库
 */
void Tools::closeDataBase(){
    m_db.close();
}
/**
 * @brief Tools::createUserTable 创建用户数据表
 */
void Tools::createUserTable(){
    QString strSql = "create table user("
                     "userid VARCHAR(20) PRIMARY KEY  , "   //user id
                     "username VARCHAR(100), "              //user name
                     "password VARCHAR(50),"                //password
                     "imageid INTEGER,"                     //imageid
                     "focuslist TEXT"                       //focuslist
                     "praisenum INTEGER"                    //被赞次数
                     "questionnum INTEGER"                  //提问次数
                     "answernum INTEGER);";                 //回答次数
    QSqlQuery query(Tools::m_db);
    query.exec(strSql);//建表

    QString strIndexSql = "CREATE INDEX user_index1 on user(id);";
}
/**
 * @brief Tools::addUserToUserTable 添加新用户到数据库用户表
 * @param newUser
 */
void Tools::addUserToUserTable(User newUser)
{
    QString strSql;
    QSqlQuery query(Tools::m_db);
    strSql.append("INSERT INTO user(userid, username, password, imageid, focuslist, praisenum, questionnum, answernum)"
                          " VALUES (:userid, :username, :password, :imageid, :focuslist, :praisenum, :questionnum, :answernum)"); //需要绑定的字段
    query.prepare(strSql);
    query.bindValue(":userid",newUser.getUserId());
    query.bindValue(":username",newUser.getUserName());
    query.bindValue(":password",newUser.getPassword());
    query.bindValue(":imageid",newUser.getImageId());
    query.bindValue(":focuslist",newUser.focusListToQString());
    query.bindValue(":praisenum",newUser.getPrasieNum());
    query.bindValue(":questionnum",newUser.getQuestionNum());
    query.bindValue(":answernum",newUser.getAnswerNum());

    bool bResult = query.exec();
    qDebug() << "添加新用户到数据库结果：" << bResult;
}

/**
 * @brief updateUserInfpToDateBase 基于userid修改用户信息
 * @param updateUserInfo
 */
void Tools::updateUserInfpToDateBase(User updateUserInfo)
{
    QString strSql = "UPDATE user "
                     "SET username = :username, password = :password, imageid = :imageid,"
                     "   focuslist = :focuslist, praisenum = :praisenum,"
                     " questionnum = :questionnum, answernum = :answernum"
                     "WHERE userid = :id";
    QSqlQuery query(Tools::m_db);
    query.prepare(strSql);
    query.bindValue(":username",updateUserInfo.getUserName());
    query.bindValue(":password",updateUserInfo.getPassword());
    query.bindValue(":imageid",updateUserInfo.getImageId());
    query.bindValue(":focuslist",updateUserInfo.focusListToQString());
    query.bindValue(":praisenum",updateUserInfo.getPrasieNum());
    query.bindValue(":questionnum",updateUserInfo.getQuestionNum());
    query.bindValue(":answernum",updateUserInfo.getAnswerNum());
    bool bReuslt = query.exec();
    qDebug()<< "更新用户到数据库结果："<<bReuslt;
}
/**
 * @brief Tools::loginQuery 基于username以及password进行登陆验证操作
 * @param userName
 * @param password
 */
bool Tools::loginQuery(QString userName,QString password){
    QString strSql = "SELECT * FROM user WHERE username = :username";
    QSqlQuery query(Tools::m_db);
    query.prepare(strSql);
    query.bindValue(":username",userName);
    query.exec();

    while (query.next()) {
        QString result = query.value("password").toString();
        if(result == password){
            return true;
        }
    }
    return false;
}

/**
 * @brief Tools::testDuoTai 测试多态
 * @param info
 */
void Tools::testDuoTai(BasicInfo* info){
    info->creator();
    info->display();

}

