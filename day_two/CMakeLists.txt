cmake_minimum_required(VERSION 3.22)
project(day_two)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(include)

add_executable(day_two ${SOURCES})
