#include <iostream>
#include <string>
#include "PointOnMap.h"
#include "Reader.h"
#include <vector>

using namespace std;

int main()
{
    PointOnMap center;
    double squareLen;
    vector<PointOnMap> items;
    Reader reader("data.csv");
    reader.readFromFile(items);
    
    cout << "Input centerLat, centerLong and squareLen: ";
    cin >> center.Lat >> center.Long >> squareLen;
    center.converse();
    return 0;
}
