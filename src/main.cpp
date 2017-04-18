#include <iostream>
#include <SDL2/SDL.h>
#include <types.h>
#include <vector.h>
#include <behaviour/strategy/explore_strategy.h>
#include <entity/goal/moving_entity_goal/think_goal.h>
#include <graph/graph_manager.h>
#include <entity/goal/moving_entity_goal/work_goal.h>
#include <SDL2/SDL_ttf.h>
#include <textures/texture_manager.h>
#include <entity/moving/lumberjack_entity.h>
#include <entity/player_manager.h>
#include <entity/moving/miner_entity.h>
#include <entity/goal/evaluator/work_evaluator.h>
#include <entity/goal/evaluator/rest_evaluator.h>
#include <entity/goal/evaluator/eat_evaluator.h>
#include <entity/moving/skeleton_entity.h>
#include <entity/static/resource_entity.h>
#include <entity/static/restaurant_entity.h>
#include <entity/static/warehouse_entity.h>
#include <entity/static/tree_entity.h>
#include <entity/static/iron_mine_entity.h>
#include <entity/static/campfire_entity.h>
#include <entity/goal/evaluator/wander_evaluator.h>
#include <entity/goal/evaluator/obstacle_avoid_evaluator.h>
#include <entity/goal/evaluator/explore_evaluator.h>
#include "logic/neighbourhood/neighbourhood_manager.h"
#include "renderer/mesh.h"
#include "logic/world/world.h"
#include "behaviour/behaviour.h"
#include "behaviour/calculator/basic_force_calculator.h"
#include "behaviour/strategy/arrive_strategy.h"
#include "behaviour/strategy/obstacle_avoidance_strategy.h"
#include "tree/bsp_tree.h"
#include "simulation.h"
#include "ui/window/simulation_window.h"
#include "ui/panel/world_panel.h"
#include "ui/eventhandler/mouse_handler.h"
#include "ui/eventhandler/key_handler.h"

int pos_x = 100, pos_y = 200, size_x = 800, size_y = 600, count = 4;

SDL_Window *window;
SDL_Renderer *renderer;
World world1;

