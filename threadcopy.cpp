#include "threadcopy.h"

ThreadCopy::ThreadCopy(QObject *parent) : QThread(parent),runningState(true),writesize(0)
{

}

ThreadCopy::~ThreadCopy()
{

}
bool ThreadCopy::getRunningState() const
{
    return runningState;
}

void ThreadCopy::setRunningState(bool value)
{
    runningState = value;
}

void ThreadCopy::getWritePath(QString fatherWritePath)
{
    this->writePath = fatherWritePath;
}

void ThreadCopy::setWriteSize(int a)
{
    this->writesize=a;
}

void ThreadCopy::getReadPath(QString fatherReadPath)
{
    this->readPath = fatherReadPath;
}

void ThreadCopy::run()
{

    QFile readFile(readPath);
    QFile writeFile(writePath);
    readFile.open(QIODevice::ReadOnly);
    writeFile.open(QIODevice::WriteOnly|QIODevice::Append);
    //字节数组类
    QByteArray array;
    //读取的字节
    qint64 totalsize = readFile.size();
    readFile.seek(writesize);
    writeFile.seek(writesize);
    while(!readFile.atEnd())
    {
        if(!runningState)
        {
            return;
        }

        //读取数据
        array=readFile.read(1024);
        //写出数据
        writesize+=writeFile.write(array);
        //计算百分比
        qint64 value=100 * writesize/totalsize;
        //设置给进度条
        emit valueSignal(value);// 发射自定义信号
    }

    //清空缓存区
    writeFile.flush();

    //关闭文件流
    readFile.close();
    writeFile.close();
}
