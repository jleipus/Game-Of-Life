#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gamefield.h"

class Game {
public:
    Game();
    virtual ~Game() {}

    void update();
    void draw();

    int getSpeed();
    int getCycles();

    void setSpeed(int s);

    void changeFieldSize(int newWidth, int newHeight);
    void changeClickedOnCell(int x, int y); // changes the value of the cell that was clicked on

    GameField* getField();

private:
    GameField *field;

    int speed = 1;
    int cycles = 0;

};

#endif // GAMEBOARD_H
