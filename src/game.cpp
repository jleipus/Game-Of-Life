#include "game.h"

#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QTime>

#include <iostream>
#include <cassert>
#include <thread>

Game::Game(QWidget *parent)
    : QWidget(parent) {

    initGame();
}

void Game::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);

    updateFrameMeasurements();
    draw();
}

void Game::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);

    update();
    repaint();
}

void Game::mousePressEvent(QMouseEvent *e) {
    Q_UNUSED(e);

    int newCellX = (this->mapFromGlobal(QCursor::pos()).x() - 11) / (CELL_SIZE + 1);
    int newCellY = (this->mapFromGlobal(QCursor::pos()).y() - 11) / (CELL_SIZE + 1);

    field->changeCellValue(newCellX, newCellY);

    repaint();
}

void Game::resizeEvent(QResizeEvent *e) {
    Q_UNUSED(e);

    updateFrameMeasurements();
}

void Game::initGame() {
    field = new GameField();

    mainFrame = new QFrame(this);
    mainFrame->setFrameStyle(QFrame::Box);

    QPushButton *plsBtn = new QPushButton("+", this);
    QPushButton *minBtn = new QPushButton("-", this);
    speedLbl = new QPushButton("Speed: 1 Cycles: 0", this);
    speedLbl->setFlat(true);

    this->resize(520, 560);
    this->setWindowTitle("Conways Game Of Life");
    this->show();

    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout(this);

    vbox->addWidget(mainFrame);
    hbox->addWidget(speedLbl, 1, Qt::AlignLeft);
    hbox->addWidget(plsBtn, 1);
    hbox->addWidget(minBtn, 1);

    vbox->addLayout(hbox);

    connect(plsBtn, &QPushButton::clicked, this, &Game::OnPlus);
    connect(minBtn, &QPushButton::clicked, this, &Game::OnMinus);
    connect(speedLbl, &QPushButton::clicked, this, &Game::Pause);

    updateFrameMeasurements();

    timerId = startTimer(1000 / speed);
}

void Game::draw() {
    drawField();
    drawUI();
}

void Game::update() {
    GameField nextField = *field;

    for(int i = 0; i < field->getFieldWidth(); i++) {
        for(int j = 0; j < field->getFieldHeight(); j++) {
            nextField.setCell(i, j, getOutcome(field->getCell(i, j), getNeighbourCount(i, j)));
        }
    }

    field->copy(nextField);
    cycles++;
}

void Game::drawField() {
    QPainter painter(this);
    painter.setBrush(QBrush("#4c4c4c"));

    for(int i = 0; i < field->getFieldWidth(); i++) {
        for(int j = 0; j < field->getFieldHeight(); j++) {
            if(field->getCell(i, j) == 1) {
                int cellPosX = frameLeft + i*(CELL_SIZE+1);
                int cellPosY = frameTop + j*(CELL_SIZE+1);

                if(isWithinFrame(cellPosX, cellPosY)) {
                    painter.drawRect(cellPosX, cellPosY, CELL_SIZE, CELL_SIZE);
                }
            }
        }
    }
}

void Game::drawUI() {
    if(!paused) {
        speedLbl->setText("Speed: " + QString::number(speed) + " Cycles: " + QString::number(cycles));
    } else {
        speedLbl->setText("Paused Cycles: " + QString::number(cycles));
    }
}

void Game::updateFrameMeasurements() {
    frameTop = mainFrame->geometry().top();
    frameLeft = mainFrame->geometry().left();
    frameWidth = mainFrame->geometry().width();
    frameHeight = mainFrame->geometry().height();
}

int Game::getOutcome(int value, int neighbours) {
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

int Game::getNeighbourCount(int x, int y) {
    int n = 0;

    for (int i = std::max(0, x - 1); i <= std::min(x + 1, field->getFieldWidth() - 1); i++) {
        for (int j = std::max(0, y - 1); j <= std::min(y + 1, field->getFieldHeight() - 1); j++) {
            if (i == x && j == y) {}
            else {
                n += field->getCell(i, j);
            }
        }
    }

    return n;
}

bool Game::isWithinFrame(int x, int y) { // returns the cell at (x,y) is within drawing frame
    if(x >= frameLeft && x + CELL_SIZE <= frameLeft + frameWidth) {
        if(y >= frameTop && y + CELL_SIZE <= frameTop + frameHeight) {
           return true;
        }
    }

    return false;
}

void Game::OnPlus() {
    if(!paused) {
        killTimer(timerId);
        speed++;
        timerId = startTimer(1000 / speed);
    } else {
        speed = 1;
        timerId = startTimer(1000 / speed);
        paused = false;
    }
}

void Game::OnMinus() {
    if(!paused) {
        killTimer(timerId);
        if(speed > 1) {
            speed--;
            timerId = startTimer(1000 / speed);
        } else {
            paused = true;
        }
    }
}

void Game::Pause() {
    if(!paused) {
        killTimer(timerId);
        paused = true;
    } else {
        timerId = startTimer(1000 / speed);
        paused = false;
    }
}

// UNIT TESTS

void Game::testGetOutcome() {
    assert(getOutcome(1, 1) == 0);
    assert(getOutcome(1, 2) == 1);
    assert(getOutcome(1, 4) == 0);
    assert(getOutcome(0, 3) == 1);
}

void Game::testGetNeighbourCount() {
    GameField testField(2);
    testField.setCell(0, 0, 1);
    testField.setCell(0, 1, 1);
    testField.setCell(1, 0, 1);
    assert(testField.getCell(1, 1) == 3);
}

void Game::testResize() {
    GameField testField;
    testField.resize(1, 2);
    assert(testField.getFieldWidth() == 1 && testField.getFieldHeight() == 2);
}

void Game::testCopy() {
    GameField test1(1);
    test1.setCell(0, 0, 1);
    GameField test2 = test1;
    assert(test2.getCell(0, 0) == 1);
}

void Game::testChangeCellValue() {
    GameField testField(1);
    testField.setCell(0, 0, 1);
    testField.changeCellValue(0, 0);
    assert(testField.getCell(0, 0) == 0);
}
