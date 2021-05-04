#pragma once
#include <cmath>
#include "PointOnMap.h"
using namespace std;


struct Rectangle {
    PointOnMap leftDown, rightUp;
};

bool intersectPointRectangle(PointOnMap point, Rectangle rect) {
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

bool intersectCircleRectangle(PointOnMap point, double R, Rectangle rect)
{
    double centerX = (rect.leftDown.x + rect.rightUp.x) / 2,
        centerY = (rect.leftDown.y + rect.rightUp.y) / 2,
        width = -rect.leftDown.x + rect.rightUp.x,
        height = -rect.leftDown.y + rect.rightUp.y;
    double dx = abs(point.x - centerX);
    double dy = abs(point.y - centerY);

    if (dx > width / 2 + R) { return false; }
    if (dy > height / 2 + R) { return false; }

    if (dx <= width / 2) { return true; }
    if (dy <= height / 2) { return true; }

    double cornerDistance = pow(dx - width / 2,  2) + pow(dy - height / 2, 2);

    return cornerDistance <= pow(R, 2);
}

bool intersectCirclePoint(PointOnMap center, double R, PointOnMap point) {
    return pow(center.x - point.x, 2) + pow(center.y - point.y, 2) <= pow(R, 2);
}