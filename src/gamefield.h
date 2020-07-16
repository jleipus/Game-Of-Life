#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <vector>
#include <QBitArray>

class GameField {
public:
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
    static const int DEAFULT_FIELD_SIZE = 100;

    int width, height;

    std::vector < std::vector < bool > > data;

};

#endif // GAMEFIELD_H
