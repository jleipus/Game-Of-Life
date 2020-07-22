#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <vector>

class GameField {
public:
    static const int MAX_FIELD_SIZE = 500;
    static const int DEAFULT_FIELD_SIZE = 50;

    GameField();
    GameField(int _size);
    GameField(int _width, int _height);
    GameField(const GameField &f2);

    virtual ~GameField() {}

    int getCell(int x, int y) const;
    void setCell(int x, int y, int value);

    int getFieldWidth();
    int getFieldHeight();

    void resize(int _size);
    void resize(int _width, int _height);

    void copy(const GameField &f2);

    void changeCellValue(int x, int y);

    void clearField();
    void printField();

private:
    int width, height;

    std::vector < std::vector < bool > > data;

};

#endif // GAMEFIELD_H
