cmake_minimum_required(VERSION 3.5)

project(QTypeEx VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCES FILES  *.h *.cpp *.hpp)

set(QTYPE_EX_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(QTypeEx 
    STATIC
    ${PROJECT_SOURCES}
)

target_link_libraries(QTypeEx PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core)

target_include_directories(QTypeEx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})




