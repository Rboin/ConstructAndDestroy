//
// Created by Stephan on 18-4-2017.
//

#ifndef C_AND_D_PROJECT_CASTLE_ENTITY_H
#define C_AND_D_PROJECT_CASTLE_ENTITY_H

#include "entity/moving/moving_entity_types.h"
#include "building_entity.h"
#include <types.h>
#include <vector>

class CastleEntity : public BuildingEntity {
    float delta_time;
    float order_time;
    vec2 spawn;
    std::vector<MovingEntityType> orders;

public:
    CastleEntity(const mesh *, vec2, float);
    CastleEntity(const mesh *, float);

    void select();
    void deselect();

    void update(float d) override;
    void order_unit_from_factory(Player *player, vec2 position, MovingEntityType moving_entity_type);
    void order_unit(MovingEntityType moving_entity_type);
    void set_transparent_or_border(bool, bool = false);
};

#endif //C_AND_D_PROJECT_CASTLE_ENTITY_H
