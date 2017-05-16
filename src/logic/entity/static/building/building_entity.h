//
// Created by Stephan on 18-04-2017.
//

#ifndef C_AND_D_PROJECT_BUILDING_ENTITY_H
#define C_AND_D_PROJECT_BUILDING_ENTITY_H

#include "building_type.h"
#include "entity/static/static_entity.h"

template<class T> class StateMachine;
class Resources;

class BuildingEntity : public StaticEntity {
private:
    BuildingType building_type;
protected:
    Resources* costs;
public:
    BuildingEntity(const mesh *, vec2, float, BuildingType, TextureTypes);
    BuildingEntity(const mesh *, float, BuildingType, TextureTypes);

    Resources* get_costs();

    BuildingType get_building_type();
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
