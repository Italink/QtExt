cmake_minimum_required(VERSION 3.5)

project(Example VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE PROJECT_SOURCES FILES *.h *.cpp *.hpp)

add_executable(Example ${PROJECT_SOURCES})

function(target_lua_warp PROJECT_TARGET INPUT_FILE_PATH)                       
    get_filename_component(INPUT_FILE_NAME ${INPUT_FILE_PATH} NAME_WE)     
    set(OUTPUT_SOURCE ${CMAKE_CURRENT_BINARY_DIR}/AutoGenFiles/Lua_${INPUT_FILE_NAME}.cpp)      
    add_custom_command(
        OUTPUT ${OUTPUT_SOURCE}                                                               #指定输出文件
        COMMAND QMocEx ${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE_PATH} -o ${OUTPUT_SOURCE} -I  F:/QtExt   #命令行指令
        MAIN_DEPENDENCY ${INPUT_FILE_PATH}                                                    #指定依赖，当该文件变动时，自动调用该指令
        )          
    set_property(TARGET ${PROJECT_TARGET} APPEND PROPERTY SOURCES ${OUTPUT_SOURCE})          #添加到构建目标中
    source_group("Generated Files" FILES ${OUTPUT_SOURCE})                                    # 文件分组
endfunction()

target_lua_warp(Example Test.h)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PROJECT_SOURCES})

target_link_libraries(Example PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core QtExt)
