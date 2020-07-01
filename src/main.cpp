#include <iostream>

#include "Game.h"

using namespace std;

int main(int argc, char *argv[]) {

	// initial board size and tickspeed are passed as console arguments
	// default values are 10 and 10 ticks/s
    if(argc > 1) {
		Game g(atoi(argv[1]), atoi(argv[2]));
	} else {
		Game g(10, 10);
	}
    return 0;
}
