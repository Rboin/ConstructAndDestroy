#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_image.h>
#include "entity/static/stone_mine_entity.h"
#include "sdl/panel/sdl_control_panel.h"
#include "settings.h"
#include "sdl/text/sdl_render_solid_text.h"
#include "sdl/image/sdl_image_health_render_object.h"
#include "sdl/panel/sdl_resource_panel.h"
#include "entity/player.h"
#include "sdl/label/sdl_render_label.h"
#include "entity/static/gold_mine_entity.h"
#include "entity/moving/knight_entity.h"
#include "entity/goal/evaluator/follow_path_evaluator.h"
#include "entity/goal/moving_entity_goal/think_goal.h"
#include "graph/graph_manager.h"
#include "entity/goal/moving_entity_goal/work_goal.h"
#include "textures/texture_manager.h"
#include "entity/moving/lumberjack_entity.h"
#include "sdl/panel/sdl_world_panel.h"
#include "sdl/image/sdl_image_render_object.h"
#include "sdl/text/sdl_render_text_object.h"
#include "sdl/panel/wave/sdl_wave_panel.h"
#include "sdl/window/sdl_window.h"
#include "entity/static/tree_entity.h"
#include "entity/goal/evaluator/obstacle_avoid_evaluator.h"
#include "entity/goal/evaluator/wander_evaluator.h"
#include "entity/moving/miner_entity.h"
#include "behaviour/calculator/basic_force_calculator.h"
#include "entity/goal/evaluator/work_evaluator.h"
#include "entity/static/building/warehouse_entity.h"
#include "sdl/event/sdl_key_event_dispatcher.h"
#include "sdl/event/sdl_mouse_event_dispatcher.h"
#include "sdl/event/slot/sdl_key_event_slot.h"
#include "entity/static/building/building_manager.h"
#include "sdl/panel/sdl_building_panel.h"
#include "sdl/event/slot/mouse_handler_buildingpanel.h"
#include "logic/neighbourhood/neighbourhood_manager.h"
#include "renderer/mesh.h"
#include "logic/world/world.h"
#include "behaviour/behaviour.h"
#include "sdl/event/slot/mouse_handler_world.h"
#include "entity/player_manager.h"
#include "entity/goal/evaluator/combat_evaluator.h"
#include "wave/wave.h"

int pos_x = 100, pos_y = 200, size_x = 800, size_y = 600, count = 4;

SDL_Window *window;
SDL_Renderer *renderer;

// initialize buildings and textures
std::vector<building_with_texture> buildings_with_textures = {
    {"castle.png", BuildingType::CASTLE},
    {"warehouse.png", BuildingType::WAREHOUSE}
};

std::vector<entity_with_texture> entities_with_textures = {
    {"lumberjack.png", MovingEntityType::LUMBERJACK},
    {"miner.png", MovingEntityType::MINER},
    {"knight.png", MovingEntityType::KNIGHT}
};


std::string get_texture_of_entity(MovingEntityType type) {
    for(int i = 0; i < entities_with_textures.size(); i++) {
        if (entities_with_textures.at(i).type == type) {
            return entities_with_textures.at(i).texture;
        }
    }
}

