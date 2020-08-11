#ifndef RULESET_H
#define RULESET_H

#include "gamefield.h"

class Ruleset {
public:
    Ruleset();

    static bool getOutcome(bool value, int neighbours);
    static int getNeighbourCount(int x, int y, GameField *field);
};

#endif // RULESET_H
