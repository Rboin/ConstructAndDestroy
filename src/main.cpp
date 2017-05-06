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
#include <sdl/panel/sdl_panel.h>
#include <sdl/panel/sdl_world_panel.h>
#include <sdl/image/sdl_image_render_object.h>
#include <sdl/window/sdl_window.h>
#include <entity/static/tree_entity.h>
#include <entity/goal/evaluator/obstacle_avoid_evaluator.h>
#include <entity/goal/evaluator/wander_evaluator.h>
#include <entity/moving/miner_entity.h>
#include <behaviour/calculator/basic_force_calculator.h>
#include <entity/goal/evaluator/work_evaluator.h>
#include <entity/static/warehouse_entity.h>
#include "logic/neighbourhood/neighbourhood_manager.h"
#include "renderer/mesh.h"
#include "logic/world/world.h"
#include "behaviour/behaviour.h"
#include "sdl/event/sdl_mouse_event_dispatcher.h"
#include "sdl/event/slot/mouse_handler_world.h"


int pos_x = 100, pos_y = 200, size_x = 800, size_y = 600, count = 4;

SDL_Window *window;
SDL_Renderer *renderer;

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

    PlayerManager *pm = PlayerManager::get_instance();
    pm->setup(4);

    TextureManager *tm = TextureManager::get_instance();
    tm->setup(renderer);

    GraphManager *gm = GraphManager::get_instance();
    gm->setup({(float) size_x, (float) size_y});

    std::vector<vec2 *> path = gm->graph->a_star_path(gm->graph->nodes[0], gm->graph->nodes[99]);

    World::get_instance()->add_graph(gm->graph);

    NeighbourhoodManager *n = NeighbourhoodManager::get_instance();
    n->setup({(float) size_x, (float) size_y}, {200.0f, 200.0f});

    vec2 default_shape[] = {
            {-20, -20},
            {20,  -20},
            {20,  20},
            {-20, 20},
    };
    mesh base = {4, default_shape};
    vec2 pos = {0, 0};
    vec2 velocity = {0, 0, 0};
    /*
   #pragma region Obstacle, Arrive entity
       vec2 v = {400, 300};
       BehaviourStrategy *avoid = new ObstacleAvoidanceStrategy();
       avoid->set_targets(&v);

       vec2 v2 = {700, 500};
       BehaviourStrategy *arrive = new ArriveStrategy();
       arrive->set_targets(&v2);

*/
    ForceCalculator *calculator = new BasicForceCalculator();
    Behaviour *behaviour = new Behaviour(calculator);
    MovingEntity *entity = new LumberJackEntity(&base, pos, 100, 0.2, 0.2);
    ThinkGoal *think_goal = new ThinkGoal(entity);

    think_goal->add_evaluator(new WorkEvaluator());

    entity->set_behaviour(behaviour);
    entity->set_goal(think_goal);
    entity->set_player(1);

    vec2 entity_size = {50, 50};
    sdl_image_data entity_data = {"lumberjack.png"};
    SDL_ImageRenderObject entity_render_object = SDL_ImageRenderObject(pos, entity_size, &entity_data);
    entity->set_representation(&entity_render_object);

    World::get_instance()->add_entity(entity);
    /*
   #pragma endregion Obstacle, Arrive entity

   #pragma region Static entities
     */
    vec2 s_position = {400, 280}, s_size = {50, 50};
    ResourceEntity *s_entity = new TreeEntity(&base, s_position, 50);
    s_entity->set_textures(TextureTypes::TREETEXTURE, TextureTypes::TREEDEPLETEDTEXTURE);
    sdl_image_data tree_data = {"tree.png"};
    SDL_ImageRenderObject tree_object = SDL_ImageRenderObject(s_position, s_size, &tree_data);
    s_entity->set_representation(&tree_object);

    vec2 s_position7 = {600, 400};
    ResourceEntity *s_entity7 = new WarehouseEntity(&base, s_position7, 50);
    sdl_image_data entity7_data = {"warehouse.png"};
    SDL_ImageRenderObject e7_object = SDL_ImageRenderObject(s_position7, {50,50}, &entity7_data);
    s_entity7->set_representation(&e7_object);

    World::get_instance()->add_entity(s_entity7);
    World::get_instance()->add_entity(s_entity);
