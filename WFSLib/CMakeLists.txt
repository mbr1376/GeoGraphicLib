cmake_minimum_required(VERSION 3.16)
project(WFSLib VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(WFSLib SHARED
    src/WFSClient.cpp
    src/SLDClient.cpp
)
if(COPY_SHARED_LIBS)
    # If this target is a shared library, register it for automatic copying to the build/lib dir
    register_shared_lib_for_copy(WFSLib)
endif()



# Prefer find_package for TinyXML2; on Debian/Ubuntu the package is libtinyxml2-dev and
# on Fedora/RHEL it's tinyxml2-devel. This ensures we get an imported target and
# include directories properly.
# sudo dnf install tinyxml2-devel
# sudo apt install libtinyxml2-dev

# For ubuntu
find_package(CURL REQUIRED)
find_package(TinyXML2 REQUIRED)

target_link_libraries(WFSLib   PRIVATE CURL::libcurl
    #ubuntu
    #PRIVATE TinyXML2::TinyXML2
    # fedora
    PRIVATE tinyxml2::tinyxml2
)

target_include_directories(WFSLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# اختیاری: نمونه تست
add_executable(wfs_example example/main.cpp)
target_link_libraries(wfs_example WFSLib)
