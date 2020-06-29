#include <vector>

#ifndef GAME_H
#define GAME_H

using namespace std;

class Game
{
    public:
        Game();
        virtual ~Game();

    protected:

    private:
        int boardSize;

        vector < vector < int > > data;
        vector < vector < int > > neighbourData;

        void init();
        void loop();

        void update();
        void draw();

        void determineFuture();

        void calculateNeighbours();
        void printNeighbours();

};

#endif // GAME_H
