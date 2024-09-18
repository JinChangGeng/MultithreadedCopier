#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    btngroup=new QButtonGroup(this);
    btngroup->addButton(ui->pushButtonOpen,1);
    btngroup->addButton(ui->pushButtonSave,2);
    btngroup->addButton(ui->pushButtonStart,3);
    btngroup->addButton(ui->pushButtonClearInfo,4);
    btngroup->addButton(ui->pushButtonStop,5);
    btngroup->addButton(ui->pushButtonClearSave,6);
    btngroup->addButton(ui->pushButtonClearOpen,7);
    copy=new ThreadCopy(this);
    connect(btngroup,SIGNAL(buttonClicked(int)),SLOT(btnClickedSlot(int)));
    connect(copy,SIGNAL(valueSignal(int)),this,SLOT(valueSlot(int)));
}
Dialog::~Dialog()
{
    delete ui;
    delete copy;
}
void Dialog::btnClickedSlot(int id)
{
    if(id==1)
    {
        QString filter="所有文件(*.*);;C++(*.h *.cpp *.hpp)";
        readPath=QFileDialog::getOpenFileName(this,"打开","C:/",filter);
        //将文本框中内容转换成字符串并判断信息文本框是否为空，不为空则清除后重新写入文件信息
        bool clearInfo=ui->textBrowserInfo->toPlainText().isEmpty();
        //qDebug()<<clearInfo.isEmpty();
        if(!clearInfo)
        {
            ui->textBrowserInfo->clear();
        }
        bool clearTextOpen=ui->textBrowserOpen->toPlainText().isEmpty();
        if(!clearTextOpen)
        {
            ui->textBrowserOpen->clear();
        }
        ui->textBrowserOpen->append(readPath);
        readFileInfo();
        copy->getReadPath(readPath);

    }
    else if(id==2)
    {
        QString filter="所有文件(*.*);;C++(*.h *.cpp *.hpp)";
        writePath=QFileDialog::getSaveFileName(this,"保存","C:/",filter);
        bool clearTextSave=ui->textBrowserSave->toPlainText().isEmpty();
        if(!clearTextSave)
        {
            ui->textBrowserSave->clear();
        }
        ui->textBrowserSave->append(writePath);
        copy->getWritePath(writePath);
    }
    else if(id==3)
    {
        if(readPath=="")
        {
            QMessageBox::warning(this,"警告","请选择要打开的文件！");
            return;
        }
        if(writePath=="")
        {
            QMessageBox::warning(this,"警告","请选择要保存的路径！");
            return;
        }
        if(ui->pushButtonStart->text() == "开始")
        {
            copy->getReadPath(readPath);
            copy->getWritePath(writePath);
            copy->setRunningState(true);
            ui->pushButtonStart->setText("暂停");
            //开始子线程拷贝和UI变动
            copy->start();
        }
        else
        {
            ui->pushButtonStart->setText("开始");
            copy->setRunningState(false);
        }
    }
    else if(id==4)
    {
        ui->textBrowserInfo->clear();
    }
    else if(id==5)
    {

        ui->progressBar->setValue(0);
        copy->setRunningState(false);
        copy->setWriteSize(0);
        //恢复开始按钮
        ui->pushButtonStart->setEnabled(true);
        ui->pushButtonStart->setText("开始");

    }
    else if(id==6)
    {
        ui->textBrowserSave->clear();
    }
    else if(id==7)
    {
        ui->textBrowserOpen->clear();

    }
}
void Dialog::readFileInfo()
{
    // 创建文件信息类对象
    QFileInfo fileInfo(readPath);
    if(!fileInfo.exists())
        return;
    QString text=fileInfo.baseName();
    text.prepend("文件名称:");
    ui->textBrowserInfo->append(text);

    text = fileInfo.lastModified().toString("修改时间: yyyy-MM-dd hh:mm:ss");
    ui->textBrowserInfo->append(text);

    qint64 size = fileInfo.size();

    sizelist={"B","KB","MB","GB","TB"};
    int units_count=0;
    double sizedouble=static_cast<double>(size);

    while(sizedouble>1024&&units_count<sizelist.size()-1)
    {
        sizedouble = sizedouble/1024;
        ++units_count;
    }
    text = QString::number(sizedouble,'g',3);
    text.prepend("文件大小:").append(sizelist.at(units_count));
    ui->textBrowserInfo->append(text);

    // 获得可读性
    if(fileInfo.isReadable())
        ui->textBrowserInfo->append("文件可读");
    else
        ui->textBrowserInfo->append("文件不可读");
}
void Dialog::valueSlot(int value)
{
    ui->progressBar->setValue(value);
    if(value == 100)
    {
        this->hide();
        this->show();
        QMessageBox::information(this,"提示","拷贝完成");
        disconnect(copy, SIGNAL(valueSignal(int)), this, SLOT(valueSlot(int)));//断开连接释放资源
        delete copy;//清除旧的堆区对象
        copy=new ThreadCopy(this);
        connect(copy,SIGNAL(valueSignal(int)),this,SLOT(valueSlot(int)));
        ui->pushButtonStart->setText("开始");
        ui->progressBar->setValue(0);
    }
}
