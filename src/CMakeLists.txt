project(construct_and_destroy)

set(SOURCE_FILES)

add_subdirectory(logic)
add_subdirectory(renderer)
add_subdirectory(ui)

include_directories(${CMAKE_SOURCE_DIR}/include)
find_library(cd_logic REQUIRED)
find_library(cd_renderer REQUIRED)
find_library(cd_ui REQUIRED)

include_directories(renderer logic ui)

add_library(construct_and_destroy_lib STATIC
        ${SOURCE_FILES})

target_link_libraries(construct_and_destroy_lib cd_logic cd_renderer cd_ui)

add_executable(construct_and_destroy main.cpp ${SOURCE_FILES})

target_link_libraries(construct_and_destroy construct_and_destroy_lib)

add_custom_command(TARGET construct_and_destroy POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:construct_and_destroy>/res)