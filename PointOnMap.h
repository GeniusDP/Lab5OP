#pragma once
#include <string>
#include <iostream>
using namespace std;
struct PointOnMap {
    double x, y;
    double Lat, Long;
    std::string type;
    std::string subType;
    std::string name;
    std::string address;
    void converse() {
        //converting into xOy coordinates
        x = 6371 * cos(Lat * 3.14159 / 180) * (Long * 3.14159 / 180);
        y = (Lat * 3.14159 / 180) * 6371;
    }
    friend ostream& operator<<(ostream& out, PointOnMap x){
        out << x.Lat << ";" << x.Long << ";" << x.type << ";" << x.subType << ";" << x.name << ";" << x.address << ";";
        return out;
    }
};
