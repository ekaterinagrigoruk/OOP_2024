#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "puqixml/pugixml.hpp"
#include "puqixml/pugiconfig.hpp"
#include "geo_point.h"

class ParserGPS final {
public:
    static std::vector<GeoPoint> parse(std::istream &stream);
private:
    static std::time_t str_to_time(const std::string& timeString);
};

class ParserErrors: public std::exception {
public:
    explicit ParserErrors(std::string  message): message{std::move(message)} {}
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};