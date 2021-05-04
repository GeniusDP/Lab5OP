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

int main(int argc, char** argv){
    SetConsoleOutputCP(65001);
    PointOnMap center;
    double radius;
    vector<PointOnMap> items;
    Reader reader(argv[1]);
    cout << "Reading...";
    reader.readFromFile(items);
    system("cls");
    
    center.Lat = atof(argv[2]);
    center.Long = atof(argv[3]);
    radius = atof(argv[4]);
    string type, subtype;
    type = argv[5];
    subtype = argv[6];
    center.converse();

    cout << "Making a tree...";
    RTree tree(0., 0., 7000., 7000.);
    for (auto i : items) {
        tree.addPoint(tree.getRoot(), i);
    }
    system("cls");

    vector<PointOnMap> res;
    tree.findPointsInCircle(tree.getRoot(), center, radius, type, subtype, res);
    //tree.findPointsInRect(tree.getRoot(), { { 0, 0 }, { 7000, 7000 } }, type, subtype, res);
    
    cout << "Number of results found: " << res.size() << endl;
    for (auto r : res) {
        cout << r << endl;
    }
    return 0;
}