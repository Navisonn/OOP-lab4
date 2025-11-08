#include "../include/figure.h"
#include "../include/rhombus.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"

#include <iostream>

template<Scalar T>
std::shared_ptr<Figure<T>> input_figure() {
    std::cout << "Тип фигуры (1=Rhombus, 2=Pentagon, 3=Hexagon): ";
    int type;
    std::cin >> type;
    T cx, cy;
    std::cout << "Центр (x y): ";
    std::cin >> cx >> cy;
    Point<T> center(cx, cy);
    if (type == 1) {
        T side;
        double angle;
        std::cout << "Ромб: сторона, угол (градусы): ";
        std::cin >> side >> angle;
        return std::make_shared<Rhombus<T>>(center, side, angle);
    } else if (type == 2) {
        T r;
        std::cout << "Пятиугольник: радиус: ";
        std::cin >> r;
        return std::make_shared<Pentagon<T>>(center, r);
    } else if (type == 3) {
        T r;
        std::cout << "Шестиугольник: радиус: ";
        std::cin >> r;
        return std::make_shared<Hexagon<T>>(center, r);
    }
    return nullptr;
}

int main() {
    using T = int;
    Array<Figure<T>> figures;
    Array<Rhombus<T>> rhombuses;
    std::cout << "Ввод фигур\n";
    while (true) {
        auto fig = input_figure<T>();
        if (!fig) {
            break;
        }
        figures.push_back(fig);
        if (auto* rh = dynamic_cast<Rhombus<T>*>(fig.get())) {
            rhombuses.push_back(std::make_shared<Rhombus<T>>(*rh));
        }
    }
    std::cout << "\nВсе фигуры\n";
    for (size_t i = 0; i < figures.get_size(); ++i) {
        std::cout << "Фигура " << i << ":\n";
        print_figure(*figures[i]);
    }
    std::cout << "Общая площадь: " << total_area(figures) << "\n";
    if (figures.get_size() > 0) {
        figures.remove(0);
        std::cout << "Удалена фигура 0. Осталось: " << figures.get_size() << "\n";
    }
    std::vector<std::shared_ptr<Figure<T>>> temp;
    for (size_t i = 0; i < figures.get_size(); ++i) {
        temp.push_back(figures[i]);
    }
    std::sort(temp.begin(), temp.end(),
              [](const auto& a, const auto& b) { return *a < *b; });

    std::cout << "\n=== Отсортировано по площади ===\n";
    for (const auto& f : temp) {
        print_figure(*f);
    }
    std::cout << "\nRhombus int size: " << rhombuses.get_size() << "\n";
    return 0;
}
