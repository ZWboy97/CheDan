#ifndef USERLISTITEM_H
#define USERLISTITEM_H

#include <QWidget>
#include <QString>

namespace Ui {
class UserListItem;
}

class UserListItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserListItem(QWidget *parent = 0);
    ~UserListItem();
    void setUserName(QString name);
    QString getUserName();
    void inflate();

private:
    QString UserName;

private:
    Ui::UserListItem *ui;
};

#endif // USERLISTITEM_H
