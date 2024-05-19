#include "gps_track.h"
#include "histogram.h"

GPS_track::GPS_track(const std::vector<GeoPoint> &points, double accuracy) {
    geo_points = points;
    if (geo_points.empty()) {
        return;
    }

    start_time = geo_points.front().get_time();
    end_time = geo_points.back().get_time();
    min_height = geo_points.front().get_elevation();
    max_height = geo_points.front().get_elevation();

    GeoPoint prev_point = geo_points.front();
    bool isFirstPoint = true;

    for (const auto &point : geo_points) {
        if (point.get_elevation() < min_height) {
            min_height = point.get_elevation();
        }
        if (point.get_elevation() > max_height) {
            max_height = point.get_elevation();
        }

        if (!isFirstPoint) {
            double distance = point.distance(prev_point);
            all_distance += distance;

            auto dt = (double)(point.get_time() - prev_point.get_time());
            double speed;
            if ((dt - 0.1) > accuracy) {
                speed = distance / dt;
            } else {
                speed = 0;
            }
            if ((speed - max_speed) > accuracy){
                max_speed = speed;
            }
            if ((speed - 0.1) >= accuracy){
                speed_histogram.add_element(std::pair(dt, speed));
                movement_time += (time_t)dt;
            } else {
                stop_time += (time_t)dt;
            }
            if ((prev_point.get_elevation() - point.get_elevation()) > accuracy) {
                total_descent += prev_point.get_elevation() - point.get_elevation();
            } else {
                total_climb += point.get_elevation() - prev_point.get_elevation();
            }
        }

        prev_point = point;
        isFirstPoint = false;
    }
}

std::ostream& operator<<(std::ostream& os, const GPS_track& track){
    os << "Duration by time: " << track.get_duration() / 3600 << " hours "
       << (track.get_duration() % 3600) / 60 << " minutes "
       << track.get_duration() % 60 << " seconds\n";
    os << "All distance: " << track.get_all_distance() << " m\n";
    os << "Average speed in general: " << track.get_all_average_speed() * 3.6 << " km/h\n";
    os << "Movement time: " << track.get_movement_time() / 3600 << " hours "
       << (track.get_movement_time() % 3600) / 60 << " minutes "
       << track.get_movement_time() % 60 << " seconds\n";
    os << "Stop time: " << track.get_stop_time() / 3600 << " hours "
       << (track.get_stop_time() % 3600) / 60 << " minutes "
       << track.get_stop_time() % 60 << " seconds\n";
    os << "Average speed: " << track.get_average_speed() * 3.6 << " km/h\n";
    os << "Max speed: " << track.get_max_speed() * 3.6 << " km/h\n";
    os << "Min height: " << track.get_min_height() << " m\n";
    os << "Max height: " << track.get_max_height() << " m\n";
    os << "Total climb: " << track.get_total_climb() << " m\n";
    os << "Total descent: " << track.get_total_descent() << " m\n";

    os << "Speed histogram:\n";
    for (const auto& element : track.get_histogram()) {
        std::string range = element.first;
        int speed_seconds = static_cast<int>(element.second);
        os << range << " m/s : " << speed_seconds / 60 << " minutes "
           << speed_seconds % 60 << " seconds\n";
    }

    return os;
}
