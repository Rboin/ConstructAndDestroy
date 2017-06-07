//
// Created by Stephan Schrijver on 7-6-2017.
//

#include "stone_miner_entity.h"

StoneMinerEntity::StoneMinerEntity(vec2 position, float mass):MinerEntity(position, mass, JobType::SMINER) {
    texture = "stoneminer.png";
    max_force = 0.2;
    max_speed = 0.1;
}
