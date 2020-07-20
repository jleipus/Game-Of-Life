#include "ruleset.h"

#include <iostream>

Ruleset::Ruleset() {}

int Ruleset::getOutcome(int value, int neighbours) {
    if(value == 1) {
        if(neighbours < 2 || neighbours > 3) {
            return 0;
        }
        else {
            return 1;
        }
    } else {
        if(neighbours == 3) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

int Ruleset::getNeighbourCount(int x, int y, GameField *field) {
    int n = 0;
    int radius = 1;

    for (int i = std::max(0, x - radius); i <= std::min(x + radius, field->getFieldWidth() - 1); i++) {
        for (int j = std::max(0, y - radius); j <= std::min(y + radius, field->getFieldHeight() - 1); j++) {
            if (i == x && j == y) {}
            else {
                n += field->getCell(i, j);
            }
        }
    }

    return n;
}
