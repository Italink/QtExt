cmake_minimum_required(VERSION 3.5)

project(QtExtension VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core REQUIRED)

include_directories(.)

add_subdirectory(QWidgetEx)
add_subdirectory(QTypeEx)
add_subdirectory(QObjectEx)

option(BUILD_EXMAPLE "build Example" ON)

if(BUILD_EXAMPLE)
	add_subdirectory(Example)
endif()