cmake_minimum_required(VERSION 3.5)

project(QMocEx VERSION 0.1 LANGUAGES CXX)
include_directories(tinycbor)

#_RECURSE
file(GLOB PROJECT_SOURCES FILES *.h *.cpp *.hpp)

add_executable(QMocEx  ${PROJECT_SOURCES})

set_target_properties(QMocEx PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(QMocEx PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG  ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(QMocEx PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})

set(MOC_EX_PATH ${CMAKE_CURRENT_BINARY_DIR}/QMocEx.exe PARENT_SCOPE)

add_subdirectory(genkey)

target_link_libraries(QMocEx PRIVATE  Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::CorePrivate )



