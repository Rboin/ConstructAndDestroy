project(construct_and_destroy)

set(TEST_FILES
        main.cpp example_test.cpp bsp_test.cpp)

if (GTEST_FOUND)
    include_directories(../include ../src ../src/renderer ../src/logic)
    find_package(Threads REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(tests ${TEST_FILES})
    target_link_libraries(tests ${GTEST_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} construct_and_destroy_lib)
    add_test(NAME tests COMMAND bin/tests)
endif (GTEST_FOUND)