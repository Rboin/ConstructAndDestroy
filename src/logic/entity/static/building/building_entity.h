//
// Created by Stephan on 18-04-2017.
//

#ifndef C_AND_D_PROJECT_BUILDING_ENTITY_H
#define C_AND_D_PROJECT_BUILDING_ENTITY_H

#include <vector>
#include "moving_entity_types.h"
#include "building_type.h"
#include "entity/static/static_entity.h"
#include "types.h"

template<class T> class StateMachine;
class Resources;
class SpawnableEntity;
class Upgrade;

class BuildingEntity : public StaticEntity {
private:
    BuildingType _building_type;
    float _delta_time;
    float _order_time;
    std::vector<MovingEntityType> _orders;
protected:
    Resources* costs;
    std::vector<SpawnableEntity*> spawnable_entities;
    std::vector<Upgrade*> upgrades;
public:
    ~BuildingEntity();
    BuildingEntity(vec2, float, BuildingType, TextureTypes);
    BuildingEntity(float, BuildingType, TextureTypes);

    Resources* get_costs();
    std::vector<MovingEntityType> get_orders();

    void update(float d) override;
    void order_unit_from_factory(Player *player, vec2 position, MovingEntityType moving_entity_type);
    void order_unit(MovingEntityType moving_entity_type);
    int get_order_time();
    int get_delta_time();

    BuildingType get_building_type();

    std::vector<SpawnableEntity*> get_spawnable_entities();

    std::vector<Upgrade*> get_upgrades();

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
