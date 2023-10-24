cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Explicitly set CMAKE_PREFIX_PATH
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libs/SDL2/SDL2-2.28.4/")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libs/SDL2_ttf/SDL2_ttf-2.20.2/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2TTF_INCLUDE_DIRS} src)

add_executable(TronGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/player.cpp)
target_include_directories(TronGame PRIVATE "${CMAKE_SOURCE_DIR}/libs/SDL2_ttf/SDL2_ttf-2.20.2/x86_64-w64-mingw32/include")
target_link_libraries(TronGame SDL2::SDL2 SDL2_ttf::SDL2_ttf)

