#ifndef MOVES_H
#define MOVES_H

#include "behaviors/moves_down.h"

class MovesBehavior : public MovesDownBehavior {
public:
    MovesBehavior(const float maxSpeed, const float acceleration) : MovesDownBehavior(maxSpeed, acceleration) {
    }

    void update(std::shared_ptr<Particle> particle, Grid &grid, const UpdateParams &params) override {
        if (!this->shouldUpdate(params))
            return;
        MovesDownBehavior::update(particle, grid, params);
    }

protected:
    [[nodiscard]] bool shouldUpdate(const UpdateParams &params) const {
        const auto sign = static_cast<int>(std::copysign(1, this->nextVelocity()));
        return params.direction == sign;
    }
};

#endif //MOVES_H
