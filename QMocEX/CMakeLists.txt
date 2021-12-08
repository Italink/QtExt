cmake_minimum_required(VERSION 3.5)
#set_target_properties(Qt6::moc PROPERTIES IMPORTED_LOCATION  "hello.exe")
project(QMocEx VERSION 0.1 LANGUAGES CXX)

include_directories(tinycbor)

#_RECURSE
file(GLOB PROJECT_SOURCES FILES *.h *.cpp *.hpp)

add_executable(QMocEx  ${PROJECT_SOURCES})

target_link_libraries(QMocEx PRIVATE  Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::CorePrivate )
