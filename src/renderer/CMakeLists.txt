project(construct_and_destroy)

set(SOURCE_FILES
        mesh.h
        textures/texture_types.h
        textures/texture_manager.h
        textures/texture_manager.cpp
)

add_library(cd_renderer SHARED
            ${SOURCE_FILES})

target_link_libraries(cd_renderer)