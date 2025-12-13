cmake_minimum_required(VERSION 3.16)
project(GeoWrapperExample VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include)


add_library(GeoWrapper STATIC GeoWrapper.cpp)
# for ubuntu
#target_link_libraries(GeoWrapper PUBLIC Geographic)
#for fedora
target_link_libraries(GeoWrapper PUBLIC GeographicLib)
target_include_directories(GeoWrapper PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GeographicLib_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


add_executable(example example/main.cpp)
target_link_libraries(example GeoWrapper)