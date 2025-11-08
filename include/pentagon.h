#pragma once


#include "figure.h"

template<Scalar T>
class Pentagon : public Figure<T> {
    T radius;
public:
    Pentagon(Point<T> c, T r) : Figure<T>(c), radius(r) {
        generate_vertices();
    }
    void generate_vertices() {
        this->vertices.clear();
        for (int i = 0; i < 5; ++i) {
            double angle = 2 * M_PI * i / 5.0 - M_PI / 2.0;
            T x = this->center->x + radius * std::cos(angle);
            T y = this->center->y + radius * std::sin(angle);
            this->vertices.push_back(std::make_unique<Point<T>>(x, y));
        }
    }
    double area() const override {
        return 0.5 * 5 * radius * radius * std::sin(2 * M_PI / 5);
    }
    void print(std::ostream& os) const override {
        os << "Pentagon[center=" << this->get_center()
           << ", radius=" << radius << ", area=" << area() << "]";
    }
    T get_radius() const { return radius; }
};
