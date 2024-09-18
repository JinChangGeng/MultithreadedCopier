#ifndef DIALOG_H
#define DIALOG_H

#include "ThreadCopy.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QButtonGroup *btngroup;
    QString readPath;
    QString writePath;
    ThreadCopy *copy;
    QList<QString> sizelist;
    void readFileInfo();
    void ioFile();
private slots:
    void btnClickedSlot(int);
    void valueSlot(int); // 接收子线程信号的槽函数
};

#endif // DIALOG_H
