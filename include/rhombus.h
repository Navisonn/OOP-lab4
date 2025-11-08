#pragma once


#include "figure.h"

template<Scalar T>
class Rhombus : public Figure<T> {
    T side;
    double angle;  

public:
    Rhombus(Point<T> c, T side, double angle_deg)
        : Figure<T>(c), side(side), angle(angle_deg * M_PI / 180.0) {
        generate_vertices();
    }
    void generate_vertices() {
        this->vertices.clear();
        Point<T> p1(this->center->x + side, this->center->y);
        for (int i = 0; i < 4; ++i) {
            double a = i * M_PI / 2.0;
            auto v = rotate(p1, *this->center, a + angle);
            this->vertices.push_back(std::make_unique<Point<T>>(v));
        }
    }


    double area() const override {
        return side * side * std::sin(angle);
    }
    void print(std::ostream& os) const override {
        os << "Rhombus[center=" << this->get_center()
           << ", side=" << side << ", angle=" << (angle * 180 / M_PI) << "°"
           << ", area=" << area() << "]";
    }
    T get_side() const { return side; }
    double get_angle() const { return angle; }
};
