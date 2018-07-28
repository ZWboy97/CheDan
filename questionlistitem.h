#ifndef QUESTIONLISTITEM_H
#define QUESTIONLISTITEM_H

#include <QWidget>
#include <QString>

namespace Ui {
class QuestionListItem;
}

class QuestionListItem : public QWidget
{
    Q_OBJECT

public:
    explicit QuestionListItem(QWidget *parent = 0);
    ~QuestionListItem();
    void setUserName(QString name);
    void setTitle(QString title);
    QString getName();
    QString getTitle();
    QString getDetail();
    void setDetail(QString detail);
    void setImageId(int imageid);
    void inflate();

private slots:
private:
    QString UserName;
    QString Title;
    QString Detail;
    int ImageId;

private:
    Ui::QuestionListItem *ui;
};

#endif // QUESTIONLISTITEM_H
