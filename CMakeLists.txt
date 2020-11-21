cmake_minimum_required(VERSION 3.15)

project(uamp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(app)
add_subdirectory(3dparty)
