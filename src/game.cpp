#include "game.h"
#include "ruleset.h"
#include "testmethods.h"

#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPainter>
#include <QTime>
#include <iostream>
#include <thread>

Game::Game(QWidget *parent)
    : QWidget(parent) {

    testMethods::runTests();

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

    int newCellX = (this->mapFromGlobal(QCursor::pos()).x()) / (CELL_SIZE + 1) - 1;
    int newCellY = (this->mapFromGlobal(QCursor::pos()).y()) / (CELL_SIZE + 1) - 1;

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

    QPushButton *plsBtnSpeed = new QPushButton("+", this);
    QPushButton *minBtnSpeed = new QPushButton("-", this);
    speedLbl = new QPushButton("Speed: 1 Cycles: 0", this);
    speedLbl->setFlat(true);

    QPushButton *plsBtnSize = new QPushButton("+", this);
    QPushButton *minBtnSize = new QPushButton("-", this);
    sizeLbl = new QLabel(" Size: 50x50", this);

    this->resize(520, 560);
    this->setWindowTitle("Conways Game Of Life");
    this->show();

    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox1 = new QHBoxLayout(this);
    QHBoxLayout *hbox2 = new QHBoxLayout(this);

    vbox->addWidget(mainFrame);

    hbox1->addWidget(speedLbl, 1, Qt::AlignCenter);
    hbox1->addWidget(plsBtnSpeed, 1);
    hbox1->addWidget(minBtnSpeed, 1);

    hbox2->addWidget(sizeLbl, 1, Qt::AlignCenter);
    hbox2->addWidget(plsBtnSize, 1);
    hbox2->addWidget(minBtnSize, 1);

    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);

    connect(plsBtnSpeed, &QPushButton::clicked, this, &Game::OnPlusSpeed);
    connect(minBtnSpeed, &QPushButton::clicked, this, &Game::OnMinusSpeed);
    connect(speedLbl, &QPushButton::clicked, this, &Game::Pause);

    connect(plsBtnSize, &QPushButton::clicked, this, &Game::OnPlusSize);
    connect(minBtnSize, &QPushButton::clicked, this, &Game::OnMinusSize);

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
            nextField.setCell(i, j, Ruleset::getOutcome(field->getCell(i, j), Ruleset::getNeighbourCount(i, j, field)));
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

    sizeLbl->setText("Size: " + QString::number(field->getFieldWidth()) + "x" + QString::number(field->getFieldHeight()));
}

void Game::updateFrameMeasurements() {
    frameTop = mainFrame->geometry().top();
    frameLeft = mainFrame->geometry().left();
    frameWidth = mainFrame->geometry().width();
    frameHeight = mainFrame->geometry().height();
}

bool Game::isWithinFrame(int x, int y) { // returns the cell at (x,y) is within drawing frame
    if(x >= frameLeft && x + CELL_SIZE <= frameLeft + frameWidth) {
        if(y >= frameTop && y + CELL_SIZE <= frameTop + frameHeight) {
           return true;
        }
    }

    return false;
}

void Game::OnPlusSpeed() {
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

void Game::OnMinusSpeed() {
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

void Game::OnPlusSize() {
    int size = field->getFieldWidth();

    if(size < GameField::MAX_FIELD_SIZE) {
        size += 1;
        field->resize(size);
        repaint();
    }
}

void Game::OnMinusSize() {
    int size = field->getFieldWidth();

    if(size > 1) {
        size -= 1;
        field->resize(size);
        repaint();
    }
}
