cmake_minimum_required(VERSION 3.0.0)
project(emulator)

set(GCC_VERSION_FLAGS "-std=c++14")
set(GCC_WARNING_FLAGS "-Weverything -Wall -Wpedantic -Wextra")

add_definitions(${GCC_VERSION_FLAGS})
add_definitions(${GCC_WARNING_FLAGS})

file(GLOB SOURCES src/*.cpp)
add_executable(emulator ${SOURCES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(emulator ${SFML_LIBRARIES})
endif()

