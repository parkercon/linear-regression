cmake_minimum_required(VERSION 3.14)
project(myproject VERSION 1.0.1)
set(CMAKE_CXX_STANDARD 17)

find_package(Matplot++ REQUIRED)

add_executable(execute ui.cpp matrix.cpp linear_regression.cpp main.cpp)

target_link_libraries(execute PUBLIC Matplot++::matplot)
