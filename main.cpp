#include "loginwindow.h"
#include <QApplication>
#include "user.h"
#include "mainwindow.h"
#include "tools.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();

    //假装几个用户数据
    User temp;
    temp.setUserName("JackChance");
    temp.setUserId("1");
    temp.setUserPassword("123456");
    temp.setQuestionNum(1);
    temp.setPraiseNum(2);
    temp.setImageId(4);
    temp.setAnserNum(5);
    temp.addFocusUser("1");
    temp.addFocusUser("2");
    MainWindow::UserList.push_front(temp);
    temp.setUserName("enenenen");
    temp.setUserId("2");
    temp.setUserPassword("123456");
    temp.setQuestionNum(1);
    temp.setPraiseNum(2);
    temp.setImageId(5);
    temp.setAnserNum(5);
    temp.addFocusUser("1");
    temp.addFocusUser("2");
    MainWindow::UserList.push_front(temp);
    temp.setUserName("Pig");
    temp.setUserId("1");
    temp.setUserPassword("123456");
    temp.setQuestionNum(1);
    temp.setPraiseNum(2);
    temp.setImageId(2);
    temp.setAnserNum(5);
    temp.addFocusUser("1");
    temp.addFocusUser("2");
    MainWindow::UserList.push_front(temp);
    temp.setUserName("Cat");
    temp.setUserId("7");
    temp.setUserPassword("123456");
    temp.setQuestionNum(1);
    temp.setPraiseNum(2);
    temp.setImageId(1);
    temp.setAnserNum(5);
    temp.addFocusUser("1");
    temp.addFocusUser("2");
    MainWindow::UserList.push_front(temp);
    temp.setUserName("Dog");
    temp.setUserId("1");
    temp.setUserPassword("123456");
    temp.setQuestionNum(1);
    temp.setPraiseNum(2);
    temp.setImageId(7);
    temp.setAnserNum(5);
    temp.addFocusUser("1");
    temp.addFocusUser("2");
    MainWindow::UserList.push_front(temp);

    //测试多态
    Question* question = new Question("你在电影院遇到过哪些奇葩的事情？？","奇闻异事！！！！","JackChance","123453",QDate::currentDate());
    Answer* answer = new Answer();
    answer->setCreateUserName("JackChance");
    answer->setCreatTime(QDate::currentDate());
    answer->setDetail("这么高大上的问题，当然是留给楼下来回答了。。。。");
    answer->setPraiseNum(100);
    answer->setDissNum(10);
    answer->setCreatUserId("12138");
    answer->setId("1233");
    qDebug()<<"多态测试";
    Tools::testDuoTai(question);
    Tools::testDuoTai(answer);



    return a.exec();
}
