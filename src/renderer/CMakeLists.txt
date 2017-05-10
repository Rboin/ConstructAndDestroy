project(construct_and_destroy)

set(SOURCE_FILES
        mesh.h
        textures/texture_types.h
        textures/texture_manager.h
        textures/texture_manager.cpp
        renderer.h render_object.h
        sdl/sdl_render_object.cpp
        sdl/sdl_render_object.h
        sdl/ui/sdl_ui_render_text_object.h
        sdl/ui/sdl_ui_render_text_object.cpp
        sdl/image/sdl_image_render_object.cpp
        sdl/image/sdl_image_render_object.h
        sdl/label/sdl_render_label.cpp
        sdl/label/sdl_render_label.h sdl/sdl_renderer.cpp sdl/sdl_renderer.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(../logic)

add_library(cd_renderer STATIC
            ${SOURCE_FILES})

target_link_libraries(cd_renderer)