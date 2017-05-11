//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_MOVINGENTITY_H
#define C_AND_D_PROJECT_MOVINGENTITY_H

#include <stack>
#include "fuzzy/fuzzy_module.h"
#include "weapon.h"
#include "entity/base_entity.h"
#include "entity/goal/moving_entity_goal/job_type.h"

//=================== Forward declarations ===================
class Behaviour;

class ThinkGoal;

struct bsp_node;

//============================================================

class MovingEntity : public BaseEntity {
private:
    const float MAX_FORCE, MAX_SPEED;
    vec2 _velocity;
    bool _possessed;
    Behaviour *_behaviour;
    ThinkGoal *_brain;
    std::vector<Weapon *> _weapons;
public:
    MovingEntity(const mesh *, vec2, float, const float, const float, JobType);

    virtual Behaviour *get_behaviour();

    virtual void set_behaviour(Behaviour *);

    virtual ThinkGoal *get_brain();

    virtual void set_goal(ThinkGoal *);

    virtual float get_max_speed();

    virtual vec2 get_velocity();

    virtual void update_render_mesh();

    virtual void update_render_mesh(const mat2 &);

    virtual void update(float);

    virtual void select();

    virtual void deselect();

    void add_weapons();

    void select_weapon();

    std::stack<vec2 *> path;

    float carrying;

    float tiredness;

    float hunger;

    float delta_time;

    JobType job_type;
};

#endif //C_AND_D_PROJECT_MOVINGENTITY_H
