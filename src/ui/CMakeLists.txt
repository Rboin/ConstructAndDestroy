project(construct_and_destroy)

set(SOURCE_FILES
        component/ui_component.h
        event/slot.h
        sdl/window/sdl_window.cpp
        sdl/window/sdl_window.h
        sdl/sdl_ui_component.h
        sdl/sdl_ui_component.h
        sdl/panel/sdl_panel.h
        sdl/panel/sdl_world_panel.h
        sdl/event/sdl_event_types.h
        sdl/button/sdl_button.h
        event/event_dispatcher.h
        event/event_types.h
        sdl/event/sdl_event_dispatcher.h
        sdl/event/slot/sdl_mouse_event_slot.h
        sdl/event/sdl_mouse_event_dispatcher.h
        sdl/event/sdl_key_event_dispatcher.h
        sdl/event/slot/mouse_handler_world.h
        sdl/event/sdl_mouse_event_dispatcher.cpp
        sdl/event/slot/sdl_mouse_event_slot.cpp
        sdl/event/slot/mouse_handler_world.cpp
        sdl/button/sdl_button.cpp
        sdl/sdl_ui_component.cpp
        sdl/panel/sdl_panel.cpp
        sdl/panel/sdl_world_panel.cpp
        sdl/window/sdl_window.cpp
        sdl/event/sdl_key_event_dispatcher.cpp
        sdl/event/slot/sdl_key_event_slot.h
        sdl/event/slot/sdl_key_event_slot.cpp
        sdl/panel/sdl_resource_panel.h
        sdl/panel/sdl_resource_panel.cpp
        sdl/panel/wave/sdl_wave_panel.cpp
        sdl/panel/wave/sdl_wave_panel.h
        sdl/panel/wave/state/wave_panel_preparing.cpp
        sdl/panel/wave/state/wave_panel_preparing.h
        sdl/panel/wave/state/wave_panel_spawning.cpp
        sdl/panel/wave/state/wave_panel_spawning.h sdl/panel/wave/state/wave_panel_finished.cpp sdl/panel/wave/state/wave_panel_finished.h sdl/button/restart_wave_button.cpp sdl/button/restart_wave_button.h)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the rendering and logic projects as a dependency
include_directories(../renderer ../logic)

add_library(cd_ui STATIC
    ${SOURCE_FILES}
        sdl/panel/sdl_building_panel.cpp
        sdl/panel/sdl_building_panel.h
        sdl/event/slot/mouse_handler_buildingpanel.cpp
        sdl/event/slot/mouse_handler_buildingpanel.h
        sdl/panel/sdl_unit_panel.cpp
        sdl/panel/sdl_unit_panel.h
        sdl/event/slot/mouse_handler_entitypanel.cpp
        sdl/event/slot/mouse_handler_entitypanel.h
        sdl/panel/sdl_entity_panel.cpp
        sdl/panel/sdl_entity_panel.h
        sdl/panel/sdl_control_panel.cpp
        sdl/panel/sdl_control_panel.h
        sdl/panel/sdl_progressbar_panel.cpp
        sdl/panel/sdl_progressbar_panel.h)

target_link_libraries(cd_ui cd_renderer cd_logic)

add_executable(ui_bin main.cpp ${SOURCE_FILES})

target_link_libraries(ui_bin cd_ui)