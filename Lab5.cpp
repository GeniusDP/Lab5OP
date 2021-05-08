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
#include <cmath>

using namespace std;


double dist(PointOnMap A, PointOnMap B) {
    return sqrt( pow(A.x - B.x, 2) + pow(A.y - B.y, 2) );
}


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
    system("cls");
    cout << "Adding points...";
    for (auto i : items) {
        tree.addPoint(tree.getRoot(), i);
    }
    system("cls");


    double currRadius = 1.;
    vector<PointOnMap> res;
    while ( currRadius <= (1<<13) ) {
        tree.findPointsInCircle(tree.getRoot(), center, currRadius, type, subtype, res);
        if (res.size() > 0)break;
        currRadius *= 2;
    }
    double minDist = 1e9;
    int pos = -1;
    for (int i = 0; i < res.size(); i++) {
        if ( dist(center, res[i]) < minDist) {
            minDist = dist(center, res[i]);
            pos = i;
        }
    }
    if (pos != -1) {
        cout << res[pos] << endl;
    }
    else {
        cout << "Not found!\n";
    }
    /*cout << "Number of results found: " << res.size() << endl;
    for (auto r : res) {
        cout << r << endl;
    }*/
    return 0;
}