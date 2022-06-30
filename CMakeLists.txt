cmake_minimum_required(VERSION 3.22)
project(Matadaan)

set(CMAKE_CXX_STANDARD 14)

add_executable(Matadaan main.cpp src/block.hpp lib/sha256.hpp)

find_package(OpenSSL REQUIRED)
target_link_libraries(Matadaan OpenSSL::SSL)
