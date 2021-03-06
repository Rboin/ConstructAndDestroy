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
#include "cavalier_entity.h"
#include "heavy_cavalier_entity.h"
#include "light_cavalier.h"
#include "juggernaut_entity.h"
#include "mercenary_entity.h"
#include "gold_miner_entity.h"
#include "stone_miner_entity.h"

MovingEntity *MovingEntityFactory::create(Player* player, vec2 position, MovingEntityType moving_entity_type) {

    MovingEntity* me;

    switch(moving_entity_type){

        case MovingEntityType::KNIGHT:
            me = new KnightEntity(position, 100);
            if(player->get_id() != player_id)
            {
                me->set_texture("blackknight.png");
            }
            break;
        case MovingEntityType::LIGHT_CAVALIER:
            me = new LightCavalierEntity(position, 100);
            break;
        case MovingEntityType::CAVALIER:
            me = new CavalierEntity(position, 100);
            break;
        case MovingEntityType::HEAVY_CAVALIER:
            me = new HeavyCavalierEntity(position, 100);
            break;
        case MovingEntityType::GOLDMINER:
            me = new GoldMinerEntity(position, 100);
            break;
        case MovingEntityType::STONEMINER:
            me = new StoneMinerEntity(position, 100);
            break;
        case MovingEntityType::LUMBERJACK:
            me = new LumberJackEntity(position, 100);
            break;
        case MovingEntityType::JUGGERNAUT:
            me = new JuggernautEntity(position, 100);
            break;
        case MovingEntityType::MERCENARY:
            me = new MercenaryEntity(position, 100);
            break;
        default:
            me = nullptr;
            break;
    }

    return me;



}

MovingEntityFactory::~MovingEntityFactory() {

}


