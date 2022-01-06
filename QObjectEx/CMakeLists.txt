 cmake_minimum_required(VERSION 3.5)

project(QObjectEx VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core   REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core  REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCES FILES *.h *.cpp *.hpp)


add_library(QObjectEx STATIC ${PROJECT_SOURCES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_SOURCES})

target_include_directories(QObjectEx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ..)

target_link_libraries(QObjectEx PUBLIC Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core QWidgetEx QTypeEx QScintilla sol2 liblua-5.3.5)
