#include "game.h"
#include "ruleset.h"

#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPainter>
#include <QTime>
#include <QLineEdit>

#include <iostream>
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

    widthEdit = new QLineEdit("50", this);
    heightEdit = new QLineEdit("50", this);
    QPushButton *changeSizeBtn = new QPushButton("Change size", this);

    this->resize(520, 560);
    this->setWindowTitle("Conways Game Of Life");
    this->show();

    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox1 = new QHBoxLayout(this);
    QHBoxLayout *hbox2 = new QHBoxLayout(this);

    vbox->addWidget(mainFrame);

    updateFrameMeasurements();

    hbox1->addWidget(speedLbl, 1, Qt::AlignCenter);
    hbox1->addWidget(plsBtnSpeed, 1);
    hbox1->addWidget(minBtnSpeed, 1);

    hbox2->addWidget(widthEdit, 1);
    hbox2->addWidget(heightEdit, 1);
    hbox2->addWidget(changeSizeBtn, 1);

    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);

    connect(plsBtnSpeed, &QPushButton::clicked, this, &Game::OnPlusSpeed);
    connect(minBtnSpeed, &QPushButton::clicked, this, &Game::OnMinusSpeed);
    connect(speedLbl, &QPushButton::clicked, this, &Game::Pause);

    connect(changeSizeBtn, &QPushButton::clicked, this, &Game::OnChangeSize);

    timerId = startTimer(1000 / speed);
}

void Game::draw() {
    drawPerimeter();

    drawUI();
    std::thread t(&Game::drawField, this);

    t.join();
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

void Game::drawPerimeter() {
    QPainter painter(this);
    painter.setBrush(QBrush("#acacac"));

    int topRightX = (field->getFieldWidth() + 1) * (CELL_SIZE + 1);
    int bottomLeftY = (field->getFieldHeight() + 1) * (CELL_SIZE + 1);

    if(topRightX < frameLeft + frameWidth) {
        painter.drawLine(topRightX, frameTop, topRightX, std::min(bottomLeftY, frameTop + frameHeight - 1));
    }

    if(bottomLeftY < frameTop + frameHeight) {
        painter.drawLine(frameLeft, bottomLeftY, std::min(topRightX, frameLeft + frameWidth - 1), bottomLeftY);
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

void Game::OnChangeSize() {
    int newWidth = widthEdit->text().toInt();
    int newHeight = heightEdit->text().toInt();

    if(newWidth > 0 && newWidth <= GameField::MAX_FIELD_SIZE) {
        if(newHeight > 0 && newHeight <= GameField::MAX_FIELD_SIZE) {
            field->resize(newWidth, newHeight);

            widthEdit->setText(QString::number(field->getFieldWidth()));
            heightEdit->setText(QString::number(field->getFieldHeight()));

            repaint();
        }
    }
}
