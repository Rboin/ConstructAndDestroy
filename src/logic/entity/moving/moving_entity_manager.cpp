
#include "entity/goal/evaluator/work_evaluator.h"
#include "sdl/image/sdl_image_render_object.h"
#include "world/world.h"
#include "behaviour/force_calculator.h"
#include "behaviour/calculator/basic_force_calculator.h"
#include "entity/goal/moving_entity_goal/think_goal.h"
#include "behaviour/behaviour.h"
#include "moving_entity_manager.h"
#include "moving_entity_factory.h"
#include "moving_entity.h"
#include "entity/player.h"

MovingEntityManager* MovingEntityManager::instance = nullptr;

MovingEntityManager::MovingEntityManager() {}

MovingEntityManager::~MovingEntityManager() {
    delete this->instance;
}

MovingEntityManager *MovingEntityManager::get_instance() {
    if(!instance){
        instance = new MovingEntityManager();
    }

    return instance;

}

void MovingEntityManager::add_unit(Player *player, vec2 position, MovingEntityType moving_entity_type) {

    MovingEntity* me = MovingEntityFactory::create(player, position, moving_entity_type);

    ForceCalculator *calculator = new BasicForceCalculator();
    Behaviour *behaviour = new Behaviour(calculator);
    ThinkGoal *think_goal = new ThinkGoal(me);

    think_goal->add_evaluator(new WorkEvaluator());

    me->set_behaviour(behaviour);
    me->set_goal(think_goal);
    me->set_player(player->get_id());

    vec2 entity_size = {50, 50};


    sdl_image_data *entity_data = new sdl_image_data{me->get_texture()};

    SDL_ImageRenderObject *entity_render_object = new SDL_ImageRenderObject(position, entity_size, entity_data);
    me->set_representation(entity_render_object);

    World::get_instance()->add_entity(me);
}



