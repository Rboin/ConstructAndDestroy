//
// Created by Sander on 6-4-2017.
//

#ifndef C_AND_D_PROJECT_SKELETON_ENTITY_H
#define C_AND_D_PROJECT_SKELETON_ENTITY_H

#include "moving_entity.h"

class MovingEntity;

class SkeletonEntity : public MovingEntity {
public:
    SkeletonEntity(const mesh *, vec2, float, const float, const float);
    void select();
    void deselect();
};


#endif //C_AND_D_PROJECT_SKELETON_ENTITY_H
