cmake_minimum_required(VERSION 3.2)
project(construct_and_destroy)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# SDL2 Library configuration
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
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
# GTest configuration
find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})

set(LIB_FILES
        include/vector.h
        include/matrix.h
        include/types.h
        include/neighbourhood_manager.h
        include/base_entity.h
        include/weapon.h
        include/behaviour/behaviour.h
        include/behaviour/behaviour_strategy.h
        include/behaviour/force_calculator.h
        include/goal/goal.h
        include/goal/composite_goal.h
        include/goal/atomic_goal.h
        include/goal/goal_evaluator.h
        include/observer/observable.h
        include/observer/observer.h
        )

set(SOURCE_FILES
        src/vector.cpp
        src/matrix.cpp
        src/mesh.h
        src/world.h src/world.cpp

        src/entity/entity_types.h
        src/entity/base_entity.cpp

        src/entity/moving/moving_entity.h src/entity/moving/moving_entity.cpp
        src/entity/moving/lumberjack_entity.h src/entity/moving/lumberjack_entity.cpp
        src/entity/moving/miner_entity.h src/entity/moving/miner_entity.cpp
        src/entity/moving/skeleton_entity.h src/entity/moving/skeleton_entity.cpp

        src/entity/weapon/axe_weapon.h src/entity/weapon/axe_weapon.cpp
        src/entity/weapon/bow_weapon.h src/entity/weapon/bow_weapon.cpp

        src/entity/static/resource_type.h
        src/entity/static/static_entity.h src/entity/static/static_entity.cpp
        src/entity/static/resource_entity.h src/entity/static/resource_entity.cpp
        src/entity/static/resource_manager.h src/entity/static/resource_manager.cpp
        src/entity/static/tree_entity.h src/entity/static/tree_entity.cpp
        src/entity/static/iron_mine_entity.h src/entity/static/iron_mine_entity.cpp
        src/entity/static/warehouse_entity.h src/entity/static/warehouse_entity.cpp
        src/entity/static/restaurant_entity.h src/entity/static/restaurant_entity.cpp
        src/entity/static/campfire_entity.h src/entity/static/campfire_entity.cpp

        src/entity/goal/evaluator/obstacle_avoid_evaluator.h src/entity/goal/evaluator/obstacle_avoid_evaluator.cpp
        src/entity/goal/evaluator/wander_evaluator.h src/entity/goal/evaluator/wander_evaluator.cpp
        src/entity/goal/evaluator/explore_evaluator.h src/entity/goal/evaluator/explore_evaluator.cpp

        src/entity/goal/moving_entity_goal/atomic_goal_type.h
        src/entity/goal/moving_entity_goal/strategy_goal_type.h
        src/entity/goal/moving_entity_goal/job_type.h
        src/entity/goal/moving_entity_goal/level_type.h
        src/entity/goal/moving_entity_goal/atomic/wander_goal.h
        src/entity/goal/moving_entity_goal/atomic/wander_goal.cpp
        src/entity/goal/moving_entity_goal/think_goal.h src/entity/goal/moving_entity_goal/think_goal.cpp
        src/entity/goal/moving_entity_goal/atomic/obstacle_avoidance_goal.h
        src/entity/goal/moving_entity_goal/atomic/obstacle_avoidance_goal.cpp
        src/entity/goal/moving_entity_goal/atomic/explore_goal.h
        src/entity/goal/moving_entity_goal/atomic/explore_goal.cpp
        src/entity/goal/moving_entity_goal/follow_path_goal.h
        src/entity/goal/moving_entity_goal/follow_path_goal.cpp
        src/entity/goal/moving_entity_goal/atomic/plan_path_goal.h
        src/entity/goal/moving_entity_goal/atomic/plan_path_goal.cpp
        src/entity/goal/moving_entity_goal/atomic/traverse_edge_goal.h
        src/entity/goal/moving_entity_goal/atomic/traverse_edge_goal.cpp
        src/entity/goal/moving_entity_goal/work_goal.h src/entity/goal/moving_entity_goal/work_goal.cpp
        src/entity/goal/moving_entity_goal/atomic/gather_resource_goal.h
        src/entity/goal/moving_entity_goal/atomic/gather_resource_goal.cpp
        src/entity/goal/moving_entity_goal/atomic/drop_resources_goal.h
        src/entity/goal/moving_entity_goal/atomic/drop_resources_goal.cpp
        src/entity/goal/moving_entity_goal/rest_goal.h src/entity/goal/moving_entity_goal/rest_goal.cpp
        src/entity/goal/moving_entity_goal/atomic/sleep_goal.h src/entity/goal/moving_entity_goal/atomic/sleep_goal.cpp
        src/entity/goal/moving_entity_goal/go_eat_goal.h src/entity/goal/moving_entity_goal/go_eat_goal.cpp
        src/entity/goal/moving_entity_goal/atomic/eat_goal.h src/entity/goal/moving_entity_goal/atomic/eat_goal.cpp

        src/entity/goal/evaluator/gather_resource_evaluator.h src/entity/goal/evaluator/gather_resource_evaluator.cpp
        src/entity/goal/evaluator/work_evaluator.h src/entity/goal/evaluator/work_evaluator.cpp
        src/entity/goal/evaluator/follow_path_evaluator.h src/entity/goal/evaluator/follow_path_evaluator.cpp
        src/entity/goal/evaluator/rest_evaluator.h src/entity/goal/evaluator/rest_evaluator.cpp
        src/entity/goal/evaluator/eat_evaluator.h src/entity/goal/evaluator/eat_evaluator.cpp

        src/behaviour/behaviour.cpp
        src/behaviour/calculator/basic_force_calculator.cpp src/behaviour/calculator/basic_force_calculator.h

        src/behaviour/strategy/behaviour_strategy.cpp
        src/behaviour/strategy/arrive_strategy.cpp src/behaviour/strategy/arrive_strategy.h
        src/behaviour/strategy/seek_strategy.cpp src/behaviour/strategy/seek_strategy.h
        src/behaviour/strategy/flee_strategy.cpp src/behaviour/strategy/flee_strategy.h
        src/behaviour/strategy/obstacle_avoidance_strategy.cpp src/behaviour/strategy/obstacle_avoidance_strategy.h
        src/behaviour/strategy/wander_strategy.h src/behaviour/strategy/wander_strategy.cpp
        src/behaviour/strategy/explore_strategy.cpp src/behaviour/strategy/explore_strategy.h

        src/graph/graph_manager.cpp src/graph/graph_manager.h
        src/graph/node.cpp src/graph/node.h src/graph/a_star_node.cpp src/graph/a_star_node.h
        src/graph/edge.cpp src/graph/edge.h src/graph/graph.cpp src/graph/graph.h

        src/tree/bsp_tree.cpp src/tree/bsp_tree.h src/tree/bsp_node.h

        src/neighbourhood/neighbourhood_manager.cpp

        src/sorting/sort_strategy.h src/sorting/quicksort_strategy.cpp src/sorting/quicksort_strategy.h

        src/simulation.cpp src/simulation.h

        src/ui/eventhandler/event_handler.h
        src/ui/ui_component.h src/ui/ui_component.cpp
        src/ui/panel/world_panel.h src/ui/panel/world_panel.cpp
        src/ui/window/simulation_window.h src/ui/window/simulation_window.cpp
        src/ui/panel/information_panel.h src/ui/panel/information_panel.cpp
        src/ui/eventhandler/key_handler.h src/ui/eventhandler/key_handler.cpp
        src/ui/eventhandler/mouse_handler.h src/ui/eventhandler/mouse_handler.cpp

        src/textures/texture_types.h
        src/textures/texture_manager.h src/textures/texture_manager.cpp

        src/fuzzy/fuzzy_hedges.h
        src/fuzzy/fz_set.h
        src/fuzzy/fuzzy_rule.h
        src/fuzzy/fuzzy_set.h
        src/fuzzy/fuzzy_term.h
        src/fuzzy/fuzzy_module.h src/fuzzy/fuzzy_module.cpp
        src/fuzzy/fuzzy_operators.h src/fuzzy/fuzzy_operators.cpp
        src/fuzzy/fuzzy_set_triangle.h src/fuzzy/fuzzy_set_triangle.cpp
        src/fuzzy/fuzzy_variable.h src/fuzzy/fuzzy_variable.cpp
        src/fuzzy/fuzzy_set_singleton.h src/fuzzy/fuzzy_set_singleton.cpp
        src/fuzzy/fuzzy_set_left_shoulder.h src/fuzzy/fuzzy_set_left_shoulder.cpp
        src/fuzzy/fuzzy_set_right_shoulder.h src/fuzzy/fuzzy_set_right_shoulder.cpp
        )

set(TEST_FILES
        test/main.cpp test/example_test.cpp test/bsp_test.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(cd_lib ${LIB_FILES} ${SOURCE_FILES})


add_executable(construct_and_destroy src/main.cpp)
target_link_libraries(construct_and_destroy cd_lib)

add_custom_command(TARGET construct_and_destroy POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:construct_and_destroy>/res)

if (GTEST_FOUND)
    find_package(Threads REQUIRED)
    enable_testing()
    add_executable(tests ${TEST_FILES})
    target_link_libraries(tests ${GTEST_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} cd_lib)
    add_test(NAME tests COMMAND bin/tests)
endif (GTEST_FOUND)
