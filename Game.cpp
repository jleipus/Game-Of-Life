#include <iostream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <windows.h>

#include "Game.h"

using namespace std;

Game::Game() {

    init();
}

Game::~Game() {
    //dtor
}

void Game::init() {
    boardSize = 20;

    data.resize(boardSize);
	for(int i = 0; i < boardSize; ++i) {
		data[i].resize(boardSize);
	}

	neighbourData.resize(boardSize);
	for(int i = 0; i < boardSize; ++i) {
		neighbourData[i].resize(boardSize);
	}

	data = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
	{0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
	{0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
	{0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0},
	{0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
	{0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
	{0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

    loop();
}

void Game::loop() {
    draw();

    int frameCap = 100;

    while(1) {
        int frameStart = clock();
        system("cls");

        update();
        draw();

        int frameTime = frameStart - clock();
        if(frameTime < frameCap) {
            Sleep(frameCap - frameTime);
        }
    }
}

void Game::update() {
    calculateNeighbours();

    determineFuture();
}

void Game::draw() {
    cout << "\n\n";
    for(int i = 1; i < boardSize - 1; i++) {
        cout << "\t";
        for(int j = 1; j < boardSize - 1; j++) {
            if(data[i][j] == 1) {
                cout << "x";
            }
            else {
                cout << " ";
            }
        }
        cout << "\n";
    }
}

void Game::determineFuture() {
    for(int i = 1; i < boardSize - 1; i++) {
        for(int j = 1; j < boardSize - 1; j++) {
            if(data[i][j] == 1) {
                if(neighbourData[i][j] < 2 || neighbourData[i][j] > 3) {
                    data[i][j] = 0;
                }
            }
            else {
                if(neighbourData[i][j] == 3) {
                    data[i][j] = 1;
                }
            }
        }
    }
}

void Game::calculateNeighbours() {
    for(int i = 1; i < boardSize - 1; i++) {
        for(int j = 1; j < boardSize - 1; j++) {
            int neighbours = 0;
            if(data[i-1][j-1] == 1) { neighbours++; }
            if(data[i-1][j] == 1) { neighbours++; }
            if(data[i-1][j+1] == 1) { neighbours++; }

            if(data[i][j-1] == 1) { neighbours++; }
            if(data[i][j+1] == 1) { neighbours++; }

            if(data[i+1][j-1] == 1) { neighbours++; }
            if(data[i+1][j] == 1) { neighbours++; }
            if(data[i+1][j+1] == 1) { neighbours++; }

            neighbourData[i][j] = neighbours;
        }
    }
}

void Game::printNeighbours() {
    cout << "\n\n";
    for(int i = 0; i < boardSize; ++i) {
        cout << "\t";
        for(int j = 0; j < boardSize; ++j) {
            cout << setw(1) << neighbourData[i][j];
        }
        cout << "\n";
    }
}
