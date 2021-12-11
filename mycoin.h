#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString imagePath);

    int x;
    int y;
    bool flag;

    void reverse();
    QTimer* timerGold;
    QTimer* timerSilver;
    int min = 1;
    int max = 8;
    bool isAnimation = false;
    void mousePressEvent(QMouseEvent* event);

    bool isWin = false;
signals:

};

#endif // MYCOIN_H
