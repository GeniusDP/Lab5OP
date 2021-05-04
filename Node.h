#pragma once
#include <vector>
#include "Rectangle.h"

using namespace std;

struct Node {
    Rectangle rect;
    PointOnMap point;
    vector< Node* > children;
    Node() {
        rect.leftDown = { 0, 0 };
        rect.rightUp = { 0, 0 };
        point.x = -1e9;
        point.y = -1e9;
    }
};