#pragma once
#include <string>

struct PointOnMap {
    double Lat, Long;
    double x, y;
    std::string type;
    std::string subType;
    std::string name;
    std::string adress;
    void converse() {
        x = 1;//formulas
        y = 1;
    }
};
