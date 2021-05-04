#pragma once
#include <string>

struct PointOnMap {
    double Lat, Long;
    double x, y;
    std::string type;
    std::string subType;
    std::string name;
    std::string address;
    void converse() {
        //converting into xOy coordinates
        x = 6371 * cos(Lat * 3.14159 / 180) * (Long * 3.14159 / 180);
        y = (Lat * 3.14159 / 180) * 6371;
    }
};