std::string get_texture_of_building(BuildingType building) {
    for(int i = 0; i < buildings_with_textures.size(); i++) {
        if (buildings_with_textures.at(i).type == building) {
            return buildings_with_textures.at(i).texture;
        }
    }
}

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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
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
        std::cout << "Failed to initialize SDL2_TTF: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool init_img() {
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (IMG_Init(flags) == -1) {
        std::cout << "Failed to initialize SDL2_IMG: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

// Initializes our window, renderer and sdl itself.
bool init_everything() {
    if (!init_sdl() || !create_window() || !create_renderer() || !init_font() || !init_img())
        return false;
    setup_renderer();
    return true;
}

int main(int argc, char **argv) {
    if (!init_everything()) {
        return -1;
    }
    TTF_Font *f_font = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);

    SDL_MouseEventDispatcher *mouse_dispatcher = SDL_MouseEventDispatcher::get_instance();
    SDL_KeyEventDispatcher *key_dispatcher = SDL_KeyEventDispatcher::get_instance();

    PlayerManager *pm = PlayerManager::get_instance();
    pm->setup(2);

    TextureManager *tm = TextureManager::get_instance();
    tm->setup(renderer);

    GraphManager *gm = GraphManager::get_instance();
    gm->setup({(float) size_x, (float) size_y});

    std::stack<vec2 *> path = gm->graph->a_star_path(gm->graph->nodes[0], gm->graph->nodes[99]);

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

    // Begin lumberjack entity
    ForceCalculator *calculator = new BasicForceCalculator();
    Behaviour *behaviour = new Behaviour(calculator);
    MovingEntity *entity = new LumberJackEntity(&base, pos, 100, 0.2, 0.2);
    ThinkGoal *think_goal = new ThinkGoal(entity);

    think_goal->add_evaluator(new WorkEvaluator());
    think_goal->add_evaluator(new FollowPathEvaluator());

    entity->set_behaviour(behaviour);
    entity->set_goal(think_goal);
    entity->set_player(player_id);

    vec2 entity_size = {50, 50};
    sdl_image_data *entity_data = new sdl_image_data{"lumberjack.png"};
    SDL_ImageRenderObject *entity_render_object = new SDL_ImageHealthRenderObject(pos, entity_size, entity_data,
                                                                                  entity);
    entity->set_representation(entity_render_object);

    World::get_instance()->add_entity(entity);
    // End lumberjack entity


    // Begin knight entity
    MovingEntity *knight_entity = new KnightEntity(&base, {100, 100}, 100, 0.2, 0.2);
    ForceCalculator *knight_calculator = new BasicForceCalculator();
    Behaviour *knight_behaviour = new Behaviour(knight_calculator);

    ThinkGoal *knight_think_goal = new ThinkGoal(knight_entity);
    knight_think_goal->add_evaluator(new CombatEvaluator());

    knight_entity->set_behaviour(knight_behaviour);
    knight_entity->set_goal(knight_think_goal);

    knight_entity->set_player(player_id);

    vec2 knight_entity_size = {50, 50};
    sdl_image_data *knight_entity_data = new sdl_image_data{"knight.png"};
    SDL_ImageRenderObject *knight_entity_render_object = new SDL_ImageHealthRenderObject(pos, knight_entity_size,
                                                                                         knight_entity_data,
                                                                                         knight_entity);

    knight_entity->set_representation(knight_entity_render_object);

    World::get_instance()->add_entity(knight_entity);
    // End knight entity

    // Begin gold miner entity
    ForceCalculator *gold_miner_calculator = new BasicForceCalculator();
    Behaviour *gold_miner_behaviour = new Behaviour(gold_miner_calculator);
    MovingEntity *gold_miner_entity = new MinerEntity(&base, {100, 100}, 100, 0.2, 0.2, GOLDMINER);
    ThinkGoal *gold_miner_think_goal = new ThinkGoal(gold_miner_entity);
    gold_miner_think_goal->add_evaluator(new WorkEvaluator());
    gold_miner_think_goal->add_evaluator(new FollowPathEvaluator());

    gold_miner_entity->set_behaviour(gold_miner_behaviour);
    gold_miner_entity->set_goal(gold_miner_think_goal);

    gold_miner_entity->set_player(1);

    vec2 gold_miner_entity_size = {50, 50};
    sdl_image_data *gold_miner_entity_data = new sdl_image_data{"miner.png"};
    SDL_ImageRenderObject *gold_miner_entity_render_object = new SDL_ImageHealthRenderObject(pos,
                                                                                             gold_miner_entity_size,
                                                                                             gold_miner_entity_data,
                                                                                             gold_miner_entity);
    gold_miner_entity->set_representation(gold_miner_entity_render_object);

    World::get_instance()->add_entity(gold_miner_entity);
    // End gold mine miner entity

    // Begin stone miner entity
    ForceCalculator *stone_miner_calculator = new BasicForceCalculator();
    Behaviour *stone_miner_behaviour = new Behaviour(stone_miner_calculator);
    MovingEntity *stone_miner_entity = new MinerEntity(&base, {100, 100}, 100, 0.2, 0.2, STONEMINER);
    ThinkGoal *stone_miner_think_goal = new ThinkGoal(stone_miner_entity);
    stone_miner_think_goal->add_evaluator(new WorkEvaluator());
    stone_miner_think_goal->add_evaluator(new FollowPathEvaluator());

    stone_miner_entity->set_behaviour(stone_miner_behaviour);
    stone_miner_entity->set_goal(stone_miner_think_goal);

    stone_miner_entity->set_player(1);

    vec2 stone_miner_entity_size = {50, 50};
    sdl_image_data *stone_miner_entity_data = new sdl_image_data{"miner.png"};
    SDL_ImageRenderObject *stone_miner_entity_render_object = new SDL_ImageHealthRenderObject(pos,
                                                                                             stone_miner_entity_size,
                                                                                             stone_miner_entity_data,
                                                                                             stone_miner_entity);
    stone_miner_entity->set_representation(stone_miner_entity_render_object);

    World::get_instance()->add_entity(stone_miner_entity);
    // End stone mine miner entity

    // Begin tree entity
    vec2 s_position = {400, 280}, s_size = {50, 50};
    ResourceEntity *s_entity = new TreeEntity(&base, s_position, 50);
    sdl_image_data *tree_data = new sdl_image_data{"tree.png"};
    s_entity->set_textures("tree.png", "trunk.png");
    SDL_ImageRenderObject *tree_object = new SDL_ImageRenderObject(s_position, s_size, tree_data);
    s_entity->set_representation(tree_object);
    World::get_instance()->add_entity(s_entity);
    // End tree entity

    // Begin tree entity
    vec2 s1_position = {400, 240}, s1_size = {50, 50};
    ResourceEntity *s1_entity = new TreeEntity(&base, s1_position, 50);
    sdl_image_data *tree1_data = new sdl_image_data{"tree.png"};
    s1_entity->set_textures("tree.png", "trunk.png");
    SDL_ImageRenderObject *tree1_object = new SDL_ImageRenderObject(s1_position, s1_size, tree1_data);
    s1_entity->set_representation(tree1_object);
    World::get_instance()->add_entity(s1_entity);
    // End tree entity

    // Begin warehouse entity
    vec2 s_position7 = {600, 400};
    BuildingEntity *s_entity7 = new WarehouseEntity(&base, s_position7, 50);
    sdl_image_data *entity7_data = new sdl_image_data{"warehouse.png"};
    SDL_ImageRenderObject *e7_object = new SDL_ImageRenderObject(s_position7, {50, 50}, entity7_data);
    s_entity7->set_representation(e7_object);

    World::get_instance()->add_entity(s_entity7);
    // End warehouse entity

    // Begin gold mine entity
    vec2 gold_mine_position = {320, 280}, gold_mine_size = {50, 50};
    ResourceEntity *gold_mine_entity = new GoldMineEntity(&base, gold_mine_position, 50);
    sdl_image_data *gold_mine_data = new sdl_image_data{"goldmine.png"};
    gold_mine_entity->set_textures("goldmine.png", "depletedgoldmine.png");
    SDL_ImageRenderObject *gold_mine_object = new SDL_ImageRenderObject(gold_mine_position, gold_mine_size,
                                                                        gold_mine_data);
    gold_mine_entity->set_representation(gold_mine_object);

    World::get_instance()->add_entity(gold_mine_entity);
    // End gold mine entity

    // Begin stone mine entity
    vec2 stone_mine_position = {240, 240}, stone_mine_size = {50, 50};
    ResourceEntity *stone_mine_entity = new StoneMineEntity(&base, stone_mine_position, 50);
    sdl_image_data *stone_mine_data = new sdl_image_data{"stonemine.png"};
    stone_mine_entity->set_textures("stonemine.png", "depletedstonemine.png");
    SDL_ImageRenderObject *stone_mine_object = new SDL_ImageRenderObject(stone_mine_position, stone_mine_size,
                                                                        stone_mine_data);
    stone_mine_entity->set_representation(stone_mine_object);

    World::get_instance()->add_entity(stone_mine_entity);
    // End gold mine entity

    // TODO: when merged enemy_player, change 1 to player_id
    BuildingManager::get_instance()->add_building(1, s_entity7);

    SDLRenderer *render_engine = new SDLRenderer(renderer);

    sdl_image_data *world_data = new sdl_image_data{"world.png"};
    SDL_ImageRenderObject *world_representation = new SDL_ImageRenderObject({0, 0}, {800, 600}, world_data);

    World::get_instance()->set_render_object(world_representation);

    vec2 main_panel_position = {0, 0}, main_panel_size = {800, 600};
    sdl_data *panel_data = new sdl_data{255, 255, 255};

    SDL_RenderObject *main_panel_representation = new SDL_RenderObject(main_panel_position, main_panel_size,
                                                                       panel_data);

    SDLWorldPanel *main_panel = new SDLWorldPanel(main_panel_representation);

    main_panel->set_world(World::get_instance());

    SDLWindow *main_window = new SDLWindow(nullptr, window, render_engine, mouse_dispatcher,
                                           key_dispatcher);

    MouseHandlerWorld *world_panel_slot = new MouseHandlerWorld();

    main_panel->set_mouse_callback(world_panel_slot);

    SDL_KeyEventSlot *key_slot = new SDL_KeyEventSlot();

    main_window->set_key_callback(key_slot);

    key_dispatcher->register_callback(main_window, key_slot);

    mouse_dispatcher->register_callback(main_panel, world_panel_slot);


    ///Begin Resource panel
    vec2 resource_panel_pos = {600,0}, resource_panel_size = {200, 40};
    sdl_data *resource_panel_data = new sdl_data{0, 0, 0, 100};
    SDL_RenderObject *panel_o = new SDL_RenderObject(resource_panel_pos, resource_panel_size, resource_panel_data);
    SDLResourcePanel *resource_panel = new SDLResourcePanel(panel_o);

    sdl_data *sdl_label_data = new sdl_data{255, 255, 255, 255};
    vec2 resource_panel_pos_wood = {605, 5};
    SDLRenderLabel *wood_label = new SDLRenderLabel(resource_panel_pos_wood, {60, 30}, sdl_label_data, "log.png",
                                                    ResourceType::WOOD, f_font);
    SDLPanel *wood_panel = new SDLPanel(wood_label);

    vec2 resource_panel_pos_gold = {675, 5};
    SDLRenderLabel *gold_label = new SDLRenderLabel(resource_panel_pos_gold, {60, 30}, sdl_label_data, "gold.png",
                                                    ResourceType::GOLD, f_font);
    SDLPanel *gold_panel = new SDLPanel(gold_label);

    vec2 resource_panel_pos_stone = {740, 5};
    SDLRenderLabel *stone_label = new SDLRenderLabel(resource_panel_pos_stone, {60, 30}, sdl_label_data, "stone.png",
                                                    ResourceType::STONE, f_font);
    SDLPanel *stone_panel = new SDLPanel(stone_label);



    ///End Resource Panel

    ///Begin Waves
    std::vector<MovingEntityType> possibilities = {
            MovingEntityType::KNIGHT
    };
    Wave *wave = new Wave(300, 10, 2);
    wave->set_spawn_possibilities(possibilities);
    vec2 wave_panel_position = {10, 300}, wave_panel_size = {150, 200};
    std::string wave_content = "";
    std::string wave_font = "res/font/Roboto/Roboto-Regular.ttf";
    sdl_solid_text *wave_panel_data = new sdl_solid_text{{0, 0, 0, 100}, {255, 255, 255, 255}, wave_font, 18, 15,
                                                         wave_content};
    SDLRenderSolidText *wave_render_object = new SDLRenderSolidText(wave_panel_position, wave_panel_size,
                                                                    wave_panel_data);
    SDLWavePanel *wave_panel = new SDLWavePanel(wave_render_object, wave);
    ///End Waves


    // building/control panel
    vec2 control_panel_pos = {0, 500}, control_panel_size = {800, 100.0};
    sdl_data *control_panel_data = new sdl_data{100, 100, 100, 100};
    SDL_RenderObject *panel_b = new SDL_RenderObject(control_panel_pos, control_panel_size, control_panel_data);
    SDLControlPanel *control_panel = new SDLControlPanel(panel_b);


    resource_panel->add_component(wood_panel);
    resource_panel->add_component(gold_panel);
    resource_panel->add_component(stone_panel);
    main_panel->add_component(resource_panel);
    main_panel->add_component(wave_panel);
    main_panel->add_component(control_panel);
    main_window->add_component(main_panel);
    main_window->show();

    delete main_window;
    delete mouse_dispatcher;
    delete key_dispatcher;
    return 0;
}
