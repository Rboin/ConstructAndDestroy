cmake_minimum_required(VERSION 3.2)
project(construct_and_destroy_ui)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# GTest configuration
find_package(GTest)
# Qt5 library configuration
find_package(Qt5Widgets REQUIRED)

include_directories(.)

set(HEADER_FILES
        component.h
        )
set(SOURCE_FILES
        component.cpp)

#set(UI_FILES)
set(BIN_FILE main.cpp)

qt5_wrap_cpp(construct_and_destroy_ui_header_moc ${HEADER_FILES})
qt5_wrap_ui(construct_and_destroy_ui_moc ${UI_FILES})

add_library(construct_and_destroy_ui_lib
        ${SOURCE_FILES}
        ${construct_and_destroy_ui_header_moc}
        ${construct_and_destroy_ui_moc}
        )


target_link_libraries(construct_and_destroy_ui_lib Qt5::Widgets)

add_executable(construct_and_destroy_ui ${BIN_FILE})

target_link_libraries(construct_and_destroy_ui construct_and_destroy_ui_lib)
