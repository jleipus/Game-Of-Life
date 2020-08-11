#include "cell.h"
#include "ui.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QPainter>

#include <iostream>

UI::UI(QWidget *parent, Game *game)
    : QWidget(parent), game(game) {

    initUi();
}

void UI::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);

    draw();
}

void UI::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);

    update();
    repaint();
}

void UI::mousePressEvent(QMouseEvent *e) {
    Q_UNUSED(e);

    int newCellX = (this->mapFromGlobal(QCursor::pos()).x() - frameLeft) / (Cell::CELL_SIZE + 1);
    int newCellY = (this->mapFromGlobal(QCursor::pos()).y() - frameTop) / (Cell::CELL_SIZE + 1);

    game->changeClickedOnCell(newCellX, newCellY);

    repaint();
}

void UI::resizeEvent(QResizeEvent *e) {
    Q_UNUSED(e);

    updateFrameMeasurements();
}

void UI::initUi() {
    this->resize(520, 560);
    this->setWindowIcon(QIcon(":/icon.png"));
    this->setWindowTitle("Conways Game Of Life");

    QVBoxLayout *vbox = new QVBoxLayout(this);      // main vertical layout
    QHBoxLayout *hbox1 = new QHBoxLayout(this);     // horizontal layout for speed adjustment elements
    QHBoxLayout *hbox2 = new QHBoxLayout(this);     // horizontal layout for size adjustment elements

    mainFrame = new QFrame(this);           // frame where cells are displayed
    mainFrame->setFrameStyle(QFrame::Box);  // gives frame a solid black border

    QPushButton *plsBtnSpeed = new QPushButton("+", this);
    QPushButton *minBtnSpeed = new QPushButton("-", this);
    speedAndCycleLbl = new QPushButton("Speed: " + QString::number(game->getSpeed()) + " Cycles: " + QString::number(game->getCycles()), this);
    speedAndCycleLbl->setFlat(true);                        // disguises button as a label

    widthEdit = new QLineEdit(QString::number(GameField::DEFAULT_FIELD_SIZE), this);    // text field for new width
    heightEdit = new QLineEdit(QString::number(GameField::DEFAULT_FIELD_SIZE), this);   // text field for new height
    QPushButton *changeSizeBtn = new QPushButton("Change size", this);

    // adding all elements to layouts
    vbox->addWidget(mainFrame);

    hbox1->addWidget(speedAndCycleLbl, 1, Qt::AlignCenter);
    hbox1->addWidget(plsBtnSpeed, 1);
    hbox1->addWidget(minBtnSpeed, 1);

    hbox2->addWidget(widthEdit, 1);
    hbox2->addWidget(heightEdit, 1);
    hbox2->addWidget(changeSizeBtn, 1);

    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);

    // connecting buttons to appropriate slots
    connect(plsBtnSpeed, &QPushButton::clicked, this, &UI::OnPlusSpeed);
    connect(minBtnSpeed, &QPushButton::clicked, this, &UI::OnMinusSpeed);
    connect(speedAndCycleLbl, &QPushButton::clicked, this, &UI::Pause);

    connect(changeSizeBtn, &QPushButton::clicked, this, &UI::OnChangeSize);

    updateFrameMeasurements(); // updates coordinates and measurements of mainFrame

    this->show();

    timerId = startTimer(1000 / game->getSpeed());
}

void UI::updateFrameMeasurements() {
    frameTop = mainFrame->geometry().top();
    frameLeft = mainFrame->geometry().left();
    frameWidth = mainFrame->geometry().width();
    frameHeight = mainFrame->geometry().height();
}

void UI::update() {
    game->update();
}

void UI::draw() {
    drawUI();
    drawField();
}

void UI::drawUI() {
    // dispalys speed if game is not paused and number of cycles
    if(!paused) {
        speedAndCycleLbl->setText("Speed: " + QString::number(game->getSpeed()) + " Cycles: " + QString::number(game->getCycles()));
    } else {
        speedAndCycleLbl->setText("Paused Cycles: " + QString::number(game->getCycles()));
    }
}

void UI::drawField() {
    QPainter painter(this); // allows for drawing
    painter.setBrush(QBrush("#4c4c4c"));

    int right = game->getField()->getRectangle().width + frameLeft; // loaction of field border with frame offset accounted for
    int bottom = game->getField()->getRectangle().height + frameTop;

    if(right < frameLeft + frameWidth) {
        painter.drawLine(right, frameTop, right, std::min(bottom, frameTop + frameHeight - 1));
    }

    if(bottom < frameTop + frameHeight) {
        painter.drawLine(frameLeft, bottom, std::min(right, frameLeft + frameWidth - 1), bottom);
    }

    for(int i = 0; i < game->getField()->getFieldWidth(); i++) {
        for(int j = 0; j < game->getField()->getFieldHeight(); j++) { // for every cell
            if(game->getField()->cellShouldBeDrawn(i, j, frameLeft + frameWidth, frameTop + frameHeight)) {
                Rectangle rect = game->getField()->getCellRectangle(i, j);
                painter.drawRect(rect.left + frameLeft, rect.top + frameTop, rect.width, rect.height);
            }
        }
    }
}

void UI::OnPlusSpeed() {
    int speed = game->getSpeed();
    if(!paused) {
        killTimer(timerId);
        speed++;
        timerId = startTimer(1000 / speed);
    } else {
        speed = 1;
        timerId = startTimer(1000 / speed);
        paused = false;
    }
    game->setSpeed(speed);
}

void UI::OnMinusSpeed() {
    int speed = game->getSpeed();
    if(!paused) {
        killTimer(timerId);
        if(speed > 1) {
            speed--;
            timerId = startTimer(1000 / speed);
        } else {
            paused = true;
        }
    }
    game->setSpeed(speed);
}

void UI::Pause() {
    int speed = game->getSpeed();
    if(!paused) {
        killTimer(timerId);
        paused = true;
    } else {
        timerId = startTimer(1000 / speed);
        paused = false;
    }
}

void UI::OnChangeSize() {
    int newWidth = widthEdit->text().toInt();
    int newHeight = heightEdit->text().toInt();

    game->changeFieldSize(newWidth, newHeight);

    widthEdit->setText(QString::number(game->getField()->getFieldWidth()));
    heightEdit->setText(QString::number(game->getField()->getFieldHeight()));

    repaint();
}
