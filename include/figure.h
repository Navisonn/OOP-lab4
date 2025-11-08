#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <concepts>
#include <algorithm>
#include <iomanip>

template<typename T>
concept Scalar = std::is_scalar_v<T>;
template<Scalar T>
struct Point {
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}
    Point(const Point&) = default;\

    Point& operator=(const Point&) = default;
    Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
    Point& operator+=(const Point& p) { x += p.x; y += p.y; return *this; }
    double distance(const Point& p) const {
        double dx = x - p.x, dy = y - p.y;
        return std::hypot(dx, dy);
    }
    void print(std::ostream& os) const {
        os << '(' << x << ", " << y << ')';
    }
};
template<Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    p.print(os); 
    return os;
}
template<Scalar T>
class Figure {
protected:
    std::unique_ptr<Point<T>> center;
    std::vector<std::unique_ptr<Point<T>>> vertices;
public:
    Figure(Point<T> c) {
        center = std::make_unique<Point<T>>(c);
    }
    virtual ~Figure() = default;
    Figure(const Figure&) = delete;
    Figure& operator=(const Figure&) = delete;
    Figure(Figure&&) = default;
    Figure& operator=(Figure&&) = default;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
    const Point<T>& get_center() const { return *center; }
    const std::vector<std::unique_ptr<Point<T>>>& get_vertices() const { return vertices; }
    explicit operator double() const { return area(); }
    bool operator<(const Figure& other) const { return area() < other.area(); }
    bool operator==(const Figure& other) const { return std::abs(area() - other.area()) < 1e-9; }
};
template<Scalar T>
Point<T> rotate(const Point<T>& p, const Point<T>& center, double angle) {
    double s = std::sin(angle), c = std::cos(angle);
    T dx = p.x - center.x, dy = p.y - center.y;
    T rx = dx * c - dy * s;
    T ry = dx * s + dy * c;
    return {center.x + rx, center.y + ry};
}
template<class T>
class Array {
    std::unique_ptr<std::shared_ptr<T>[]> data;
    size_t size;
    size_t capacity;
    void ensure_capacity(size_t min_cap) {
        if (capacity >= min_cap) {
            return;
        }
        size_t new_cap = capacity ? capacity * 2 : 8;
        if (new_cap < min_cap) {
            new_cap = min_cap;
        }
        auto new_data = std::make_unique<std::shared_ptr<T>[]>(new_cap);
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        data = std::move(new_data);
        capacity = new_cap;
    }
public:
    Array() : size(0), capacity(0) {}
    void push_back(std::shared_ptr<T> item) {
        ensure_capacity(size + 1);
        data[size++] = std::move(item);
    }


    void remove(size_t index) {
        if (index >= size) {
            return;
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size;
    }
    std::shared_ptr<T>& operator[](size_t i) { return data[i]; }
    const std::shared_ptr<T>& operator[](size_t i) const { return data[i]; }
    size_t get_size() const { return size; }
    auto begin() { return data.get(); }
    auto end() { return data.get() + size; }

    auto begin() const { return data.get(); }
    auto end() const { return data.get() + size; }
};
template<Scalar T>
void print_figure(const Figure<T>& fig, std::ostream& os = std::cout) {
    os << "Center: " << fig.get_center() << "\n";
    os << "Vertices: ";
    for (const auto& v : fig.get_vertices()) {
        os << *v << " ";
    }
    os << "\nArea: " << std::fixed << std::setprecision(3) << (double)fig << "\n";
    fig.print(os);
    os << "\n\n";
}
template<Scalar T>
double total_area(const Array<Figure<T>>& arr) {
    double sum = 0.0;
    for (size_t i = 0; i < arr.get_size(); ++i) {
        sum += (double)*arr[i];
    }
    return sum;
}
