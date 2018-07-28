#ifndef USER_H
#define USER_H

#include <QString>
#include <QStringList>
#include<QVector>

/*用户数据类型，完成用户数据的增删查改操作*/
class User
{
public:
    User();
    User(QString name,QString userId,QString password);//重载构造函数
    //getter和setter
    QString getUserName();
    QString getUserId();
    QString getPassword();
    QVector<QString> getFocusList();
    int getPrasieNum();
    int getQuestionNum();
    int getAnswerNum();
    int getImageId();
    void setUserName(QString username);
    void setUserId(QString userid);
    void setUserPassword(QString password);
    void setFocusList(QVector<QString> focusUserList);
    void setPraiseNum(int num);
    void setQuestionNum(int num);
    void setAnserNum(int num);
    void setImageId(int imageid);
    //更新User内容
    void addPraiseNum();
    void addQuestionNum();
    void addAnswerNum();
    void addFocusUser(QString focusUsername);
    //一些转换方法
    QString toQString();                    //将User对象转换为QString，便于存储
    QString focusListToQString();           //将关注列表转换为QString，便于存储
    void fromString(QString src);           //从QStrign中解析出User属性
    void focusFromString(QString focusstr); //从QString中解析出关注列表
    //重载运算符
    void operator= (User src);              //重载=运算

private:
    QString UserID;                 //用户ID，
    QString UserName;               //用户名，具有唯一性
    QString Password;               //用户密码
    QVector <QString> FocusUserList;//内部为Username
    int PraiseNum;                  //用户被赞次数
    int QuestionNum;                //用户提问次数
    int AnswerNum;                  //用户回答次数
    int ImageId;                    //用户头像ID
};

#endif // USER_H
