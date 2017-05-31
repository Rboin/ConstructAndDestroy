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
    vec2 *_goal;
    float _goal_time;
public:
    TraverseEdgeGoal(MovingEntity *t, vec2*, int initiator = Initiator::AI);

    ~TraverseEdgeGoal();

    /*!
     * Sets SeekStrategy and a target. Also sets status to active.
     */
    void activate() override;

    /*!
     * Checks if the entity is close to it's goal. When it's close enough this goal will be completed.
     * There also is a check for the time active for this goal. Currently, when this goal is active more
     * than 1 second there is a high probability that the bot is stuck so we call the method is_stuck to unstuck it.
     */
    const int process() override;

    void terminate() override;

    const char *get_name() const override;

    /*!
     * Remove the SeekStrategy and set it again to unstuck the bot.
     */
    void is_stuck();
};


#endif //C_AND_D_PROJECT_TRAVERSE_EDGE_GOAL_H
