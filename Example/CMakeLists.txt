cmake_minimum_required(VERSION 3.5)

project(Example VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE PROJECT_SOURCES FILES *.h *.cpp *.hpp)

add_executable(Example ${PROJECT_SOURCES})

target_lua_warp(Example Test.h)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_SOURCES})

target_link_libraries(Example PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core QtExt)
