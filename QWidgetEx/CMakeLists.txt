cmake_minimum_required(VERSION 3.5)

project(QWidgetEx VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core REQUIRED)


file(GLOB_RECURSE PROJECT_SOURCES FILES  *.h *.cpp *.hpp)

set(QWIDGET_EX_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
    Adjuster
    Widgets
    Window
    Effect
    ..
)

qt6_add_resources(QRC_FILES resources.qrc)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_SOURCES})

message(WARNING "TEST ${QRC_FILES}")

add_library(QWidgetEx
    STATIC
    ${PROJECT_SOURCES}
    ${QRC_FILES}
)

target_include_directories(QWidgetEx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(QWidgetEx PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ksuser ole32)
target_link_libraries(QWidgetEx PUBLIC QTypeEx)


