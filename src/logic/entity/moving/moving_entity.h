//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_MOVINGENTITY_H
#define C_AND_D_PROJECT_MOVINGENTITY_H

#include <stack>
#include "entity/static/resource_type.h"
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
    bool _engaged;
    Behaviour *_behaviour;
    ThinkGoal *_brain;
    std::vector<Weapon *> _weapons;
    JobType _job_type;
    std::stack<vec2 *> _path;
    float _delta_time;

protected:
    float carrying;
public:
    std::string texture;

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

    virtual std::string get_texture();

    virtual void set_texture(std::string src);

    bool is_engaged();

    void set_engaged(bool);

    void set_job_type(JobType);

    void set_carrying(float);

    float get_carrying();

    JobType get_job_type();

    void set_path(std::stack<vec2 *>);

    std::stack<vec2 *>& get_path();

    float get_delta_time();
};

#endif //C_AND_D_PROJECT_MOVINGENTITY_H