bool init_sdl() {
    if (SDL_Init(0) == -1) {
        std::cout << " Failed to open SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool create_window() {
    window = SDL_CreateWindow("Construct And Destroy", pos_x, pos_y, size_x, size_y, 0);

    if (!window) {
        std::cout << " Failed to open window: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool create_renderer() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << " Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void setup_renderer() {
    // Set size of renderer to the same as window
    SDL_RenderSetLogicalSize(renderer, size_x, size_y);
    // Set color of renderer to green
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
}

bool init_font() {
    if (TTF_Init() == -1) {
        std::cout << "Failed to initialize font: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

// Initializes our window, renderer and sdl itself.
bool init_everything() {
    if (!init_sdl() || !create_window() || !create_renderer() || !init_font())
        return false;
    setup_renderer();
    return true;
}

int main(int argc, char **argv) {
    if (!init_everything()) {
        return -1;
    }
#pragma region Initialize Managers
    PlayerManager *pm = PlayerManager::get_instance();
    pm->setup(4);

    TextureManager *tm = TextureManager::get_instance();
    tm->setup(renderer);

    GraphManager *gm = GraphManager::get_instance();
    gm->setup({(float) size_x, (float) size_y});

    std::vector<vec2 *> path = gm->graph->a_star_path(gm->graph->nodes[0], gm->graph->nodes[99]);

    world1.add_graph(gm->graph);

    NeighbourhoodManager *n = NeighbourhoodManager::get_instance();
    n->setup({(float) size_x, (float) size_y}, {200.0f, 200.0f});

    vec2 default_shape[] = {
            {-20, -20},
            {20,  -20},
            {20,  20},
            {-20, 20},
    };
    mesh base = {4, default_shape};
#pragma endregion Initialize Managers

#pragma region Static entities
    vec2 s_position = {400, 280};
    ResourceEntity *s_entity = new TreeEntity(&base, s_position, 50);
    world1.add_entity(s_entity);

    vec2 s_position1 = {400, 240};
    ResourceEntity *s_entity1 = new TreeEntity(&base, s_position1, 50);
    world1.add_entity(s_entity1);

    vec2 s_position2 = {400, 200};
    ResourceEntity *s_entity2 = new TreeEntity(&base, s_position2, 50);
    world1.add_entity(s_entity2);

    vec2 s_position4 = {360, 280};
    ResourceEntity *s_entity4 = new TreeEntity(&base, s_position4, 50);
    world1.add_entity(s_entity4);

    vec2 s_position5 = {360, 240};
    ResourceEntity *s_entity5 = new IronMineEntity(&base, s_position5, 50);
    world1.add_entity(s_entity5);

    vec2 s_position6 = {360, 200};
    ResourceEntity *s_entity6 = new TreeEntity(&base, s_position6, 50);
    world1.add_entity(s_entity6);

    vec2 s_position7 = {600, 400};
    ResourceEntity *s_entity7 = new WarehouseEntity(&base, s_position7, 50);
    world1.add_entity(s_entity7);

    vec2 s_position8 = {40, 160};
    ResourceEntity *s_entity8 = new RestaurantEntity(&base, s_position8, 50);
    world1.add_entity(s_entity8);

    vec2 s_position9 = {400, 480};
    ResourceEntity *s_entity9 = new CampfireEntity(&base, s_position9, 50);
    world1.add_entity(s_entity9);
#pragma endregion Static Object

#pragma  region A*
    ForceCalculator *a_star_calculator = new BasicForceCalculator();
    Behaviour *a_star_behaviour = new Behaviour(a_star_calculator);

    vec2 a_star_starting_pos = {0, 80};
    MovingEntity *a_star_entity = new LumberJackEntity(&base, a_star_starting_pos, 10, 0.2, 0.2);
    a_star_entity->set_player(1);

    ThinkGoal *a_star_think_goal = new ThinkGoal(a_star_entity);
    a_star_think_goal->add_evaluator(new WorkEvaluator());
    a_star_entity->set_behaviour(a_star_behaviour);
    a_star_entity->set_goal(a_star_think_goal);

    world1.add_entity(a_star_entity);

    ForceCalculator *a_star_calculator2 = new BasicForceCalculator();
    Behaviour *a_star_behaviour2 = new Behaviour(a_star_calculator2);

    vec2 a_star_starting_pos2 = {760, 320};
    MovingEntity *a_star_entity2 = new MinerEntity(&base, a_star_starting_pos2, 10, 0.2, 0.2);
    a_star_entity2->set_player(1);

    ThinkGoal *a_star_think_goal2 = new ThinkGoal(a_star_entity2);
    a_star_think_goal2->add_evaluator(new WorkEvaluator());
    a_star_entity2->set_behaviour(a_star_behaviour2);
    a_star_entity2->set_goal(a_star_think_goal2);

    world1.add_entity(a_star_entity2);
#pragma endregion A*

    SDL_Color f_color = {0, 0, 0, 255};
    TTF_Font *f_font = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 16);
//    information static_information = {
//            "Press <S> to show Graph\nClick on an entity to select it\nClick anywhere to deselect it",
//            &f_color,
//            f_font
//    };

    SDL_Rect s_window_rect = {0, 0, size_x, size_y};
    SDL_Rect s_screen_rect = {0, 0, size_x, size_y};
//    SDL_Rect s_info_rect = {600, 0, 200, 600};
    WorldPanel s_screen = WorldPanel(&world1, &s_screen_rect);
//    SimulationWindow s_window = SimulationWindow(window, renderer, &s_window_rect);
//    InformationPanel s_info_panel = InformationPanel(&s_info_rect, &static_information);

//    s_window.add_component("panel", &s_screen);
//    s_window.add_component("info", &s_info_panel);
//    Simulation simulation = Simulation(&s_window);

    MouseHandler mouse_handler = MouseHandler();
    KeyHandler key_handler = KeyHandler();

//    s_info_panel.set_subject(&mouse_handler);

//    simulation.set_key_handler(&key_handler);
//    simulation.set_mouse_handler(&mouse_handler);

//    world1.set_texture(renderer);
//
//    simulation.loop();

    return 0;
}
