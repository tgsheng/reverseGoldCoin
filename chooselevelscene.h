#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"
#include <QDebug>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* event);

    PlayScene* playScenePointer = NULL;
signals:
    void ChooseBackButton();
};

#endif // CHOOSELEVELSCENE_H
