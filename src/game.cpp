#include "game.h"
#include "ruleset.h"

#include <iostream>

Game::Game() {
    field = new GameField();
}

void Game::update() {
    for(int i = 0; i < field->getFieldWidth(); i++) {
        for(int j = 0; j < field->getFieldHeight(); j++) {
            field->setCellNeighbours(i, j, Ruleset::getNeighbourCount(i, j, field));
        }
    }

    for(int i = 0; i < field->getFieldWidth(); i++) {
        for(int j = 0; j < field->getFieldHeight(); j++) {
            field->setCellValue(i, j, Ruleset::getOutcome(field->getCellValue(i, j), field->getCellNeighbours(i, j)));
        }
    }

    cycles++;
}

void Game::draw() {

}

int Game::getSpeed() {
    return speed;
}

int Game::getCycles() {
    return cycles;
}

void Game::setSpeed(int s) {
    speed = s;
}

void Game::changeFieldSize(int newWidth, int newHeight) {
    if(newWidth > 0 && newWidth <= GameField::MAX_FIELD_SIZE) {
        if(newHeight > 0 && newHeight <= GameField::MAX_FIELD_SIZE) {
            field->resize(newWidth, newHeight);
        }
    }
}

void Game::changeClickedOnCell(int x, int y) {
    if(x >= 0 && x < field->getFieldWidth() && y >= 0 && y < field->getFieldHeight()) {
        field->setCellValue(x, y, !field->getCellValue(x, y));
    }
}

GameField* Game::getField() {
    return field;
}