/*
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

   #pragma region Explore entity
       ForceCalculator *explore_calculator = new BasicForceCalculator();
       Behaviour *explore_behaviour = new Behaviour(explore_calculator);

       vec2 explore_starting_pos = {600, 40};
       MovingEntity *explore_entity = new LumberJackEntity(&base, explore_starting_pos, 10, 0.2, 0.2);
       ThinkGoal *explore_think_goal = new ThinkGoal(explore_entity);

       explore_think_goal->add_evaluator(new ExploreEvaluator());
       explore_entity->set_behaviour(explore_behaviour);
       explore_entity->set_goal(explore_think_goal);

       world1.add_entity(explore_entity);
   #pragma endregion explore entity
   #pragma  region A*
       ForceCalculator *a_star_calculator = new BasicForceCalculator();
       Behaviour *a_star_behaviour = new Behaviour(a_star_calculator);

       vec2 a_star_starting_pos = {0, 80};
       MovingEntity *a_star_entity = new LumberJackEntity(&base, a_star_starting_pos, 10, 0.2, 0.2);
       a_star_entity->set_player(1);

       ThinkGoal *a_star_think_goal = new ThinkGoal(a_star_entity);
       a_star_think_goal->add_evaluator(new WorkEvaluator());
       a_star_think_goal->add_evaluator(new RestEvaluator);
       a_star_think_goal->add_evaluator(new EatEvaluator());
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
       a_star_think_goal2->add_evaluator(new RestEvaluator());
       a_star_think_goal2->add_evaluator(new EatEvaluator());
       a_star_entity2->set_behaviour(a_star_behaviour2);
       a_star_entity2->set_goal(a_star_think_goal2);

       world1.add_entity(a_star_entity2);
   #pragma endregion A*

   #pragma region Enemy
       ForceCalculator *skeleton_calculator = new BasicForceCalculator();
       Behaviour *skeleton_behaviour = new Behaviour(skeleton_calculator);

       vec2 skeleton_starting_pos = {520, 280};
       MovingEntity *skeleton = new SkeletonEntity(&base, skeleton_starting_pos, 10, 0.2, 0.2);

       skeleton->set_behaviour(skeleton_behaviour);
       skeleton->add_weapons();
       world1.add_entity(skeleton);
   #pragma endregion skeleton

   #pragma  region Controllable Character
       ForceCalculator *cc_calculator = new BasicForceCalculator();
       Behaviour *cc_behaviour = new Behaviour(cc_calculator);

       vec2 cc_start_pos = {0, 0};
       MovingEntity *cc_entity = new MinerEntity(&base, cc_start_pos, 10, 0.2, 0.2);

       ThinkGoal *cc_think_goal = new ThinkGoal(cc_entity);
       cc_entity->set_behaviour(cc_behaviour);
       cc_entity->set_goal(cc_think_goal);

       world1.add_controllable_character(cc_entity);
   #pragma endregion Controllable Character
   */

    Renderer<SDL_Renderer> render_engine = Renderer<SDL_Renderer>(renderer);
    SDL_MouseEventDispatcher *mouse_dispatcher = SDL_MouseEventDispatcher::get_instance();

    sdl_image_data world_data = {"world.png"};
    SDL_ImageRenderObject world_representation = SDL_ImageRenderObject({0, 0}, {800, 600}, &world_data);

    World::get_instance()->set_render_object(&world_representation);

    vec2 main_panel_position = {0, 0}, main_panel_size = {800, 600};
    sdl_data panel_data = {255, 255, 255};

    SDL_RenderObject main_panel_representation = SDL_RenderObject(main_panel_position, main_panel_size, &panel_data);
    SDLWorldPanel main_panel = SDLWorldPanel(&main_panel_representation);
    main_panel.set_world(World::get_instance());

    SDLWindow main_window(&main_panel_representation, window, &render_engine, mouse_dispatcher);

    MouseHandlerWorld *world_panel_slot = new MouseHandlerWorld();

    main_panel.set_mouse_callback(world_panel_slot);
    main_window.set_mouse_callback(world_panel_slot);


    mouse_dispatcher->register_callback(&main_panel, world_panel_slot);
    mouse_dispatcher->register_callback(&main_window, world_panel_slot);

    main_window.add_component(&main_panel);

    main_window.show();

    return 0;
}