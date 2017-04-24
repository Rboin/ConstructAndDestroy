cmake_minimum_required(VERSION 3.2)
project(construct_and_destroy)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# SDL2 Library configuration
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
# GTest configuration
find_package(GTest)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIRS}
)
link_libraries(
        ${SDL2_LIBRARY}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
)

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
include_directories(include)