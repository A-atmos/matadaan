cmake_minimum_required(VERSION 3.22)
project(Matadaan)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "E:\\boost_1_60_0")
set(BOOSTROOT "E:\\boost_1_60_0")
find_package(Boost 1.60.0 REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()



add_executable(Matadaan main.cpp src/block.hpp lib/sha256.hpp src/blockchain.hpp src/utils.hpp main.h)

find_package(OpenSSL REQUIRED)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)


if(Boost_FOUND)

    target_link_libraries(Matadaan ${Boost_LIBRARIES})

endif()
target_compile_features(Matadaan PRIVATE cxx_std_17)
target_sources(Matadaan PRIVATE main.cpp)
target_include_directories(Matadaan PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_directories(Matadaan PRIVATE ${GTKMM_LIBRARY_DIRS})
target_link_libraries(Matadaan PRIVATE ${GTKMM_LIBRARIES} OpenSSL::SSL)