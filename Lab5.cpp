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
    double squareLen;
    vector<PointOnMap> items;
    Reader reader("data.csv");
    reader.readFromFile(items);
    double result = -1e9;
    for (auto i : items) {
        result = max(result, max(i.x, i.y));
    }
    cout << result;

    /*cout << "Input centerLat, centerLong and squareLen: ";
    cin >> center.Lat >> center.Long >> squareLen;
    center.converse();
    RTree tree(0., 0., 50000., 50000.);*/


    return 0;
}