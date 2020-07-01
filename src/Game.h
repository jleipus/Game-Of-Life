#include <vector>

#ifndef GAME_H
#define GAME_H

using namespace std;

class Game
{
    public:
        Game(int _boardSize, int _tickspeed);
        virtual ~Game();
		
    private:
        int boardSize;
		int tickspeed;

        vector < vector < int > > data; // need to replace with more memmory efficient and faster option
        vector < vector < int > > nextData;

        void init();
        void loop();

        void draw();
        void update();

};

#endif // GAME_H
