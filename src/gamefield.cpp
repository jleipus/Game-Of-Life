#include "gamefield.h"

#include <iostream>

#define ALIVE true
#define DEAD false

GameField::GameField() {
    resize(DEFAULT_FIELD_SIZE, DEFAULT_FIELD_SIZE);
}

bool GameField::getCellValue(int x, int y) const {
    return data[x][y]->getValue();
}

void GameField::setCellValue(int x, int y, bool val) {
    data[x][y]->setValue(val);
}

int GameField::getCellNeighbours(int x, int y) {
    return data[x][y]->getNeighbours();
}

void GameField::setCellNeighbours(int x, int y, int n) {
    data[x][y]->setNeighbours(n);
}

int GameField::getFieldWidth() {
    return width;
}

int GameField::getFieldHeight() {
    return height;
}

Rectangle GameField::getRectangle() {
    return Rectangle(left, right, top, bottom, right - left, bottom - top);
}

Rectangle GameField::getCellRectangle(int x, int y) {
    return data[x][y]->getRectangle();
}

bool GameField::cellShouldBeDrawn(int x, int y, int frameRight, int frameBottom) {
    Rectangle rect = data[x][y]->getRectangle();

    if(rect.left >= left && rect.right <= frameRight) {
        if(rect.top >= top && rect.bottom <= frameBottom) {
           if(data[x][y]->getValue() == 1) {
                return true;
           }
        }
    }

    return false;
}

void GameField::resize(int newWidth, int newHeight) {
    if(newWidth <= MAX_FIELD_SIZE && newHeight <= MAX_FIELD_SIZE) {
		data.resize(newWidth);
		for(int i = 0; i < newWidth; i++) {
			if(i < width) {
				if(height < newHeight) {
					for(int j = height; j < newHeight; j++) {
						data[i].push_back(new Cell(i, j, DEAD));
					}
				} else {
					data[i].resize(newHeight);
				}
			} else {
				for(int j = 0; j < newHeight; j++) {
					data[i].push_back(new Cell(i, j, DEAD));
				}
			}
		}

		width = newWidth;
		height = newHeight;

		left = 0;
		right = width * (Cell::CELL_SIZE + 1) + left - 1;
		top = 0;
		bottom = height * (Cell::CELL_SIZE + 1) + top - 1;
	}
}

void GameField::printField() {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(getCellValue(i, j)) {
                std::cout << 1;
            } else {
                std::cout << 0;
            }
        }
        std::cout << std::endl;
    }
}
