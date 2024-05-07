#include "gps_track.h"
#include "histogram.h"

GPS_track::GPS_track(std::vector<GeoPoint> &points) {
    if (points.empty()) {
        return;
    }

    start_time = points.front().get_time();
    end_time = points.back().get_time();
    min_height = points.front().get_elevation();
    max_height = points.front().get_elevation();

    GeoPoint prev_point = points.front();
    bool isFirstPoint = true;

    for (const auto &point : points) {
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
            if (dt > 0.1) {
                speed = distance / dt;
            } else {
                speed = 0;
            }
            if (speed > max_speed) {
                max_speed = speed;
            }
            if (speed >= 0.5) {
                speed_by_time.emplace_back(dt, speed);
                movement_time += (time_t)dt;
            } else {
                stop_time += (time_t)dt;
            }
            if (prev_point.get_elevation() > point.get_elevation()) {
                total_descent += prev_point.get_elevation() - point.get_elevation();
            } else {
                total_climb += point.get_elevation() - prev_point.get_elevation();
            }
        }

        prev_point = point;
        isFirstPoint = false;
    }
}


void GPS_track::print_track(std::ostream &stream) const {
    const time_t seconds_per_day = 86400;
    const time_t seconds_per_hour = 3600;
    const time_t seconds_per_minute = 60;
    const double to_km_h = 3.6;

    auto print_time = [&stream](time_t duration) {
        int days = static_cast<int>(duration / seconds_per_day);
        int hours = static_cast<int>((duration % seconds_per_day) / seconds_per_hour);
        int minutes = static_cast<int>((duration % seconds_per_hour) / seconds_per_minute);
        int seconds = static_cast<int>(duration % seconds_per_minute);
        stream << days << " days " << hours << " hours " << minutes << " minutes " << seconds << " seconds\n";
    };

    stream << "Duration by time: ";
    print_time(get_duration());

    stream << "All distance: " << get_all_distance() << " m\n";
    stream << "Average speed in general: " << get_all_average_speed() * to_km_h << " km/h\n";

    stream << "Movement time: ";
    print_time(get_movement_time());

    stream << "Stop time: ";
    print_time(get_stop_time());

    stream << "Average speed: " << get_average_speed() * to_km_h << " km/h\n";
    stream << "Max speed: " << get_max_speed() * to_km_h << " km/h\n";
    stream << "Min height: " << get_min_height() << " m\n";
    stream << "Max height: " << get_max_height() << " m\n";
    stream << "Total climb: " << get_total_climb() << " m\n";
    stream << "Total descent: " << get_total_descent() << " m\n";

    Histogram histogram (speed_by_time);
    stream << "Speed histogram:\n";
    for (const auto& range_and_time : histogram.get_histogram()) {
        std::string range = range_and_time.first;
        int speed_seconds = static_cast<int>(range_and_time.second);
        stream << range << " m/s : " << speed_seconds / seconds_per_minute << " minutes "
               << speed_seconds % seconds_per_minute << " seconds\n";
    }

}
