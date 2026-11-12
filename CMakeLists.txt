cmake_minimum_required(VERSION 3.31.6)
project(donut_spinner C)

set(CMAKE_C_STANDARD 11)

add_executable(donut_spinner source/main.c
        source/donut.c
        source/donut.h
        source/codec.c
        source/codec.h)

target_link_libraries(donut_spinner m)