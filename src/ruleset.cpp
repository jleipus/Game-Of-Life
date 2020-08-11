#include "ruleset.h"

#include <iostream>
#include <algorithm>

#define ALIVE true
#define DEAD false

Ruleset::Ruleset() {}

bool Ruleset::getOutcome(bool value, int neighbours) {
    if(value == ALIVE) {
        if(neighbours < 2 || neighbours > 3) {
            return DEAD;
        }
        else {
            return ALIVE;
        }
    } else {
        if(neighbours == 3) {
            return ALIVE;
        }
        else {
            return DEAD;
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
                if(field->getCellValue(i, j)) {
                    n++;
                }
            }
        }
    }

    return n;
}
