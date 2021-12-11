#include "mycoin.h"
#include "playscene.h"

MyCoin::MyCoin(QString imagePath)
{
    QPixmap pixmap;
    bool returnNumber = pixmap.load(imagePath);
    if (returnNumber == false)
    {
        QString markedWord = QString("图片加载失败，失败路径为%1").arg(imagePath);
        return;
    }
    else
    {
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));

        this->timerGold = new QTimer(this);
        this->timerSilver = new QTimer(this);

        connect(timerGold,&QTimer::timeout,this,[=](){
            QPixmap pixmap;
            QString imagePath2 = QString(":/prefix1/resource/image/Coin000%1.png").arg(this->min++);
            bool returnNumber = pixmap.load(imagePath2);
            if (returnNumber == false)
            {
                QString markedWord = QString("图片加载失败，失败路径为%1").arg(imagePath);
                return;
            }
            else
            {
                this->setFixedSize(pixmap.width(),pixmap.height());
                this->setStyleSheet("QPushButton{border:0px;}");
                this->setIcon(pixmap);
                this->setIconSize(QSize(pixmap.width(),pixmap.height()));
            }

            if (this->min > this->max)
            {
                this->min = 1;
                this->timerGold->stop();
                this->isAnimation = false;
            }
        });

        connect(timerSilver,&QTimer::timeout,this,[=](){
            QPixmap pixmap;
            QString imagePath2 = QString(":/prefix1/resource/image/Coin000%1.png").arg(this->max--);
            bool returnNumber = pixmap.load(imagePath2);
            if (returnNumber == false)
            {
                QString markedWord = QString("图片加载失败，失败路径为%1").arg(imagePath);
                return;
            }
            else
            {
                this->setFixedSize(pixmap.width(),pixmap.height());
                this->setStyleSheet("QPushButton{border:0px;}");
                this->setIcon(pixmap);
                this->setIconSize(QSize(pixmap.width(),pixmap.height()));
            }

            if (this->max < this->min)
            {
                this->max = 8;
                this->timerSilver->stop();
                this->isAnimation = false;
            }
        });
    }
}

void MyCoin::reverse()
{
    if (this->flag == true)
    {
        this->timerGold->start(30);
        this->flag = false;
    }
    else
    {
        this->timerSilver->start(30);
        this->flag = true;
    }

    this->isAnimation = true;
}

void MyCoin::mousePressEvent(QMouseEvent *event)
{
    if (this->isAnimation == true || this->isWin == true)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(event);
    }
}
