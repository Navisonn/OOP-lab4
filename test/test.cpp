#include <gtest/gtest.h>
#include "../include/figure.h"
#include "../include/rhombus.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"

TEST(PointTest, BasicOperations) {
    Point<int> p1(1, 2);
    Point<int> p2(3, 4);
    
    auto p3 = p1 + p2;
    EXPECT_EQ(p3.x, 4);
    EXPECT_EQ(p3.y, 6);
    
    auto p4 = p2 - p1;
    EXPECT_EQ(p4.x, 2);
    EXPECT_EQ(p4.y, 2);
    
    EXPECT_NEAR(p1.distance(p2), std::sqrt(8), 1e-9);
}


TEST(RhombusTest, AreaCalculation) {
    Rhombus<int> rh(Point<int>(0, 0), 5, 90.0);
    EXPECT_NEAR(rh.area(), 25.0, 1e-9);
}
TEST(RhombusTest, VerticesCount) {
    Rhombus<int> rh(Point<int>(0, 0), 5, 45.0);
    EXPECT_EQ(rh.get_vertices().size(), 4);
}


TEST(PentagonTest, AreaCalculation) {
    Pentagon<int> pent(Point<int>(0, 0), 1);
    double expected_area = 0.5 * 5 * 1 * 1 * std::sin(2 * M_PI / 5);
    EXPECT_NEAR(pent.area(), expected_area, 1e-9);
}
TEST(PentagonTest, VerticesCount) {
    Pentagon<int> pent(Point<int>(0, 0), 5);
    EXPECT_EQ(pent.get_vertices().size(), 5);
}


TEST(HexagonTest, AreaCalculation) {
    Hexagon<int> hex(Point<int>(0, 0), 1);
    double expected_area = 1.5 * std::sqrt(3) * 1 * 1;
    EXPECT_NEAR(hex.area(), expected_area, 1e-9);
}
TEST(HexagonTest, VerticesCount) {
    Hexagon<int> hex(Point<int>(0, 0), 5);
    EXPECT_EQ(hex.get_vertices().size(), 6);
}


TEST(ArrayTest, BasicOperations) {
    Array<Figure<int>> arr;
    auto rh = std::make_shared<Rhombus<int>>(Point<int>(0, 0), 5, 90.0);
    arr.push_back(rh);
    EXPECT_EQ(arr.get_size(), 1);
    arr.remove(0);
    EXPECT_EQ(arr.get_size(), 0);
}
TEST(ArrayTest, TotalArea) {
    Array<Figure<int>> arr;
    auto rh = std::make_shared<Rhombus<int>>(Point<int>(0, 0), 2, 90.0); // площадь = 4
    auto pent = std::make_shared<Pentagon<int>>(Point<int>(0, 0), 1);
    double pent_area = 0.5 * 5 * 1 * 1 * std::sin(2 * M_PI / 5);
    arr.push_back(rh);
    arr.push_back(pent);
    double total = total_area(arr);
    EXPECT_NEAR(total, 4.0 + pent_area, 1e-9);
}


TEST(FigureTest, Comparison) {
    auto rh1 = std::make_shared<Rhombus<int>>(Point<int>(0, 0), 2, 90.0); // площадь = 4
    auto rh2 = std::make_shared<Rhombus<int>>(Point<int>(0, 0), 3, 90.0); // площадь = 9
    EXPECT_TRUE(*rh1 < *rh2);
    EXPECT_FALSE(*rh2 < *rh1);
    EXPECT_TRUE(*rh1 == *rh1);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
