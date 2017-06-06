//
// Created by robin on 3/1/17.
//

#ifndef C_AND_D_PROJECT_MOVINGENTITY_H
#define C_AND_D_PROJECT_MOVINGENTITY_H

#include <stack>
#include <string>
#include "entity/static/resource_type.h"
#include "entity/base_entity.h"
#include "entity/goal/moving_entity_goal/job_type.h"

//=================== Forward declarations ===================
class Behaviour;

class ThinkGoal;

//============================================================

class MovingEntity : public BaseEntity {
private:
        vec2 _velocity;
    bool _engaged;
    Behaviour *_behaviour;
    ThinkGoal *_brain;
    JobType _job_type;
    std::stack<vec2 *> _path;
    float _delta_time;

protected:
    float carrying;
    float max_force;
    float max_speed;
public:
    std::string texture;

    MovingEntity(vec2, float, JobType);

    ~MovingEntity();

    virtual Behaviour *get_behaviour();

    virtual void set_behaviour(Behaviour *);

    virtual ThinkGoal *get_brain();

    virtual void set_goal(ThinkGoal *);

    virtual float get_max_speed();

    virtual vec2 get_velocity();

    virtual void update(float);

    virtual void select();

    virtual void deselect();

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
