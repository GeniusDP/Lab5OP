#pragma once
#include <vector>
#include "Node.h"

using namespace std;

class RTree {
    Node* root;
    int height;

private:
    vector< Node* > divideNodeByFourParts(Rectangle rect) {
        Node* leftUp = new Node(), * rightUp = new Node(), * leftBottom = new Node(), * rightBottom = new Node;
        double x1 = rect.leftDown.x, y1 = rect.leftDown.y,
            x2 = rect.rightUp.x, y2 = rect.rightUp.y;
        double midX = (x1 + x2) / 2;
        double midY = (y1 + y2) / 2;
        leftUp->rect.leftDown = { x1, midY };
        leftUp->rect.rightUp = { midX, y2 };
        rightUp->rect.leftDown = { midX, midY };
        rightUp->rect.rightUp = { x2, y2 };
        leftBottom->rect.leftDown = { x1,y1 };
        leftBottom->rect.rightUp = { midX, midY };
        rightBottom->rect.leftDown = { midX, y1 };
        rightBottom->rect.rightUp = { x2, midY };
        vector< Node* > result = { leftUp, rightUp, leftBottom, rightBottom };
        return result;
    }

public:
    RTree(double x1, double y1, double x2, double y2) {
        root = new Node();
        root->rect.leftDown = { x1, y1 };
        root->rect.rightUp = { x2, y2 };
        height = 10;//hight of the tree
        buildTree(root);
    }
    Node* getRoot() {
        return root;
    }
    void buildTree(Node* node, int h = 1) {
        vector< Node* > children = divideNodeByFourParts(node->rect);
        for (int i = 0; i < children.size(); i++) {
            node->children.push_back(children[i]);
        }
        if (h < height) {
            for (int i = 0; i < node->children.size(); i++)
                buildTree(node->children[i], h + 1);
        }
    }
    void addPoint(Node* node, PointOnMap point, int h = 1) {
        if (!intersectPointRectangle(point, node->rect))
            return;
        if (h == height) {
            Node* newNode = new Node();
            newNode->point = point;
            node->children.push_back(newNode);
        }
        else {
            for (int i = 0; i < node->children.size(); i++)
                addPoint(node->children[i], point, h + 1);
        }
    }
    void removePoint(Node* node, PointOnMap point) {
        if (!intersectPointRectangle(point, node->rect))
            return;
        bool finded = false;
        for (int i = 0; i < node->children.size(); i++)
            if (node->children[i]->point.x != -1e9) {
                if (node->children[i]->point.x == point.x && node->children[i]->point.y == point.y) {
                    delete node->children[i];
                    node->children.erase(node->children.begin() + i);
                    finded = true;
                }
            }
        if (!finded) {
            for (int i = 0; i < node->children.size(); i++)
                removePoint(node->children[i], point);
        }
    }
    void findPointsInRect(Node* node, Rectangle rect, vector< PointOnMap >& result) {
        if (node->children.size() > 0) {
            if (intersectRectangles(node->rect, rect)) {
                for (int i = 0; i < node->children.size(); i++) {
                    findPointsInRect(node->children[i], rect, result);
                }
            }
        }
        else
            if (node->point.x != -1e9 && node->point.y != -1e9) {
                if (intersectPointRectangle(node->point, rect)) {
                    result.push_back(node->point);
                }
            }
    }
    void findPointsInCircle(Node* node, PointOnMap center, double R, vector< PointOnMap >& result) {
        if (node->children.size() > 0) {
            if (intersectCircleRectangle(center, R, node->rect)) {
                for (int i = 0; i < node->children.size(); i++) {
                    findPointsInCircle(node->children[i], center, R, result);
                }
            }
        }
        else
            if (node->point.x != -1e9 && node->point.y != -1e9) {
                if (intersectCirclePoint(center, R, node->point)) {
                    result.push_back(node->point);
                }
            }
    }

    /* ~RTree() {
         stack< Node* > _stack;
         _stack.push(root);
         while (!_stack.empty()) {
             Node* node = _stack.top();
             for (int i = 0; i < node->children.size(); i++)
                 _stack.push(node->children[i]);
             delete node;
             node = nullptr;
         }
     }*/
};
