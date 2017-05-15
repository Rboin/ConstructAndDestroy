//
// Created by Stephan on 18-4-2017.
//

#ifndef C_AND_D_PROJECT_CASTLE_ENTITY_H
#define C_AND_D_PROJECT_CASTLE_ENTITY_H

#include "entity/moving/moving_entity_types.h"
#include "building_entity.h"
#include <vector.h>
#include <types.h>

class BuildingEntity;

class CastleEntity : public BuildingEntity {
    float delta_time;
    std::vector<MovingEntityType > orders;

public:
    CastleEntity(const mesh *, vec2, float);
    CastleEntity(const mesh *, float);
    void set_to_transparent(bool, bool = true);

    void select();
    void deselect();

    void update(float d) override;
    void order_unit(Player *player, vec2 position, MovingEntityType moving_entity_type);
    void order_unit(MovingEntityType moving_entity_type);
};

#endif //C_AND_D_PROJECT_CASTLE_ENTITY_H
