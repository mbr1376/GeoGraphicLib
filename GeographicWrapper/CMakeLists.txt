cmake_minimum_required(VERSION 3.16)
project(GeoWrapperExample VERSION 0.1 LANGUAGES CXX C)

# Compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Try to find GeographicLib (dependency). On Debian/Ubuntu the package is libgeographic-dev
# On Fedora/RHEL the package is geographiclib-devel.


#### for fedora/redhat
#find_package(GeographicLib REQUIRED)

add_library(GeoWrapper SHARED  
            src/GeoWrapper.cpp 
            src/api/geo.cpp
            src/geodesy/geodesicengine.cpp
            src/datum/ellipsoid.cpp
            src/datum/datum.cpp
            src/projection/transversemercator.cpp
            src/projection/utmprojection.cpp
            src/projection/projectionfacade.cpp
            src/projection/webmercator.cpp
            src/crs/crs.cpp
            src/transform/transformer.cpp
            src/datum/helmerttransform.cpp
            )
# for ubuntu
target_link_libraries(GeoWrapper PUBLIC GeographicLib)
# for fedora
#target_link_libraries(GeoWrapper PUBLIC Geographic)


# For linking use the imported target provided by the package (if available) so includes and
# link flags are handled correctly. If not provided, CMake may fallback to library names.
target_include_directories(GeoWrapper PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GeographicLib_INCLUDE_DIRS}
)
target_link_libraries(GeoWrapper PUBLIC ${GeographicLib_LIBRARIES} )


if(COPY_SHARED_LIBS)
    register_shared_lib_for_copy(GeoWrapper)
endif()
add_executable(examplewrapper example/main.cpp)
target_link_libraries(examplewrapper GeoWrapper)
