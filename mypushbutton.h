#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(QString normalPath,QString pressPath = "");

    QString normalPath;
    QString pressPath;

    void upJump();
    void downJump();

    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
signals:

};

#endif // MYPUSHBUTTON_H
