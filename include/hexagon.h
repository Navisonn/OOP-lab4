#pragma once

#include "figure.h"

template<Scalar T>
class Hexagon : public Figure<T> {
    T radius;
public:
    Hexagon(Point<T> c, T r) : Figure<T>(c), radius(r) {
        generate_vertices();
    }


    void generate_vertices() {
        this->vertices.clear();
        for (int i = 0; i < 6; ++i) {
            double angle = 2 * M_PI * i / 6.0;
            T x = this->center->x + radius * std::cos(angle);
            T y = this->center->y + radius * std::sin(angle);
            this->vertices.push_back(std::make_unique<Point<T>>(x, y));
        }
    }
    double area() const override {
        return 1.5 * std::sqrt(3) * radius * radius;
    }
    void print(std::ostream& os) const override {
        os << "Hexagon[center=" << this->get_center()
           << ", radius=" << radius << ", area=" << area() << "]";
    }
    T get_radius() const { return radius; }
};
