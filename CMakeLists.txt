cmake_minimum_required(VERSION 3.20)
project(rotating_figures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
add_executable(rotating_figures
    src/main.cpp
    src/rhombus.cpp
    src/pentagon.cpp
    src/hexagon.cpp
)

target_include_directories(rotating_figures PUBLIC include)

# Тесты
find_package(GTest REQUIRED)
add_executable(tests
    test/test.cpp
    src/rhombus.cpp
    src/pentagon.cpp
    src/hexagon.cpp
)

target_include_directories(tests PUBLIC include)
target_link_libraries(tests GTest::gtest GTest::gtest_main)

# Установка для сборки
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(rotating_figures PRIVATE -Wall -Wextra -g)
    target_compile_options(tests PRIVATE -Wall -Wextra -g)
else()
    target_compile_options(rotating_figures PRIVATE -Wall -Wextra -O2)
    target_compile_options(tests PRIVATE -Wall -Wextra -O2)
endif()
