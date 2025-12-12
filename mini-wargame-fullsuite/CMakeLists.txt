cmake_minimum_required(VERSION 3.10)

project(MiniWargame)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/src)

# add project source dir to include paths so headers like "units/unit.h" resolve
include_directories(${CMAKE_SOURCE_DIR}/src)
file(GLOB SOURCES
    src/*.cpp
    src/phases/*.cpp
    src/units/*.cpp
    src/utils/*.cpp
)

add_executable(mini_wargame ${SOURCES})