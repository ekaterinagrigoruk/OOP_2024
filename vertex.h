#pragma once

class Vertex final {
public:
    Vertex() = default;
    Vertex(int x, int y, double intensity) : x(x), y(y), intensity(intensity) {}
    [[nodiscard]] double get_intensity() const {
        return intensity;
    }
    [[nodiscard]] int get_x() const {
        return x;
    }
    [[nodiscard]] int get_y() const {
        return y;
    }
    bool operator==(const Vertex& vertex) const {
        return x == vertex.x && y == vertex.y;
    }
private:
    int x;
    int y;
    double intensity;
};
