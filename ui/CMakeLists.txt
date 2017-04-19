cmake_minimum_required(VERSION 3.2)
project(ui)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_AUTOMOC ON)
# GTest configuration
find_package(GTest)
# Qt5 library configuration
find_package(Qt5Widgets REQUIRED)

set(LIB_FILES
        ../include/vector.h ../include/vector.cpp
        ../include/matrix.h ../include/matrix.cpp
        )

set(HEADER_FILES
        component.h
        window/window.h
        panel/panel.h
        panel/world_panel.h
        view/game_view.h
        )
set(SOURCE_FILES
        component.cpp
        window/window.cpp
        panel/panel.cpp
        panel/world_panel.cpp
        view/game_view.cpp
        )

set(BIN_FILE main.cpp  )

qt5_wrap_cpp(ui_header_moc ${HEADER_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)

add_library(ui_lib
        ${LIB_FILES}
        ${SOURCE_FILES}
        ${construct_and_destroy_ui_header_moc}
        ${construct_and_destroy_ui_moc}
        )


target_link_libraries(ui_lib Qt5::Widgets)

add_executable(ui ${BIN_FILE})

target_link_libraries(ui ui_lib)
