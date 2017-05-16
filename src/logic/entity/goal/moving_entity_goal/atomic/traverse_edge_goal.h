//
// Created by Sander on 14-3-2017.
//

#ifndef C_AND_D_PROJECT_TRAVERSE_EDGE_GOAL_H
#define C_AND_D_PROJECT_TRAVERSE_EDGE_GOAL_H

#include <goal/atomic_goal.h>
#include <types.h>

class MovingEntity;
class Node;

class TraverseEdgeGoal : public AtomicGoal<MovingEntity> {
private:
    vec2 *goal;
public:
    TraverseEdgeGoal(MovingEntity *t, vec2*, int initiator = Initiator::AI);

    void activate() override;

    const int process() override;

    void terminate() override;

    const char *get_name() const override;
};


#endif //C_AND_D_PROJECT_TRAVERSE_EDGE_GOAL_H
