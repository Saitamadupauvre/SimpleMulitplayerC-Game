cmake_minimum_required(VERSION 3.20)

project(
    multiplayer
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 REQUIRED)

add_subdirectory(src)

target_include_directories(multiplayer PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

target_compile_options(multiplayer PRIVATE
    -W
    -Wall
    -Wextra
)
