#pragma once
#include <map>
#include "parser.h"
#include "geo_point.h"
#include "histogram.h"

class GPS_track final {
public:
    explicit GPS_track(const std::vector<GeoPoint>& points, double accuracy = 1e-7);
    [[nodiscard]] time_t get_duration() const {
        return (end_time - start_time);
    }
    [[nodiscard]] double get_all_distance() const {
        return all_distance;
    }
    [[nodiscard]] double get_all_average_speed() const {
        return (all_distance / (double)(end_time - start_time));
    }
    [[nodiscard]] time_t get_movement_time() const {
        return movement_time;
    }
    [[nodiscard]] time_t get_stop_time() const {
        return stop_time;
    }
    [[nodiscard]] double get_average_speed() const {
        return (all_distance / (double)(movement_time));
    }
    [[nodiscard]] double get_max_speed() const {
        return max_speed;
    }
    [[nodiscard]] double get_min_height() const {
        return min_height;
    }
    [[nodiscard]] double get_max_height() const {
        return max_height;
    }
    [[nodiscard]] double get_total_climb() const {
        return total_climb;
    }
    [[nodiscard]] double get_total_descent() const {
        return total_descent;
    }
    const Histogram& get_histogram() const {
        return speed_histogram;
    }

private:
    std::vector<GeoPoint> geo_points;
    Histogram speed_histogram;

    time_t start_time = 0, end_time = 0, movement_time = 0, stop_time = 0;
    double all_distance = 0;
    double max_speed = 0;
    double min_height = 0, max_height = 0;
    double total_climb = 0, total_descent = 0;

};

std::ostream& operator<<(std::ostream& os, const GPS_track& track);

