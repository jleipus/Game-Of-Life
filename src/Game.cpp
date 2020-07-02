#include "game.h"

#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QTime>

#include <iostream>

Game::Game(QWidget *parent)
    : QWidget(parent){

    initGame();
}

void Game::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);

    draw();
}

void Game::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);

    update();
    repaint();
}

void Game::mousePressEvent(QMouseEvent *e) {
    Q_UNUSED(e);

    int newCellX = this->mapFromGlobal(QCursor::pos()).x() / (CELL_SIZE + 1);
    int newCellY = this->mapFromGlobal(QCursor::pos()).y() / (CELL_SIZE + 1);

    if(newCellX <= SIZE && newCellY <= SIZE) {
        if(data[newCellX][newCellY] == 1) {
            data[newCellX][newCellY] = 0;
        } else if(data[newCellX][newCellY] == 0) {
            data[newCellX][newCellY] = 1;
        }
    }

    repaint();
}


void Game::initGame() {
    QFrame *mainFrame = new QFrame(this);
    mainFrame->setFrameStyle(QFrame::Box);

    fieldTop = mainFrame->geometry().top();
    fieldLeft = mainFrame->geometry().left();
    fieldWidth = mainFrame->geometry().width();
    fieldHeight = mainFrame->geometry().height();

    QPushButton *plsBtn = new QPushButton("+", this);
    QPushButton *minBtn = new QPushButton("-", this);
    speedLbl = new QPushButton("Speed: 1 Cycles: 0", this);
    speedLbl->setFlat(true);

    this->resize(520, 560);
    this->move(300, 300);
    this->setWindowTitle("Conways Game Of Life");
    this->setToolTip("C++ based project using Qt5.");
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

    data[1][3] = 1;
    data[2][3] = 1;
    data[3][3] = 1;
    data[3][2] = 1;
    data[2][1] = 1;

    timerId = startTimer(1000 / speed);
}

void Game::draw() {
    QPainter qp(this);
    qp.setBrush(QBrush("#4c4c4c"));

    for(int i = 1; i < SIZE + 1; i++) {
        for(int j = 1; j < SIZE + 1; j++) {
            if(data[i][j] == 1) {
                int cellPosX = fieldLeft + i*(CELL_SIZE+1);
                int cellPosY = fieldTop + j*(CELL_SIZE+1);

                //if(cellPosX >= fieldLeft && cellPosX <= fieldLeft + fieldWidth) {
                    //if(cellPosY >= fieldTop && cellPosY <= fieldTop + fieldHeight) {
                       qp.drawRect(cellPosX, cellPosY, CELL_SIZE, CELL_SIZE);
                    //}
                //}
            }
        }
    }

    if(!paused) {
        speedLbl->setText("Speed: " + QString::number(speed) + " Cycles: " + QString::number(cycles));
    } else {
        speedLbl->setText("Paused Cycles: " + QString::number(cycles));
    }
}

void Game::update() {
    nextData = data;

    for(int i = 1; i < SIZE + 1; i++) {
        for(int j = 1; j < SIZE + 1; j++) {
            int neighbours = 0;

            // total number of "live" neighbouring cells is counted
            if(data[i-1][j-1] == 1) { neighbours++; }
            if(data[i-1][j] == 1) { neighbours++; }
            if(data[i-1][j+1] == 1) { neighbours++; }

            if(data[i][j-1] == 1) { neighbours++; }
            if(data[i][j+1] == 1) { neighbours++; }

            if(data[i+1][j-1] == 1) { neighbours++; }
            if(data[i+1][j] == 1) { neighbours++; }
            if(data[i+1][j+1] == 1) { neighbours++; }

            // checking conditions for death and "birth"
            if(data[i][j] == 1) {
                if(neighbours < 2 || neighbours > 3) {
                    nextData[i][j] = 0;
                }
            } else {
                if(neighbours == 3) {
                    nextData[i][j] = 1;
                }
            }
        }
    }

    data = nextData;
    cycles++;
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
