#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QPushButton>

#include <array>

class Game : public QWidget
{
    //Q_OBJECT

public:
    Game(QWidget *parent = 0);

protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);

private slots:
    void OnPlus();
    void OnMinus();
    void Pause();

private:
    static const int SIZE = 50;
    static const int CELL_SIZE = 10;

    int timerId;
    bool paused = false;
    int speed = 10;

    std::array<std::array<int, SIZE + 2>, SIZE + 2> data = {0}; // need to replace with more memmory efficient option
    std::array<std::array<int, SIZE + 2>, SIZE + 2> nextData = {0};

    QPushButton *speedLbl;

    void initGame();
    void loop();

    void draw();
    void update();

};

#endif // GAMEBOARD_H
