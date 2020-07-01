#include <iostream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <windows.h>

#include "Game.h"

using namespace std;

Game::Game(int _boardSize, int _tickspeed) {
	boardSize = _boardSize + 2; // two extra rows and columns are added at the edges to simplify calculation
	tickspeed = _tickspeed;
	
    	init();
}

Game::~Game() {
    	//dtor
}

void Game::init() {
	// initialization of both arrays to specified size
    	data.resize(boardSize);
	for(int i = 0; i < boardSize; ++i) {
		data[i].resize(boardSize);
	}

	nextData.resize(boardSize);
	for(int i = 0; i < boardSize; ++i) {
		nextData[i].resize(boardSize);
	}

	data = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	nextData = data;

    	loop();
}

void Game::loop() {
	// tickspeed is provided in ticks/s, so frameCap 1000ms 
	// divided by tickspeed giving the minimum time for each frame
    	int frameCap = 1000 / tickspeed; 

    	while(1) {
		int frameStart = clock();
        	system("cls"); // only works on Windows

		draw();
        	update();
        
        	int frameTime = frameStart - clock();
        	if(frameTime < frameCap) {
           		 Sleep(frameCap - frameTime);
        	}
    	}
}

void Game::draw() {
	for(int i = 1; i < boardSize - 1; i++) {
        	for(int j = 1; j < boardSize - 1; j++) {
            		if(data[i][j] == 1) {
		 		cout << "x";
			} else {
                		cout << " ";
            		}
        	}
        	cout << "\n";
    	}
}

void Game::update() {
	nextData = data;
	
    	for(int i = 1; i < boardSize - 1; i++) {
        	for(int j = 1; j < boardSize - 1; j++) {
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
}

