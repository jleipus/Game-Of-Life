#include "testmethods.h"

#include "gamefield.h"
#include "ruleset.h"

#include <assert.h>
#include <iostream>

testMethods::testMethods() {}

void testMethods::runTests() {
    testResize();
    testGetOutcome();
    testGetNeighbourCount();
    testCopy();
}

void testMethods::testGetOutcome() {
    assert(getOutcome(1, 1) == 0); // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    assert(getOutcome(1, 2) == 1); // Any live cell with two or three live neighbours lives on to the next generation.
    assert(getOutcome(1, 4) == 0); // Any live cell with more than three live neighbours dies, as if by overpopulation.
    assert(getOutcome(0, 3) == 1); // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
}

void testMethods::testGetNeighbourCount() {
    GameField testField(3);
    testField.setCell(0, 1, 1);
    testField.setCell(1, 0, 1);
    testField.setCell(1, 1, 1);
    testField.setCell(2, 2, 1);
    assert(testField.getCell(0, 0) == 3);
}

void testMethods::testResize() {
    GameField testField;
    testField.resize(1, 2);
    assert(testField.getFieldWidth() == 1 && testField.getFieldHeight() == 2);
}

void testMethods::testCopy() {
    GameField test1(1);
    test1.setCell(0, 0, 1);
    GameField test2 = test1;
    assert(test2.getCell(0, 0) == 1);
}
