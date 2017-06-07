#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_image.h>
#include <stack>
#include "sdl/button/restart_wave_button.h"
#include "sdl/panel/sdl_resource_label.h"
#include "sdl/label/sdl_name_label.h"
#include "sdl/label/manager/description_manager.h"
#include "sdl/badge/sdl_badge_render_object.h"
#include "camera/camera_manager.h"
#include "sdl/panel/sdl_unit_info_panel.h"
#include "sdl/label/sdl_render_resource_label.h"
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
#include "sdl/panel/wave/sdl_wave_panel.h"
#include "sdl/window/sdl_window.h"
#include "entity/static/tree_entity.h"
#include "entity/goal/evaluator/wander_evaluator.h"
#include "entity/moving/miner_entity.h"
#include "behaviour/calculator/basic_force_calculator.h"
#include "entity/goal/evaluator/work_evaluator.h"
#include "sdl/event/sdl_key_event_dispatcher.h"
#include "sdl/event/sdl_mouse_event_dispatcher.h"
#include "sdl/event/slot/sdl_key_event_slot.h"
#include "sdl/event/slot/mouse_handler_buildingpanel.h"
#include "logic/world/world.h"
#include "behaviour/behaviour.h"
#include "sdl/event/slot/mouse_handler_world.h"
#include "entity/player_manager.h"
#include "entity/goal/evaluator/combat_evaluator.h"
#include "wave/wave.h"
#include "wave/wave_manager.h"
#include "sdl/event/slot/wave_reset_handler.h"
#include "graph/graph.h"

int pos_x = 100, pos_y = 200;

SDL_Window *window;
SDL_Renderer *renderer;

vec2 window_size = {800, 600};
float camera_zoom = 1.0f;

// initialize buildings and textures
std::vector<building_with_texture> buildings_with_textures = {
    {"castle.png", BuildingType::CASTLE, new Resources(0,25,25,0), "Castle", "This building can create new units"},
    {"warehouse.png", BuildingType::WAREHOUSE, new Resources(0,10,10,0), "Warehouse", "This building is used to store resources"},
    {"horsestable.png", BuildingType::STABLE, new Resources(0,50,50,0), "Stable", "This building can create strong fighters on horseback"},
    {"warfactory.png", BuildingType::WARFACTORY, new Resources(0,50,50,0), "Warfactory", "This building can create some advanced warfare units"}
};

std::vector<entity_with_texture> entities_with_textures = std::vector<entity_with_texture>{
        {"lumberjack.png", MovingEntityType::LUMBERJACK},
        {"goldminer.png",      MovingEntityType::GOLDMINER},
        {"stoneminer.png",      MovingEntityType::STONEMINER},
        {"knight.png",     MovingEntityType::KNIGHT},
        {"lightcavalier.png",   MovingEntityType::LIGHT_CAVALIER},
        {"cavalier.png",      MovingEntityType::CAVALIER},
        {"heavycavalier.png", MovingEntityType::HEAVY_CAVALIER},
        {"mercenary.png", MovingEntityType::MERCENARY},
        {"juggernaut.png", MovingEntityType::JUGGERNAUT}
};

std::string get_texture_of_entity(MovingEntityType type) {
    for (int i = 0; i < entities_with_textures.size(); i++) {
        if (entities_with_textures.at(i).type == type) {
            return entities_with_textures.at(i).texture;
        }
    }
}

