#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gamefield.h"

#include <QWidget>
#include <QPushButton>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>

class Game : public QWidget {
    //Q_OBJECT

public:
    Game(QWidget *parent = 0);
    virtual ~Game() {}


protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void mousePressEvent(QMouseEvent *e);
      void resizeEvent(QResizeEvent *e);

private slots:
    void OnPlusSpeed();
    void OnMinusSpeed();
    void Pause();

    void OnPlusSize();
    void OnMinusSize();

    void OnChangeSize();

private:
    static const int CELL_SIZE = 10;

    int frameLeft, frameTop;
    int frameWidth, frameHeight;

    int timerId;
    bool paused = false;
    int speed = 1;
    int cycles = 0;

    GameField *field;

    QPushButton *speedLbl;

    QLineEdit *widthEdit;
    QLineEdit *heightEdit;

    QFrame *mainFrame;

    void initGame();
    void loop();

    void draw();
    void update();

    void drawField();
    void drawPerimeter();
    void drawUI();

    void updateFrameMeasurements();

    bool isWithinFrame(int x, int y);
};

#endif // GAMEBOARD_H
