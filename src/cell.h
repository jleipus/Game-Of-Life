#ifndef CELL_H
#define CELL_H

#include "rectangle.h"

class Cell {
public:
    static const int CELL_SIZE = 10; // size of cell in pixels

    Cell(int x, int y, bool val);
    virtual ~Cell() {}

    bool getValue();
    void setValue(bool val);

    int getNeighbours();
    void setNeighbours(int n);

    Rectangle getRectangle();

private:
    // value of cell: true = alive, false = dead
    bool value = false;
    int neighbours = 0;

    // cells location in field and size in pixels
    int left, right;
    int top, bottom;

};

#endif // CELL_H
