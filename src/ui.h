#ifndef UI_H
#define UI_H

#include <QFrame>
#include <QLineEdit>
#include <QPaintEvent>
#include <QPushButton>
#include <QWidget>

#include "game.h"

class UI : public QWidget {
    //Q_OBJECT

public:
    UI(QWidget *parent = 0, Game *game = 0);
    virtual ~UI() {}

protected:
    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    Game *game;

    QFrame *mainFrame;

    QPushButton *speedAndCycleLbl;
    QLineEdit *widthEdit;
    QLineEdit *heightEdit;

    int frameLeft, frameTop;
    int frameWidth, frameHeight;

    int timerId;
    bool paused = false;

    void initUi();
    void updateFrameMeasurements();

    void draw();
    void update();

    void drawUI();
    void drawField();

private slots:
    void OnPlusSpeed();
    void OnMinusSpeed();
    void Pause();

    void OnChangeSize();

};

#endif // UI_H
