#include <iostream>
#include <vector>
#include <stack>
#include "RTree.h"

using namespace std;

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
        tree.findPointsInCircle(tree.getRoot(), { 5, 5 }, 5, result);
        cout << "Size: " << result.size() << endl;
        for (int i = 0; i < result.size(); i++)
            cout << result[i].x << " " << result[i].y << endl;
        
    }
    return 0;
}
