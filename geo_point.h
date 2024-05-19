#pragma once
#include <cmath>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>

class GeoPoint final {
public:

    GeoPoint(double lat, double lng, double elev, time_t t)
            : latitude(lat), longitude(lng), elevation(elev), time(t) {}
    inline double get_latitude() const { return latitude; }
    inline double get_longitude() const { return longitude; }
    inline double get_elevation() const { return elevation; }
    inline time_t get_time() const { return time; }
    double distance(const GeoPoint &other) const;
private:
    double latitude;
    double longitude;
    double elevation;
    time_t time;
};
