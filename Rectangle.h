#pragma once

using namespace std;

struct Point {
    double x, y;
};

struct Rectangle {
    Point leftDown, rightUp;
};

bool intersectPointRectangle(Point point, Rectangle rect) {
    double x1 = rect.leftDown.x, y1 = rect.leftDown.y,
        x2 = rect.rightUp.x, y2 = rect.rightUp.y;
    if (point.x < x1 || point.x > x2 || point.y < y1 || point.y > y2)
        return false;
    return true;
}

bool intersectRectangles(Rectangle rect1, Rectangle rect2) {
    if ((rect1.leftDown.x <= rect2.rightUp.x || rect1.rightUp.x >= rect2.leftDown.x) &&
        (rect1.leftDown.y <= rect2.rightUp.y || rect1.rightUp.y >= rect2.leftDown.y))
        return true;
    return false;
}