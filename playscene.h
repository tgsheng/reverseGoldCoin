#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QMenuBar>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    int level;
    PlayScene(int level);

    void paintEvent(QPaintEvent* event);

    int gameArray[4][4];

    MyCoin* myCoin[4][4];

    bool isWin = true;
signals:
    void ChooseBackButton();
};

#endif // PLAYSCENE_H
