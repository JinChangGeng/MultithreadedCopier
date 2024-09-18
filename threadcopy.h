#ifndef THREADCOPY_H
#define THREADCOPY_H

#include <QObject>
#include <QThread>
#include <QDialog>
#include <QButtonGroup>
#include <QFileInfo>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QByteArray>
#include <QFileDevice>
#include <QDebug>
#include <QList>

class ThreadCopy : public QThread
{
    Q_OBJECT
public:
    explicit ThreadCopy(QObject *parent = 0);
    ~ThreadCopy();
    bool getRunningState() const;
    void setRunningState(bool value);
    void getReadPath(QString fatherReadPath);
    void getWritePath(QString fatherWritePath);
    void setWriteSize(int);

signals:
     void valueSignal(int);
protected:
    void run();
private:
    bool runningState;// 状态标记
    QString readPath;
    QString writePath;
    qint64 writesize;
public slots:
};

#endif // THREADCOPY_H
