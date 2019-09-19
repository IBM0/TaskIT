cmake_minimum_required(VERSION 3.10)
project(TaskIT)

set(CMAKE_CXX_STANDARD 14)

set(EXEC code)

file(GLOB SOURCES src/*.cpp)

include_directories(include)

add_executable(${EXEC} ${SOURCES})


