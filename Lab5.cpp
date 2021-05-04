#include <iostream>
#include <string>
#include "PointOnMap.h"
#include "Reader.h"
#include <vector>
#include "RTree.h"
#include "Rectangle.h"
#include "RTree.h"
#include <cmath>
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(65001);
    PointOnMap center;
    double radius;
    vector<PointOnMap> items;
    Reader reader("data1.csv");
    reader.readFromFile(items);

    cout << "Input centerLat, centerLong and radius: ";
    cin >> center.Lat >> center.Long >> radius;
    string type, subtype;
    cout << "Input type of object: ";
    cin.ignore();
    getline(cin, type);
    cout << "Input subtype of object: ";
    getline(cin, subtype);
    if (subtype == "ar")
        subtype = "car";
    center.converse();
    RTree tree(0., 0., 7000., 7000.);
    for (auto i : items) {
        tree.addPoint(tree.getRoot(), i);
    }
    vector<PointOnMap> res;
    tree.findPointsInCircle(tree.getRoot(), center, radius, type, subtype, res);
    //tree.findPointsInRect(tree.getRoot(), { { 0, 0 }, { 7000, 7000 } }, type, subtype, res);
    cout << "Number of results found: " << res.size() << endl;
    for (auto r : res) {
        cout << r << endl;
    }
    return 0;
}