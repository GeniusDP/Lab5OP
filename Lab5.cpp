#include <iostream>
#include <string>
#include "PointOnMap.h"
#include "Reader.h"
#include <vector>
#include "RTree.h"
#include "Rectangle.h"
#include "RTree.h"
#include <cmath>

using namespace std;



int main()
{
    PointOnMap center;
    double radius;
    vector<PointOnMap> items;
    Reader reader("data1.csv");
    reader.readFromFile(items);
    double result = -1e9;
    /*for (auto i : items) {
        result = max(result, max(i.x, i.y));
    }
    cout << result;*/

    cout << "Input centerLat, centerLong and radius: ";
    cin >> center.Lat >> center.Long >> radius;
    cout << radius << endl;
    center.converse();
    cout << center.x << " " << center.y << "\n";
    cout << "************************\n";
    RTree tree(0., 0., 7000., 7000.);
    for (auto i : items) {
        tree.addPoint(tree.getRoot(), i);
        cout << i.x << " " << i.y << "\n";
    }
    cout << "************************\n";
    vector<PointOnMap> res;
    tree.findPointsInRect(tree.getRoot(), { {0, 0}, {7000, 7000} }, res);
    for (auto r : res) {
        cout << r;
    }
    return 0;
}