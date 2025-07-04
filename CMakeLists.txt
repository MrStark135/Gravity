cmake_minimum_required(VERSION 4.0.3)
project(Gravity VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug
        CACHE STRING "Choose the build type (Debug / Release)" FORCE)
endif()

find_package(SFML 3.0 COMPONENTS System Window Graphics REQUIRED)

file(GLOB sources ./src/*)

add_executable(Gravity ${sources})

target_include_directories(Gravity PRIVATE include ${PROJECT_BINARY_DIR})

target_link_libraries(Gravity sfml-graphics sfml-window sfml-system)