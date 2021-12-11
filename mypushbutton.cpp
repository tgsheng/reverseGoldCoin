#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>           //动画的头文件

MyPushButton::MyPushButton(QString normalPath,QString pressPath)
{
    this->normalPath = normalPath;
    this->pressPath = pressPath;

    QPixmap pixmap;
    bool result = pixmap.load(this->normalPath);
    if (result == false)
    {
        QString errorPath = QString("图标加载失败！失败路径为：%1").arg(this->normalPath);
        qDebug() << errorPath;
    }
    else
    {
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
}

void MyPushButton::upJump()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");        //创建动画对象
    animation->setDuration(200);            //设置动画持续时间
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));      //设置起始位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));      //设置结束位置
    animation->setEasingCurve(QEasingCurve::OutBounce);         //设置动画效果
    animation->start(QAbstractAnimation::DeleteWhenStopped);            //当动画结束删除对象（释放空间）
}

void MyPushButton::downJump()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");        //创建动画对象
    animation->setDuration(200);            //设置动画持续时间
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));      //设置起始位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));      //设置结束位置
    animation->setEasingCurve(QEasingCurve::OutBounce);         //设置动画效果
    animation->start(QAbstractAnimation::DeleteWhenStopped);            //当动画结束删除对象（释放空间）
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //如果鼠标按下路径不为空，替换图案
    if (this->pressPath != "")
    {
        QPixmap pixmap;
        bool result = pixmap.load(this->pressPath);
        if (result == false)
        {
            QString errorPath = QString("图标加载失败！失败路径为：%1").arg(this->normalPath);
            qDebug() << errorPath;
        }
        else
        {
            this->setFixedSize(pixmap.width(),pixmap.height());
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pixmap);
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        }
    }

    //将其余事件交予父类处理
    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //替换为原图案
    if (this->pressPath != "")
    {
        QPixmap pixmap;
        bool result = pixmap.load(this->normalPath);
        if (result == false)
        {
            QString errorPath = QString("图标加载失败！失败路径为：%1").arg(this->normalPath);
            qDebug() << errorPath;
        }
        else
        {
            this->setFixedSize(pixmap.width(),pixmap.height());
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pixmap);
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        }
    }

    QPushButton::mouseReleaseEvent(e);
}
