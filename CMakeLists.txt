cmake_minimum_required(VERSION 3.5)

project(QtExt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Core REQUIRED)

option(QtExt_BUILD_EXAMPLE "Build Example" ON)

file(GLOB_RECURSE PROJECT_SOURCES FILES
	QObjectEx/*.h QObjectEx/*.cpp QObjectEx/*.hpp  QObjectEx/*.inl
	QWidgetEx/*.h QWidgetEx/*.cpp QWidgetEx/*.hpp 
	QTypeEx/*.h QTypeEx/*.cpp QTypeEx/*.hpp 
)

qt6_add_resources(QRC_FILES resources.qrc)

add_library(QtExt STATIC ${PROJECT_SOURCES} ${QRC_FILES})

target_link_libraries(QtExt PUBLIC Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network ksuser ole32 QScintilla sol2 liblua-5.3.5)
target_include_directories(QtExt PUBLIC .)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_SOURCES})
set(QT_EXT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
function(target_lua_warp PROJECT_TARGET INPUT_FILE_PATH)                       
    get_filename_component(INPUT_FILE_NAME ${INPUT_FILE_PATH} NAME_WE)     
    set(OUTPUT_SOURCE ${CMAKE_CURRENT_BINARY_DIR}/AutoGenFiles/Lua_${INPUT_FILE_NAME}.cpp)      
    add_custom_command(
        OUTPUT ${OUTPUT_SOURCE}                                                               #指定输出文件
        COMMAND QMocEx ${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE_PATH} -o ${OUTPUT_SOURCE} -I ${QT_EXT_DIR} #命令行指令
        MAIN_DEPENDENCY ${INPUT_FILE_PATH}                                                    #指定依赖，当该文件变动时，自动调用该指令
        )          
    set_property(TARGET ${PROJECT_TARGET} APPEND PROPERTY SOURCES ${OUTPUT_SOURCE})          #添加到构建目标中
    source_group("Generated Files" FILES ${OUTPUT_SOURCE})                                    # 文件分组
endfunction()

add_subdirectory(3rdParty)
add_subdirectory(Example)


