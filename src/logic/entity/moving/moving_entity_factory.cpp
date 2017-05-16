//
// Created by Mark on 10-5-2017.
//

#include "world/world.h"
#include "moving_entity.h"
#include "moving_entity_types.h"
#include "moving_entity_factory.h"
#include "knight_entity.h"
#include "miner_entity.h"
#include "lumberjack_entity.h"
#include "skeleton_entity.h"
#include "../player.h"
#include "mesh.h"

vec2* MovingEntityFactory::default_shape = new vec2[4] {vec2(-20,20), vec2(20,-20), vec2(20,20), vec2(-20, 20)};

mesh* MovingEntityFactory::base = new mesh {4, default_shape};

MovingEntity *MovingEntityFactory::create(Player* player, vec2 position, MovingEntityType moving_entity_type) {

    MovingEntity* me;

    switch(moving_entity_type){

        case MovingEntityType::KNIGHT:
            me = new KnightEntity(base, position, 100, 0.2, 0.2);
            break;

        case MovingEntityType::MINER:
            me = new MinerEntity(base, position, 100, 0.2, 0.2, GOLDMINER);
            break;

        case MovingEntityType::LUMBERJACK:
            me = new LumberJackEntity(base, position, 100, 0.2, 0.2);
            break;

        case MovingEntityType::SKELETON:
            //me = SkeletonEntity(base, position, 100, 0.2, 0.2);
            break;
        default:
            me = nullptr;
            break;
    }

    return me;



}

