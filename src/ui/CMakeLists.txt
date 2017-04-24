project(construct_and_destroy)

set(SOURCE_FILES
        eventhandler/event_handler.h
        ui_component.h
        panel/world_panel.h
        window/simulation_window.h
        panel/information_panel.h
        eventhandler/key_handler.h
        eventhandler/mouse_handler.h
        ui_component.cpp
        panel/world_panel.cpp
        window/simulation_window.cpp
        panel/information_panel.cpp
        eventhandler/key_handler.cpp
        eventhandler/mouse_handler.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the rendering and logic projects as a dependency
include_directories(../renderer ../logic)

add_library(cd_ui STATIC
            ${SOURCE_FILES})

target_link_libraries(cd_ui cd_renderer cd_logic)