std::string get_texture_of_building(BuildingType building) {
    for (int i = 0; i < buildings_with_textures.size(); i++) {
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
    window = SDL_CreateWindow("Construct And Destroy", 100, 100,
                              (int) window_size.x, (int) window_size.y, SDL_WINDOW_RESIZABLE);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
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
    SDL_RenderSetLogicalSize(renderer, (int) window_size.x, (int) window_size.y);
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

bool init_world() {
    sdl_image_data *world_data = new sdl_image_data{"world-large.png"};
    SDL_ImageRenderObject *world_representation = new SDL_ImageRenderObject({0, 0}, world_size, world_data);

    if (!world_data || !world_representation) {
        return false;
    }
    World::get_instance()->set_render_object(world_representation);
    return true;
}

bool init_camera() {
    CameraManager *camera = CameraManager::get_instance();

    return camera != nullptr;
}

// Initializes our window, renderer and sdl itself.
bool init_everything() {
    if (!init_sdl() || !create_window() || !create_renderer() || !init_font() || !init_img() || !init_camera() ||
        !init_world())
        return false;
    setup_renderer();
    return true;
}

int random_number(int size) {
    static int number = 1;
    number = (221 * number + 1) % size;
    return number;
}

void add_trees(int amount) {
    GraphManager *gm = GraphManager::get_instance();
    World *w = World::get_instance();
    sdl_image_data *tree_data = new sdl_image_data{"tree.png"};


    for (int i = 0; i < amount; i++) {
        vec2 s_position = gm->graph->nodes[random_number(gm->graph->nodes.size())]->get_position()->clone();
        ResourceEntity *s_entity = new TreeEntity(s_position, 50);
        s_entity->set_textures("tree.png", "trunk.png");
        SDL_ImageRenderObject *tree_object = new SDL_ImageRenderObject(s_position, {40, 40}, tree_data);
        s_entity->set_representation(tree_object);
        w->add_entity(s_entity);
    }
}

void add_stones(int amount) {
    GraphManager *gm = GraphManager::get_instance();
    World *w = World::get_instance();
    sdl_image_data *stone_mine_data = new sdl_image_data{"stonemine.png"};

    for (int i = 0; i < amount; i++) {
        vec2 s_position = gm->graph->nodes[random_number(gm->graph->nodes.size())]->get_position()->clone();
        ResourceEntity *stone_mine_entity = new StoneMineEntity(s_position, 50);
        stone_mine_entity->set_textures("stonemine.png", "depletedstonemine.png");
        SDL_ImageRenderObject *stone_mine = new SDL_ImageRenderObject(s_position, {40, 40}, stone_mine_data);
        stone_mine_entity->set_representation(stone_mine);
        w->add_entity(stone_mine_entity);
    }
}

void add_gold_mines(int amount){
    GraphManager *gm = GraphManager::get_instance();
    World *w = World::get_instance();
    sdl_image_data *gold_mine_data = new sdl_image_data{"goldmine.png"};

    for(int i = 0; i < amount; i++) {
        vec2 s_position = gm->graph->nodes[random_number(gm->graph->nodes.size())]->get_position()->clone();
        ResourceEntity *gold_mine_entity = new GoldMineEntity(s_position, 50);
        gold_mine_entity->set_textures("goldmine.png", "depletedgoldmine.png");
        SDL_ImageRenderObject *gold_mine_object = new SDL_ImageRenderObject(s_position, {40,40},
                                                                            gold_mine_data);
        gold_mine_entity->set_representation(gold_mine_object);
        w->add_entity(gold_mine_entity);
    }
}


int main(int argc, char **argv) {
    if (!init_everything()) {
        return -1;
    }

    SDL_MouseEventDispatcher *mouse_dispatcher = SDL_MouseEventDispatcher::get_instance();
    SDL_KeyEventDispatcher *key_dispatcher = SDL_KeyEventDispatcher::get_instance();

    PlayerManager *pm = PlayerManager::get_instance();
    pm->setup(2);

    TextureManager *tm = TextureManager::get_instance();
    tm->setup(renderer);

    GraphManager *gm = GraphManager::get_instance();
    gm->setup(world_size, node_distance);

    /// Add resources
    add_trees(100);
    add_stones(100);
    add_gold_mines(100);
    ///End resources

    SDLRenderer *render_engine = new SDLRenderer(renderer, {window_size.x, window_size.y});

    vec2 main_panel_position = {0, 0}, main_panel_size = {window_size.x, window_size.y};
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
    vec2 resource_panel_pos = {600, 0}, resource_panel_size = {200, 40};
    sdl_data *resource_panel_data = new sdl_data{0, 0, 0, 100};
    SDL_RenderObject *panel_o = new SDL_RenderObject(resource_panel_pos, resource_panel_size, resource_panel_data);
    SDLResourcePanel *resource_panel = new SDLResourcePanel(panel_o);

    TTF_Font *f_wood = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);
    sdl_data *sdl_label_data_wood = new sdl_data{255, 255, 255, 255};
    vec2 resource_panel_pos_wood = {605, 5};
    SDLRenderResourceLabel *wood_label = new SDLRenderResourceLabel(resource_panel_pos_wood, {60, 30}, sdl_label_data_wood, "log.png",
                                                    ResourceType::WOOD, f_wood);
    SDLResourceLabel *wood_panel = new SDLResourceLabel(wood_label);

    TTF_Font *f_gold = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);
    sdl_data *sdl_label_data_gold = new sdl_data{255, 255, 255, 255};
    vec2 resource_panel_pos_gold = {675, 5};
    SDLRenderResourceLabel *gold_label = new SDLRenderResourceLabel(resource_panel_pos_gold, {60, 30}, sdl_label_data_gold, "gold.png",
                                                    ResourceType::GOLD, f_gold);
    SDLResourceLabel *gold_panel = new SDLResourceLabel(gold_label);

    TTF_Font *f_stone = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 100);
    sdl_data *sdl_label_data_stone = new sdl_data{255, 255, 255, 255};
    vec2 resource_panel_pos_stone = {740, 5};
    SDLRenderLabel *stone_label = new SDLRenderResourceLabel(resource_panel_pos_stone, {60, 30}, sdl_label_data_stone,
                                                     "stone.png",
                                                     ResourceType::STONE, f_stone);
    SDLResourceLabel *stone_panel = new SDLResourceLabel(stone_label);
    ///End Resource Panel

    ///Begin Waves
    WaveManager *wm = WaveManager::get_instance();
    std::vector<MovingEntityType> possibilities = {
            MovingEntityType::KNIGHT
    };
    wave_setting setting = {wave_pre_stage_time, wave_preparation_time, wave_duration,
                            stat_modifier, stat_modifier_increment, wave_amount, wave_unit_size};
    Wave *wave = new Wave(setting);
    wave->set_spawn_possibilities(possibilities);
    wm->set_wave(wave);
    vec2 wave_panel_position = {10, 250}, wave_panel_size = {150, 250};
    std::string wave_content = "";
    std::string wave_font = "res/font/Roboto/Roboto-Regular.ttf";
    sdl_solid_text *wave_panel_data = new sdl_solid_text{{0, 0, 0, 100}, {255, 255, 255, 255}, wave_font, 18, 15,
                                                         wave_content};
    SDLRenderSolidText *wave_render_object = new SDLRenderSolidText(wave_panel_position, wave_panel_size,
                                                                    wave_panel_data);
    SDLWavePanel *wave_panel = new SDLWavePanel(wave_render_object, WaveManager::get_instance());

    vec2 restart_button_pos = {50, 470}, restart_button_size = {60, 30};
    std::string restart_content = "Restart";
    sdl_solid_text *restart_text = new sdl_solid_text{{255, 0, 0, 255}, {255, 255, 255, 255}, wave_font, 14, 5,
                                                      restart_content};
    SDLRenderSolidText *restart_o = new SDLRenderSolidText(restart_button_pos, restart_button_size, restart_text);
    RestartWaveButton *restart_button = new RestartWaveButton(restart_o);

    wave_panel->add_component(restart_button);

    WaveResetHandler *reset = new WaveResetHandler();
    restart_button->set_mouse_callback(reset);
    mouse_dispatcher->register_callback(restart_button, reset);
    ///End Waves

    // building/control panel
    vec2 control_panel_pos = {0, 500}, control_panel_size = {680, 100.0};
    sdl_data *control_panel_data = new sdl_data{0, 0, 0, 100};
    SDL_RenderObject *panel_b = new SDL_RenderObject(control_panel_pos, control_panel_size, control_panel_data);

    SDLControlPanel *control_panel = SDLControlPanel::get_instance(panel_b);


    SDLPanel *description_panel = new SDLPanel(DescriptionManager::get_description());



    // unit information panel
    vec2 unit_info_panel_pos = {680, 500};
    vec2 unit_info_panel_size = {120, 100};
    sdl_data *unit_info_panel_data = new sdl_data{0, 0, 0, 100};
    SDL_RenderObject *unit_info_panel_renderer = new SDL_RenderObject(unit_info_panel_pos, unit_info_panel_size, unit_info_panel_data);
    SDLUnitInfoPanel *unit_info_panel = new SDLUnitInfoPanel(unit_info_panel_renderer);



    resource_panel->add_component(wood_panel);
    resource_panel->add_component(gold_panel);
    resource_panel->add_component(stone_panel);
    main_panel->add_component(resource_panel);
    main_panel->add_component(wave_panel);
    main_panel->add_component(unit_info_panel);
    main_panel->add_component(control_panel);
    main_panel->add_component(description_panel);
    main_window->add_component(main_panel);

    main_window->show();


    delete main_window;
    delete mouse_dispatcher;
    delete key_dispatcher;
    return 0;
}
