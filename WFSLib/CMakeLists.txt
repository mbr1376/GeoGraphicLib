cmake_minimum_required(VERSION 3.16)
project(WFSLib VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(WFSLib STATIC
    src/WFSClient.cpp
)

find_package(CURL REQUIRED)

# Prefer find_package for TinyXML2; on Debian/Ubuntu the package is libtinyxml2-dev and
# on Fedora/RHEL it's tinyxml2-devel. This ensures we get an imported target and
# include directories properly.
# sudo dnf install tinyxml2-devel
# sudo apt install tinyxml2-dev
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
