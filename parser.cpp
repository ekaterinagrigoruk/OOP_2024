#include "parser.h"

std::vector<GeoPoint> ParserGPS::parse(std::istream &stream) {
    pugi::xml_document document;
    if (!document.load(stream)) {
        throw ParserErrors("Stream error");
    }
    std::vector<GeoPoint> points;
    pugi::xml_node tools = document.child("gpx").child("trk").child("trkseg");
    for (pugi::xml_node trkpt : tools.children("trkpt")) {
        double lat = trkpt.attribute("lat").as_double();
        double lon = trkpt.attribute("lon").as_double();
        double ele = trkpt.child("ele").text().as_double();
        std::string time = trkpt.child_value("time");
        points.emplace_back(lat, lon, ele, str_to_time(time));
    }
    return points;
}

std::time_t ParserGPS::str_to_time(const std::string& timeString) {
    std::tm dt = {};
    std::istringstream ss(timeString);
    ss >> std::get_time(&dt, "%Y-%m-%dT%H:%M:%S");
    if (ss.fail()) {
        throw ParserErrors("Data error");
    }
    std::time_t time = std::mktime(&dt);
    return time;
}