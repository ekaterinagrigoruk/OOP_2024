#include <iostream>
#include <fstream>
#include "gps_track.h"


int main() {
    std::ifstream file("input.gpx");
    try {
        std::vector<GeoPoint> points = ParserGPS::parse(file);
        GPS_track example(points);

        std::ofstream result("output.txt");
        result << example;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
