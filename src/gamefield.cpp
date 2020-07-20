#include "gamefield.h"

#include <iostream>

GameField::GameField()
    : GameField(DEAFULT_FIELD_SIZE) {

}

GameField::GameField(int _size)
    : GameField(_size, _size) {
}

GameField::GameField(int _width, int _height) {
    width = _width;
    height = _height;

    data.resize(width);
    for(int i = 0; i < width; i++) {
        data[i].resize(height);
        std::fill(data[i].begin(), data[i].end(), 0);
    }
}

GameField::GameField(const GameField &f2) {
    width = f2.width;
    height = f2.height;
    data = f2.data;
}

int GameField::getCell(int x, int y) const {
    return data[x][y];
}

void GameField::setCell(int x, int y, int value) {
    data[x][y] = value;
}

int GameField::getFieldWidth() {
    return width;
}

int GameField::getFieldHeight() {
    return height;
}

void GameField::resize(int _size) {
    resize(_size, _size);
}

void GameField::resize(int _width, int _height) {
    width = _width;
    height = _height;

    data.resize(width);
    for(int i = 0; i < width; i++) {
        data[i].resize(height);
    }
}

void GameField::copy(const GameField &f2) {
    width = f2.width;
    height = f2.height;
    this->resize(width, height);

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            this->setCell(i, j, f2.getCell(i, j));
        }
    }
}

void GameField::changeCellValue(int x, int y) {
    if(x >= 0 && x < this->getFieldWidth() && y >= 0 && y < this->getFieldHeight()) {
        if(this->getCell(x, y) == 1) {
            this->setCell(x, y, 0);
        } else if(this->getCell(x, y) == 0) {
            this->setCell(x, y, 1);
        }
    }
}

void GameField::clearField() {
    for(int i = 0; i < width; i++) {
        std::fill(data[i].begin(), data[i].end(), 0);
    }
}

void GameField::printField() {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// UNIT TESTS


