//
// Created by Sander on 4-4-2017.
//

#ifndef C_AND_D_PROJECT_LUMBERJACK_ENTITY_H
#define C_AND_D_PROJECT_LUMBERJACK_ENTITY_H

#include "moving_entity.h"

class MovingEntity;

class LumberJackEntity : public MovingEntity {
private:

public:
    LumberJackEntity(vec2, float, const float, const float);
    void select();
    void deselect();

    std::string get_texture()override ;
    void set_texture(std::string src) override ;
};


#endif //C_AND_D_PROJECT_LUMBERJACK_ENTITY_H
