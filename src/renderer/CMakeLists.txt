project(construct_and_destroy)

set(SOURCE_FILES
        mesh.h
        textures/texture_types.h
        textures/texture_manager.h
        textures/texture_manager.cpp
        renderer.h render_object.h sdl/sdl_ui_render_object.cpp sdl/sdl_ui_render_object.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(cd_renderer SHARED
            ${SOURCE_FILES})

target_link_libraries(cd_renderer)