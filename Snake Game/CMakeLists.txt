cmake_minimum_required(VERSION 3.10)

project("Snake Game")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Snake Game main.cpp)

target_include_directories(Snake Game PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(Snake Game PRIVATE sfml-graphics sfml-window sfml-system)