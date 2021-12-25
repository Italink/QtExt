 cmake_minimum_required(VERSION 3.5)

project(Example VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE PROJECT_SOURCES FILES *.h *.cpp *.hpp)

set(CMAKE_AUTOMOC ON)

add_executable(Example ${PROJECT_SOURCES})

#function(setup_mocex PROJECT_TARGET)
#	set_target_properties(Qt${QT_VERSION_MAJOR}::moc PROPERTIES IMPORTED_LOCATION ${MOC_EX_PATH})
#	add_dependencies(${PROJECT_TARGET}  QMocEx)
#endfunction()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_SOURCES})

target_link_libraries(Example PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core QObjectEx)
