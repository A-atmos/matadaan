cmake_minimum_required(VERSION 3.22)
project(Matadaan)

set(CMAKE_CXX_STANDARD 14)

add_executable(Matadaan main.cpp src/block.hpp lib/sha256.hpp)

find_package(OpenSSL REQUIRED)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)


target_compile_features(Matadaan PRIVATE cxx_std_17)
target_sources(Matadaan PRIVATE main.cpp)
target_include_directories(Matadaan PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_directories(Matadaan PRIVATE ${GTKMM_LIBRARY_DIRS})
target_link_libraries(Matadaan PRIVATE ${GTKMM_LIBRARIES} OpenSSL::SSL)