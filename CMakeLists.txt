cmake_minimum_required(VERSION 3.1)

project(ConvexHullOfIntersections)

set(bin_name ${CMAKE_PROJECT_NAME})
set(lib_name choi)

file(GLOB lib_source "lib/*.cpp")
file(GLOB bin_source "bin/*.cpp")
file(GLOB test_source "test/*.cpp")

if (CMAKE_BUILD_TYPE STREQUAL "none")
    set(CMAKE_BUILD_TYPE release)
endif (CMAKE_BUILD_TYPE STREQUAL "none")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -march=native")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

include_directories("include")

add_library(${lib_name} STATIC ${lib_source})

add_executable(${bin_name} ${bin_source})
target_link_libraries(${bin_name} ${lib_name})

add_executable(unit_test ${test_source})
target_link_libraries(unit_test ${lib_name})

include(CTest)
add_test(unit_test ${PROJECT_BINARY_DIR}/unit_test)
add_test(system_test ${CMAKE_SOURCE_DIR}/script/system_test.sh ${CMAKE_SOURCE_DIR} ${PROJECT_BINARY_DIR})
