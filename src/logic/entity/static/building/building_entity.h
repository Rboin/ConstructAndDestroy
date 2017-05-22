//
// Created by Stephan on 18-04-2017.
//

#ifndef C_AND_D_PROJECT_BUILDING_ENTITY_H
#define C_AND_D_PROJECT_BUILDING_ENTITY_H

#include <vector>
#include "entity/moving/moving_entity_types.h"
#include "building_type.h"
#include "entity/static/static_entity.h"
#include "types.h"
#include "spawnable_entity.h"

template<class T> class StateMachine;
class Resources;

class BuildingEntity : public StaticEntity {
private:
    BuildingType building_type;
    float delta_time;
    float order_time;
    vec2 spawn;
    std::vector<MovingEntityType> orders;

protected:
    Resources* costs;
    std::vector<SpawnableEntity*> spawnable_entities;
public:
    ~BuildingEntity();
    BuildingEntity(const mesh *, vec2, float, BuildingType, TextureTypes);
    BuildingEntity(const mesh *, float, BuildingType, TextureTypes);

    Resources* get_costs();

    void update(float d) override;
    void set_position(float, float, bool);
    void order_unit_from_factory(Player *player, vec2 position, MovingEntityType moving_entity_type);
    void order_unit(MovingEntityType moving_entity_type);
    int get_order_time();

    BuildingType get_building_type();

    std::vector<SpawnableEntity*> get_spawnable_entities();

    /*
     * This will change the texture of a building entity.
     * The first boolean will determine if the texture should be transparent
     * The second boolean will determine if the texture needs a red border
     * The red border will only work if the object is transparent
     *
     * TODO: transparency should be set with a SDL method instead of setting another texture!
     */
    virtual void set_transparent_or_border(bool, bool) = 0;
};


#endif //C_AND_D_PROJECT_BUILDING_ENTITY_H
