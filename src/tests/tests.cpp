#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../ruleset.h"
#include "../gamefield.h"

TEST_CASE("Outcome for cell is computed", "[getOutcome]") {
    REQUIRE(Ruleset::getOutcome(1, 1) == 0);
    REQUIRE(Ruleset::getOutcome(1, 2) == 1);
    REQUIRE(Ruleset::getOutcome(1, 4) == 0);
    REQUIRE(Ruleset::getOutcome(0, 3) == 1);
}

TEST_CASE("Neighbouring cells are counted", "[getNeighbourCount]") {
    GameField testField(3);
    testField.setCell(0, 1, 1);
    testField.setCell(1, 0, 1);
    testField.setCell(1, 1, 1);
    testField.setCell(2, 2, 1);
    REQUIRE(Ruleset::getNeighbourCount(0, 0, &testField) == 3);
}

TEST_CASE("Field is resized", "[resize]") {
    GameField testField;
    testField.resize(1, 2);
    REQUIRE((testField.getFieldWidth() == 1 && testField.getFieldHeight() == 2) == true);
}

TEST_CASE("Field object is copied", "[copy]") {
    GameField test1(1);
    test1.setCell(0, 0, 1);
    GameField test2 = test1;
    REQUIRE(test2.getCell(0, 0) == 1);
}
