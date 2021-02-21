cmake_minimum_required(VERSION 3.20.0)
project(asteroids)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(src)

target_include_directories(asteroids SYSTEM PRIVATE
    "${PROJECT_SOURCE_DIR}/include/")

target_link_libraries(asteroids PRIVATE -lX11 -lGL -lpthread -lpng -lstdc++fs)