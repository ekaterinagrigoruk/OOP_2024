#pragma once
#include <cmath>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>

class GeoPoint final {
public:

    GeoPoint(double lat = 0, double lng = 0, double elev = 0, time_t t = 0)
            : latitude(lat), longitude(lng), elevation(elev), time(t) {}
    [[nodiscard]] double get_latitude() const { return latitude; }
    [[nodiscard]] double get_longitude() const { return longitude; }
    [[nodiscard]] double get_elevation() const { return elevation; }
    [[nodiscard]] time_t get_time() const { return time; }
    [[nodiscard]] double distance(const GeoPoint &other) const;
    bool operator < (const GeoPoint& other) const {
        return time < other.time;
    }
private:
    double latitude;
    double longitude;
    double elevation;
    time_t time;
};
