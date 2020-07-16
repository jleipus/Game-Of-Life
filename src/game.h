#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gamefield.h"

#include <QWidget>
#include <QPushButton>
#include <QFrame>

class Game : public QWidget {
    //Q_OBJECT

public:
    Game(QWidget *parent = 0);
    virtual ~Game() {}

    // UNIT TESTS
    void testGetOutcome();
    void testGetNeighbourCount();

    void testResize();
    void testCopy();
    void testChangeCellValue();

protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void mousePressEvent(QMouseEvent *e);
      void resizeEvent(QResizeEvent *e);

private slots:
    void OnPlus();
    void OnMinus();
    void Pause();

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
    QFrame *mainFrame;

    void initGame();
    void loop();

    void draw();
    void update();

    void drawField();
    void drawUI();

    void updateFrameMeasurements();

    int getOutcome(int value, int neighbours);
    int getNeighbourCount(int x, int y);
    bool isWithinFrame(int x, int y);
};

#endif // GAMEBOARD_H
