project(construct_and_destroy)

set(SOURCE_FILES
        textures/texture_types.h
        textures/texture_manager.h
        textures/texture_manager.cpp
        renderer.h render_object.h
        sdl/sdl_render_object.cpp
        sdl/sdl_render_object.h
        sdl/text/sdl_render_text_object.h
        sdl/text/sdl_render_text_object.cpp
        sdl/image/sdl_image_render_object.cpp
        sdl/image/sdl_image_render_object.h
        sdl/label/sdl_render_label.cpp
        sdl/label/sdl_render_label.h
        sdl/sdl_renderer.h
        sdl/sdl_renderer.cpp
        sdl/text/sdl_render_solid_text.cpp
        sdl/text/sdl_render_solid_text.h
        sdl/image/sdl_image_health_render_object.cpp
        sdl/image/sdl_image_health_render_object.h
        sdl/progressbar/sdl_progressbar_render_object.cpp
        sdl/progressbar/sdl_progressbar_render_object.h
        camera/camera.h
        camera/camera.cpp
        camera/camera_manager.cpp
        camera/camera_manager.h
        sdl/label/sdl_cost_label.h
        sdl/label/sdl_cost_label.cpp
        sdl/label/sdl_name_label.h
        sdl/label/sdl_name_label.cpp
        sdl/label/manager/description_manager.h
        sdl/label/manager/description_manager.cpp
        sdl/badge/sdl_badge_render_object.cpp
        sdl/badge/sdl_badge_render_object.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(../logic)

add_library(cd_renderer STATIC
            ${SOURCE_FILES})

target_link_libraries(cd_renderer)