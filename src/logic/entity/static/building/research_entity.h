//
// Created by Sander on 6-6-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_RESEARCH_ENTITY_H
#define CONSTRUCT_AND_DESTROY_RESEARCH_ENTITY_H


#include "building_entity.h"

class ResearchEntity : public BuildingEntity {
public:
    ResearchEntity(vec2, float);
    ResearchEntity(float);
    void set_transparent_or_border(bool, bool = true);

    void select() override ;
    void deselect() override;
};


#endif //CONSTRUCT_AND_DESTROY_RESEARCH_ENTITY_H
