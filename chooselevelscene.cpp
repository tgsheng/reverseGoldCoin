#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    QMenuBar* menuBarPointer = menuBar();
    this->setMenuBar(menuBarPointer);
    QMenu* startMenu = menuBarPointer->addMenu("开始");
    QAction* quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,this,[=](){
        this->close();
    });
    //设置窗口属性：标题、图标、大小
    this->setWindowTitle("选择关卡");
    this->setWindowIcon(QIcon(":/prefix1/resource/image/Coin0001.png"));
    this->setFixedSize(320,588);

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

    //创建选关按钮
    for (int i = 0; i < 20 ; i++)
    {
        //创建按钮，设置图片、位置
        MyPushButton* chooseButton = new MyPushButton(":/prefix1/resource/image/LevelIcon.png");
        chooseButton->setParent(this);
        chooseButton->move(25+i%4*70,130+i/4*70);

        //设置文本显示，并设置鼠标穿透
        QLabel* label = new QLabel;
        label->setParent(this);
        label->setFixedSize(chooseButton->width(),chooseButton->width());
        label->move(25+i%4*70,130+i/4*70);
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);      //设置鼠标穿透

        //创建新的关卡
        connect(chooseButton,&QPushButton::clicked,this,[=](){
            QSound* chooseSound = new QSound(":/prefix2/resource/music/TapButtonSound.wav",this);
            chooseSound->play();

            this->playScenePointer = new PlayScene(i+1);
            this->playScenePointer->setGeometry(this->geometry());
            this->playScenePointer->show();
            this->hide();

            connect(this->playScenePointer,&PlayScene::ChooseBackButton,this,[=](){
                this->playScenePointer->hide();
                this->show();

                this->setGeometry(this->playScenePointer->geometry());

                delete this->playScenePointer;
                this->playScenePointer = NULL;
            });
        });
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    //设置开始-背景图片
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/prefix1/resource/image/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    //设置开始-标题文件
    pixmap.load(":/prefix1/resource/image/Title.png");
    painter.drawPixmap((this->width()-pixmap.width())*0.5,30,pixmap);
}
