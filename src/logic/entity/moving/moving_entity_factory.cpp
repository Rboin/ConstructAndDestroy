//
// Created by Mark on 10-5-2017.
//

#include "settings.h"
#include "world/world.h"
#include "moving_entity.h"
#include "moving_entity_factory.h"
#include "knight_entity.h"
#include "miner_entity.h"
#include "lumberjack_entity.h"
#include "../player.h"

MovingEntity *MovingEntityFactory::create(Player* player, vec2 position, MovingEntityType moving_entity_type) {

    MovingEntity* me;

    switch(moving_entity_type){

        case MovingEntityType::KNIGHT:
            me = new KnightEntity(position, 100, 0.2, 0.2);
            if(player->get_id() != player_id)
            {
                me->set_texture("blackknight.png");
            }
            break;

        case MovingEntityType::MINER:
            me = new MinerEntity(position, 100, 0.2, 0.2, GOLDMINER);
            break;

        case MovingEntityType::LUMBERJACK:
            me = new LumberJackEntity(position, 100, 0.2, 0.2);
            break;
        default:
            me = nullptr;
            break;
    }

    return me;



}

MovingEntityFactory::~MovingEntityFactory() {

}


