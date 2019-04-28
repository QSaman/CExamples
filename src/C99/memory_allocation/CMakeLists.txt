project(strtok_example)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(GLOB_RECURSE SRC_LIST src/*.c src/*.h)

################################################################################

foreach (SRC ${SRC_LIST})
    get_filename_component(SRC_FILE ${SRC} NAME_WE)
    add_executable(${SRC_FILE} ${SRC})
endforeach (SRC ${SRC_LIST})


