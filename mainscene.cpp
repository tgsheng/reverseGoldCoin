#include "mainscene.h"
#include "ui_mainscene.h"
#include <QDebug>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent): QMainWindow(parent), ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //点击‘退出’按钮退出当前窗口
    connect(ui->actiona,&QAction::triggered,this,[=](){
        this->close();
    });

    //设置窗口属性：标题、图标、大小
    this->setWindowTitle("翻金币");
    this->setWindowIcon(QIcon(":/prefix1/resource/image/Coin0001.png"));
    this->setFixedSize(320,588);

    //创建开始按钮，设置图片、位置
    MyPushButton* startButton = new MyPushButton(":/prefix1/resource/image/MenuSceneStartButton.png");
    startButton->setParent(this);
    startButton->move(this->width()*0.5-startButton->width()*0.5,this->height()*0.7);
    this->choosePointer = new ChooseLevelScene;
    connect(startButton,&MyPushButton::clicked,this,[=](){
        QSound* startSound = new QSound(":/prefix2/resource/music/TapButtonSound.wav",this);
        startSound->play();

        startButton->downJump();
        startButton->upJump();

        QTimer::singleShot(500,this,[=](){          //延时0.5秒执行lambda表达式
            this->choosePointer->setGeometry(this->geometry());
            this->choosePointer->show();            //显示‘选关’窗口
            this->hide();           //关闭‘开始’窗口
        });
    });

    connect(choosePointer,&ChooseLevelScene::ChooseBackButton,this,[=](){
        this->setGeometry(this->choosePointer->geometry());
        this->show();
        choosePointer->hide();
    });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent* event)
{
    //设置开始-背景图片
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/prefix1/resource/image/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    //设置开始-标题文件
    pixmap.load(":/prefix1/resource/image/Title.png");
    pixmap = pixmap.scaled(pixmap.width()*0.5,pixmap.height()*0.5);         //对图片进行缩放
    painter.drawPixmap(10,30,pixmap);
}
