cmake_minimum_required(VERSION 3.10)

project("Snake Game")

set(CMAKE_PREFIX_PATH "C:/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(SnakeGame main.cpp)

target_include_directories(SnakeGame PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(SnakeGame PRIVATE sfml-graphics sfml-window sfml-system)