#ifndef RECTANGLE_H
#define RECTANGLE_H


class Rectangle {
public:
    Rectangle(int left, int right, int top, int bottom, int width, int height)
        : left(left), right(right), top(top), bottom(bottom), width(width), height(height) {}
    virtual ~Rectangle() {}

    int left;
    int right;
    int top;
    int bottom;
    int width;
    int height;
};

#endif // RECTANGLE_H
