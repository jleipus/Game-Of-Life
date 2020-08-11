#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <vector>

#include "cell.h"

class GameField {
public:
    static const int MAX_FIELD_SIZE = 500;
    static const int DEFAULT_FIELD_SIZE = 50;

    GameField();

    virtual ~GameField() {}

    bool getCellValue(int x, int y) const;
    void setCellValue(int x, int y, bool val);

    int getCellNeighbours(int x, int y);
    void setCellNeighbours(int x, int y, int n);

    int getFieldWidth();
    int getFieldHeight();

    Rectangle getRectangle();
    Rectangle getCellRectangle(int x, int y);

    bool cellShouldBeDrawn(int x, int y, int frameRight, int frameBottom);

    void resize(int newWidth, int newHeight);

    void printField();

private:
    // size of field in cells
    int width = 0;
    int height = 0;

    // cooridnates of field
    int left, right;
    int top, bottom;

    // vector of pointers to Cell objects
    std::vector < std::vector < Cell* > > data;

};

#endif // GAMEFIELD_H
