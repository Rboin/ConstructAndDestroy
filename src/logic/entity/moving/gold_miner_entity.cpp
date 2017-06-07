//
// Created by Stephan Schrijver on 7-6-2017.
//

#include "gold_miner_entity.h"

GoldMinerEntity::GoldMinerEntity(vec2 position, float mass) : MinerEntity(position, mass, JobType::GMINER) {
    texture = "goldminer.png";
}