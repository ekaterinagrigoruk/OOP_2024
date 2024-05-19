#include "geo_point.h"
#include "geo_constants.h"

double GeoPoint::distance(const GeoPoint& other) const {
    double lat1Rad = latitude * M_PI / 180.0;
    double lat2Rad = other.latitude * M_PI / 180.0;
    double lon1Rad = longitude * M_PI / 180.0;
    double lon2Rad = other.longitude * M_PI / 180.0;


    double deltaLat = lat2Rad - lat1Rad;
    double deltaLon = lon2Rad - lon1Rad;

    double a = pow(sin(deltaLat / 2), 2) + cos(lat1Rad) * cos(lat2Rad) * pow(sin(deltaLon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double horizontal_distance = GeoConstants::earth_radius * c;

    double delta_height = other.elevation - elevation;

    double distance = sqrt(pow(horizontal_distance, 2) + pow(delta_height, 2));
    return distance;
}


