add_subdirectory(QMocEx)
add_subdirectory(QScintilla)
add_subdirectory(SOL)

function(get_all_targets var)
    set(targets)
    get_all_targets_recursive(targets ${CMAKE_CURRENT_SOURCE_DIR})
    set(${var} ${targets} PARENT_SCOPE)
endfunction()

macro(get_all_targets_recursive targets dir)
    get_property(subdirectories DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)
    foreach(subdir ${subdirectories})
        get_all_targets_recursive(${targets} ${subdir})
    endforeach()
    get_property(current_targets DIRECTORY ${dir} PROPERTY BUILDSYSTEM_TARGETS)
    list(APPEND ${targets} ${current_targets})
endmacro()

get_all_targets(TARGET_LIST)

foreach(TARGET_ITEM ${TARGET_LIST})
    set_target_properties(${TARGET_ITEM} PROPERTIES FOLDER "3rdParty")
endforeach()
