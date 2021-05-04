#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Point {
    double x, y;
};

struct Rectangle {
    Point leftDown, rightUp;
};

struct Node {
    Rectangle rect;
    Point point;
    vector< Node* > children;
    Node() {
        rect.leftDown = { 0, 0 };
        rect.rightUp = { 0, 0 };
        point.x = -1e9;
        point.y = -1e9;
    }
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
        height = 3;
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
    void addPoint(Node* node, Point point, int h = 1) {
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
    void removePoint(Node* node, Point point) {
        if (!intersectPointRectangle(point, node->rect))
            return;
        bool finded = false;
        for (int i = 0 ; i < node->children.size(); i++)
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
    void findPointsInRect(Node* node, Rectangle rect, vector< Point >& result, int h = 1) {
        if (node->children.size() > 0) {
            if (intersectRectangles(node->rect, rect)) {
                for (int i = 0; i < node->children.size(); i++) {
                    findPointsInRect(node->children[i], rect, result, h + 1);
                }
            }
        }
        else 
        if (node->point.x != -1e9 && node->point.y != -1e9){
            if (intersectPointRectangle(node->point, rect)){
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

int main()
{
    RTree tree(0, 0, 15, 15);
    int N;
    cin >> N; 
    for (int i = 0; i < N; i++) {
        double x, y;
        cin >> x >> y;
        tree.addPoint(tree.getRoot(), { x, y });
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        double x1, y1;
        cin >> x1 >> y1;
        tree.removePoint(tree.getRoot(), { x1, y1 });
        vector< Point > result;
        Rectangle rect = { { 2, 2 }, { 8, 8 } };
        tree.findPointsInRect(tree.getRoot(), rect, result);
        cout << "Size: " << result.size() << endl;
        for (int i = 0; i < result.size(); i++)
            cout << result[i].x << " " << result[i].y << endl;
        
    }
    
    return 0;
}
