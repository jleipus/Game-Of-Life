#include "cell.h"

Cell::Cell(int x, int y, bool val)
    : value(val) {

    left = x * (CELL_SIZE + 1);
    right = left + CELL_SIZE;

    top = y * (CELL_SIZE + 1);
    bottom = top + CELL_SIZE;
}

bool Cell::getValue() {
    return value;
}

void Cell::setValue(bool val) {
    value = val;
}

int Cell::getNeighbours() {
    return neighbours;
}
void Cell::setNeighbours(int n) {
    neighbours = n;
}

Rectangle Cell::getRectangle() {
    return Rectangle(left, right, top, bottom, CELL_SIZE, CELL_SIZE);
}
