cmake_minimum_required(VERSION 3.16)
project(WFSLib VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(WFSLib STATIC
    src/WFSClient.cpp
)

find_package(CURL REQUIRED)
#sudo  apt install libtinyxml2-dev
#find_path(TINYXML2_INCLUDE_DIR tinyxml2.h)
find_library(TINYXML2_LIBRARY tinyxml2)

# if(NOT TINYXML2_INCLUDE_DIR OR NOT TINYXML2_LIBRARY)
#     message(FATAL_ERROR "TinyXML2 library not found. Please install libtinyxml2-dev.")
# endif()

include_directories(${TINYXML2_INCLUDE_DIR})

target_link_libraries(WFSLib
    PRIVATE CURL::libcurl
    #PRIVATE TinyXML2::TinyXML2
    PRIVATE ${TINYXML2_LIBRARY}
)

# اختیاری: نمونه تست
add_executable(example example/main.cpp)
target_link_libraries(example WFSLib)
