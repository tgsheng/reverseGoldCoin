#include "playscene.h"
#include <QDebug>
#include <QIcon>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSound>
#include "mypushbutton.h"
#include "chooselevelscene.h"
#include "mycoin.h"
#include "dataconfig.h"

PlayScene::PlayScene(int level)
{
    this->level = level;        //传递进来关卡数

    this->setFixedSize(320,588);        //设置窗口大小
    this->setWindowTitle("第"+QString::number(level)+"关");           //设置窗口标题
    this->setWindowIcon(QIcon(":/prefix1/resource/image/Coin0001.png"));            //设置窗口图标

    QMenuBar* menuBarPointer = menuBar();
    QMenu* startMenu = menuBarPointer->addMenu("开始");
    QAction* quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,this,[=](){
        this->close();
    });

    //显示关卡数
    QLabel* levelLabel = new QLabel;
    levelLabel->setParent(this);
    levelLabel->setText("Level："+QString::number(level));
    levelLabel->setGeometry(QRect(30,this->height()-50,this->width(),50));             //设置位置、大小
    levelLabel->setFont(QFont("华文彩云",20));
    levelLabel->setAttribute(Qt::WA_TransparentForMouseEvents);             //设置鼠标穿透

    //创建胜利图片
    QLabel* successLabel = new QLabel;
    successLabel->setParent(this);
    QPixmap pix;
    pix.load(":/prefix1/resource/image/LevelCompletedDialogBg.png");
    successLabel->setPixmap(pix);
    successLabel->setGeometry(0,0,pix.width(),pix.height());
    successLabel->move(this->width()*0.5-pix.width()*0.5,-pix.height());

    //创建返回按钮
    MyPushButton* backButton = new MyPushButton(":/prefix1/resource/image/BackButton.png",":/prefix1/resource/image/BackButtonSelected.png");
    backButton->setParent(this);
    backButton->move(this->width()-backButton->width(),this->height()-backButton->height());

    //按下返回按钮回归主窗口
    connect(backButton,&QPushButton::clicked,this,[=](){
        QTimer::singleShot(500,[=](){
            QSound* backSound = new QSound(":/prefix2/resource/music/BackButtonSound.wav",this);
            backSound->play();

            emit this->ChooseBackButton();
        });
    });

    //记录当前关卡的数组
    dataConfig config;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->gameArray[i][j] = config.mData[this->level][i][j];
        }
    }

    //设置金币背景图
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            QLabel* label = new QLabel;
            label->setParent(this);
            label->setPixmap(QPixmap(":/prefix1/resource/image/BoardNode.png"));
            label->setGeometry(0,0,50,50);
            label->move(57+i*50,200+j*50);

            //创建金币
            QString pixPath;
            if (gameArray[i][j] == 0)
            {
                pixPath = ":/prefix1/resource/image/Coin0008.png";
            }
            if (gameArray[i][j] == 1)
            {
                pixPath = ":/prefix1/resource/image/Coin0001.png";
            }
            MyCoin* coin = new MyCoin(pixPath);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->x = i;
            coin->y = j;
            coin->flag = gameArray[i][j];
            this->myCoin[i][j] = coin;

            connect(coin,&MyCoin::clicked,this,[=](){
                QSound* coinSound = new QSound(":/prefix2/resource/music/ConFlipSound.wav",this);
                coinSound->play();

                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        myCoin[i][j]->isWin = true;
                    }
                }

                coin->reverse();
                gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;

                if (coin->x < 3)
                {
                    this->myCoin[coin->x + 1][coin->y]->reverse();
                    gameArray[coin->x + 1][coin->y] = gameArray[coin->x + 1][coin->y] == 0 ? 1 : 0;
                }
                if (coin->x > 0)
                {
                    this->myCoin[coin->x - 1][coin->y]->reverse();
                    gameArray[coin->x - 1][coin->y] = gameArray[coin->x - 1][coin->y] == 0 ? 1 : 0;
                }
                if (coin->y < 3)
                {
                    this->myCoin[coin->x][coin->y + 1]->reverse();
                    gameArray[coin->x][coin->y + 1] = gameArray[coin->x][coin->y + 1] == 0 ? 1 : 0;
                }
                if (coin->y > 0)
                {
                    this->myCoin[coin->x][coin->y - 1]->reverse();
                    gameArray[coin->x][coin->y - 1] = gameArray[coin->x][coin->y - 1] == 0 ? 1 : 0;
                }

                this->isWin = true;
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (myCoin[i][j]->flag == false)
                        {
                            this->isWin = false;
                            break;
                        }
                    }
                }

                if (this->isWin == true)
                {
                    QSound* coinSound = new QSound(":/prefix2/resource/music/LevelWinSound.wav",this);
                    coinSound->play();

                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            myCoin[i][j]->isWin = true;
                        }
                    }

                    QPropertyAnimation* animation = new QPropertyAnimation(successLabel,"geometry");
                    animation->setDuration(1000);
                    animation->setStartValue(QRect(successLabel->x(),successLabel->y(),successLabel->width(),successLabel->height()));
                    animation->setEndValue(QRect(successLabel->x(),successLabel->y()+120,successLabel->width(),successLabel->height()));
                    animation->setEasingCurve(QEasingCurve::OutBounce);
                    animation->start(QAbstractAnimation::DeleteWhenStopped);
                }
                else
                {
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            myCoin[i][j]->isWin = false;
                        }
                    }
                }

            });
        }
    }


}

void PlayScene::paintEvent(QPaintEvent *event)
{
    //取背景图
    QPixmap pixmap1;
    pixmap1.load(":/prefix1/resource/image/PlayLevelSceneBg.png");

    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap1);

    pixmap1.load(":/prefix1/resource/image/Title.png");
    pixmap1 = pixmap1.scaled(pixmap1.width()*0.5,pixmap1.height()*0.5);
    painter.drawPixmap(10,30,pixmap1);
}
